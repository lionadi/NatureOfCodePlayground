/**
 * Holds the action management routines. Actions are the interface
 * between what the AI wants to do, and the game that allows them to
 * do it. Actions can be combined, sequenced, interrupted, and so on,
 * depending on the needs of the AI.
 *
 * The decision making algorithms in the remainder of the toolkit
 * generate these actions to get the game to take account of their
 * decisions.
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

/**
     * The action class is the base class for any request the AI makes
     * of the game. In some cases the AI is simple enough for this to
     * be uneccesary (in steering behaviours for example, the steering
     * output is often directly applied). In decision making, however,
     * it is more important.
     */
    public class Action
    {
        /**
         * The relative priority of this action. This allows actions
         * to prempt others.
         */
        public float Priority { get; set; }

        /**
         * Actions naturally come in sequences, so their are
         * implemented as a single linked list by default.
         */
        public Action Next { get; set; }

        /**
         * Returns the last action in the list of actions.
         */
        public Action GetLast()
        {
            // If we're at the end, then end
            if (Next == null) return this;

            // Otherwise find the end iteratively
            Action thisAction = this;
            Action nextAction = Next;
            while (nextAction != null)
            {
                thisAction = nextAction;
                nextAction = nextAction.Next;
            }

            // The final element is in thisAction, so return it
            return thisAction;
        }

        /**
         * Checks if this action can be interrupt others. By default
         * no actions can be interrupt.
         */
        public virtual bool CanInterrupt()
        {
            return false;
        }

        /**
         * Asks the action to check if it be performed at the same
         * time as the given action. This relationship may not be
         * reflexible: both actions in a pair are asked, and things
         * only progress if both agree. By default an action cannot be
         * done with any other.
         */
        public virtual bool CanDoBoth(Action other)
        {
            return false;
        }

        /**
         * Returns true if the action is done. Otherwise the manager
         * keeps scheduling the action. The default implementation is
         * always done.
         */
        public virtual bool IsComplete()
        {
            return true;
        }

        /**
         * Requests that the action delete itself and its children.
         */
        public virtual void DeleteList()
        {
            // Decurse first
            if (Next != null) Next.DeleteList();

            // Delete ourself
            this.Next = null;
        }

        /**
         * Called to make the action do its stuff. This depends on the
         * type of action, and the default implementation does
         * nothing.
         */
        public virtual void Act()
        {

        }
    };

/**
     * The action manager is a central marshalling system that can be
     * notified of actions that bits of AI wants to perform, and can
     * correctly and flexibly schedule them. It supports priorities in
     * actions, mixing actions together, and sequences of action.
     */
    public class ActionManager
    {
    
        /**
         * Holds the highest priority value for all actions in the
         * active set.
         */
        private float ActivePriority { get; set; }

        /**
         * Holds the head of the action queue. This consists of
         * actions that have been scheduled, but are not yet being
         * performed.
         */
        private Action ActionQueue { get; set; }

        /**
         * Holds the list of actions that are currently being
         * performed.
         */
        private Action Active { get; set; }

        /**
         * Runs all the active actions, deleting any that
         * complete. This is called automatically by the execute
         * function.
         */
        protected void RunActive()
        {
            Action previous = Active;
            Action next = Active;

            while (next != null)
            {
                // Do the action first
                next.Act();

                // Check if we're done with this action
                if (next.IsComplete())
                {
                    // Remove it from the list
                    previous = next.Next;

                    // Keep a temp of what we're about to delete
                    Action temp = next;

                    // Move the next pointer only along (previous stays)
                    next = next.Next;

                    // And delete the item
                    //delete temp;
                }
                else
                {
                    // We're not done, just chug along
                    previous = next.Next;
                    next = next.Next;
                }
            }
        }

        /**
         * Allows any high-priority actions to interrupt the currently
         * active set. This is called automatically be the execute
         * method.
         */
        protected void CheckInterrupts()
        {
            // Find any new interrupters
            Action previous = ActionQueue;
            Action next = ActionQueue;
            while (next != null)
            {
                // If we drop below the active priority, give up
                if (next.Priority < ActivePriority)
                {
                    break;
                }

                // Otherwise we're beating for priority, so check if we
                // need to interrupt.
                if (next.CanInterrupt())
                {
                    // So we have to interrupt. Initially just replace the
                    // active set.

                    // Delete the previous active list
                    if (Active != null) Active.DeleteList();

                    // Add the new one
                    Active = next;
                    
                    ActivePriority = Active.Priority;

                    // Rewire the queue to extract our action
                    previous = next.Next;
                    next.Next = null;

                    // And stop looking (the highest priority interrupter
                    // wins).
                    break;
                }

                // Check the next one
                previous = next.Next;
                next = next.Next;
            }
        }

        /**
         * Checks through all the actions in the action queue, to see
         * if they can be performed at the same time as the actions
         * already in the active set. If so, they are scheduled. This
         * is called automatically be the execute method.
         */
        protected void AddAllToActive()
        {
            Action previous = ActionQueue;
            Action next = ActionQueue;
            while (next != null)
            {
                Action inActive = Active;
                while (inActive != null)
                {
                    // Check for compatibility
                    if (!inActive.CanDoBoth(next) ||
                        !next.CanDoBoth(inActive))
                    {
                        goto nextInQueue;
                    }
                }

                // We are compatible, so move from the queue to the active set
                previous = next.Next;
                next.Next = Active;
                Active = next;

                // Move the next counter, but keep the previous as is.
                next = next.Next;

                // Don't fall through, because we don't want to update
                // previous
                continue;

            nextInQueue:
                // We only get here if there was no compatibility, so chug along
                previous = next.Next;
                next = next.Next;
            }
        }

        /**
         * Creates a new empty action manager.
         */
        public ActionManager()
        {
            this.ActivePriority = 0;
            this.ActionQueue = null;
            this.Active = null;
        }

        /**
         * Adds the given action to the queue.
         */
        public void ScheduleAction(Action newAction)
        {
            // Find the correct place to insert the new action
            Action previous = this.ActionQueue;
            Action next = this.ActionQueue;
            while (next != null)
            {
                // if we've found a lower priority, we go here. Note that
                // this will be much quicker with a >=, but it means in
                // the absence of priority ordering the queue defaults to
                // fifo, which isn't very useful.
                if (newAction.Priority > next.Priority)
                {
                    break;
                }

                previous = next.Next;
                next = next.Next;
            }

            // When we get here, we've either found the location mid-list
            // or reached the end of the list, so add it on
            previous = newAction;
            newAction.Next = next;
        }

        /**
         * Runs the action manager, running the component actions in
         * turn. Note that the action manager deletes the action
         * objects it is done with.
         */
        public void Execute()
        {
            // Check if we need to interrupt the currently active actions
            CheckInterrupts();

            // Add as many actions to the active set as play with the
            // actions already there.
            AddAllToActive();

            // Execute the active set
            RunActive();
        }
    };


/**
     * Compund actions are made up of sub-actions. This is a base
     * class that adds the sub-action management code that then has
     * sematics added in its sub-classes.
     */
   public  class ActionCompound : Action
   {
        public Action SubActions;

        /**
         * Requests that the action delete itself and its children.
         */
        public override void DeleteList()
        {
            if (SubActions != null) SubActions.DeleteList();
            base.DeleteList();
        }

        /**
         * Compound actions are compatible, only if all their
         * components are compatible.
         */
        public override bool CanDoBoth(Action other)
        {
            Action next = SubActions;
            while (next != null)
            {
                if (!next.CanDoBoth(other)) return false;
                next = next.Next;
            }
            return true;
        }
    };

/**
     * An action combination is a set of actions that can be performed
     * at the same time.
     */
    public class ActionCombination :  ActionCompound
    {
        /**
         * Checks if this action can interrupt. The combination can
         * interrupt if any of its actions can.
         */
        public override bool CanInterrupt()
        {
            Action next = SubActions;
            while (next != null)
            {
                if (next.CanInterrupt()) return true;
                next = next.Next;
            }
            return false;
        }

        /**
         * Returns true if all the sub-actions is done. Otherwise the
         * manager keeps scheduling the action.
         */
        public override bool IsComplete()
        {
            Action next = SubActions;
            while (next != null)
            {
                if (!next.IsComplete()) return false;
                next = next.Next;
            }
            return true;
        }

        /**
         * Called to make the action do its stuff. It calls all its
         * subactions.
         */
        public override void Act()
        {
            Action next = SubActions;
            while (next != null)
            {
                if (!next.IsComplete()) next.Act();
                next = next.Next;
            }
        }
    };

/**
     * An action combination is a set of actions that can be performed
     * at the same time.
     */
    public class ActionSequence :  ActionCompound
    {
        /**
         * Checks if this action can interrupt. The combination can
         * interrupt if the first action can.
         */
        public override bool CanInterrupt()
        {
            if (SubActions != null) return SubActions.CanInterrupt();
            else return false;
        }

        /**
         * Returns true if all the sub-actions are done. Otherwise the
         * manager keeps scheduling the action.
         */
        public override bool IsComplete()
        {
            return (SubActions == null);
        }

        /**
         * Called to make the action do its stuff. It calls all its
         * subactions.
         */
        public override void Act()
        {
            // Check if we have anything to do
            if (SubActions == null) return;

            // Run the first action in the list
            SubActions.Act();

            // Then consume it if its done
            if (SubActions.IsComplete())
            {
                // TODO: Is this needed in C# compared to C++?
                Action temp = SubActions;
                SubActions = SubActions.Next;
                //delete temp;
            }
        }
    };