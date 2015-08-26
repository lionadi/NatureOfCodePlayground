/**
 * Holds an implementation of a finite state machine.
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

// TODO: Implement hierachial state machine

    /**
     * This represents one internal state a character be in: such as
     * angry, or searching-for-ammo.
     */
    public class StateMachineState
    {
        /**
         * Returns the first in a sequence of actions that should be
         * performed while the character is in this state.
         *
         * Note that this method should return one or more newly
         * created action instances, and the caller of this method
         * should be responsible for the deletion. In the default
         * implementation, it returns nothing.
         */
        public virtual Action GetActions()
        {
            return null;
        }

        /**
         * Returns the sequence of actions to perform when arriving in
         * this state.
         *
         * Note that this method should return one or more newly
         * created action instances, and the caller of this method
         * should be responsible for the deletion. In the default
         * implementation, it returns nothing.
         */
        public virtual Action GetEntryActions()
        {
            return null;
        }

        /**
         * Returns the sequence of actions to perform when leaving
         * this state.
         *
         * Note that this method should return one or more newly
         * created action instances, and the caller of this method
         * should be responsible for the deletion. In the default
         * implementation, it returns nothing.
         */
        public virtual Action GetExitActions()
        {
            return null;
        }

        /**
         * The first in the sequence of transitions that can leave
         * this state.
         */
        public Transition FirstTransition { get; set; }
    };

    /**
     * Transitions map between state machines.
     */
    public class Transition : BaseTransition
    {
        /**
         * The transition returns a target state to transition to.
         */
        public virtual StateMachineState GetTargetState()
        {
            return null;
        }
    };

    /**
     * A mixin intended for use with a BasTransition derived class. We
     * assume that the trasition always leads to the same state. So a
     * target state member is added.
     */
    public class FixedTargetTransitionMixin
    {
        /**
         * Holds the state into which the transition should flow.
         */
        public StateMachineState Target { get; set; }

        /**
         * The transition returns a target state to transition to.
         */
        public virtual StateMachineState GetTargetState()
        {
            return Target;
        }
    };

    /**
     * Encapsulates a single layer state machine (i.e. one without
     * hierarchical transitions, see HierarchicalStateMachine for
     * that.
     */
    public class StateMachine
    {
        /**
         * Holds the initial state (a pointer into the 'state' array).
         */
        public StateMachineState InitialState { get; set; }

        /**
         * Holds the current state of the machine.
         */
        public StateMachineState CurrentState { get; set; }

        /**
         * This method runs the state machine - it checks for
         * transitions, applies them and returns a list of actions.
         */
        public virtual Action Update()
        {
            // The variable to hold the actions to perform
            Action actions = null;

            // First case - we have no current state.
            if (CurrentState == null)
            {
                // In this case we use the entry action for the initial state.
                if (InitialState != null)
                {

                    // Transition to the first state
                    CurrentState = InitialState;

                    // Returns the initial states entry actions
                    actions = CurrentState.GetEntryActions();

                }
                else
                {

                    // We have nothing to do
                    actions = null;
                }
            }

            // Otherwise we have a current state to work with
            else
            {
                // Start off with no transition
                Transition transition = null;

                // Check through each transition in the current state.
                BaseTransition testTransition = CurrentState.FirstTransition;
                while (testTransition != null)
                {
                    if (testTransition.IsTriggered())
                    {
                        transition = (Transition)testTransition;
                        break;
                    }
                    testTransition = testTransition.Next;
                }

                // Check if we found a transition
                if (transition != null)
                {
                    // Find our destination
                    StateMachineState nextState = transition.GetTargetState();

                    // Accumulate our list of actions
                    Action tempList = null;
                    Action last = null;

                    // Add each element to the list in turn
                    actions = CurrentState.GetExitActions();
                    last = actions.GetLast();

                    tempList = transition.GetActions();
                    last.Next = tempList;
                    last = tempList.GetLast();

                    tempList = nextState.GetActions();
                    last.Next = tempList;

                    // Update the change of state
                    CurrentState = nextState;
                }
                // Otherwise our actions to perform are simply those for the
                // current state.
                else
                {
                    actions = CurrentState.GetActions();
                }
            }

            return actions;
        }
    };