/**
 * Holds the base classes for different state machine
 * implementations. State machines have similarities regardless of the
 * specifics of the techniques that they use. The classes in this file
 * are then extended and used by other types of state machines.
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

/**
     * The base transition is used for any kind of state machine. It
     * doesn't force a representation for the states or their
     * transitions, but does give values for the actions to be carried
     * out and the triggering.
     */
    public class BaseTransition
    {
        /**
         * The transition needs to decide if it can be triggered or
         * not. This will depend on the sub-class of transition we're
         * dealing with.
         */
        public virtual bool IsTriggered()
        {
            return false;
        }

        /**
         * The transition can also optionally return a list of actions
         * that need to be performed during the transition.
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
         * Points to the next transition in the sequence. Transitions
         * are arranged in a singly linked list.
         */
        public BaseTransition Next;
    };

/**
     * @name Types of Condition
     *
     * Conditions can be used to trigger transitions (or anything
     * else).
     */
    /* @{ */

    /**
     * The condition interface offsets the problem of whether
     * transitions should fire by having a separate set of condition
     * instances that can be combined together with boolean operators.
     */
    public class Condition
    {
        /**
         * Performs the test for this condition.
         */
        public virtual bool Test()
        {
            return false;
        }
    };

    /**
     * A condition that checks if a watched integer matches a
     * specified value.
     */
    public class IntegerMatchCondition : Condition
    {
        /**
         * A pointer to the integer value we should try to match.
         */
        public int Watch { get; set; }

        /**
         * The target value for the integer. If this is matched, then
         * the condition will be true.
         */
        public int Target { get; set; }

        /**
         * Checks if the target matches the watch value.
         */
        public override bool Test()
        {
            return (Watch == Target);
        }
    };

    /**
     * A mixin intended for use with a base transition derived
     * class. Uses an external condition instances to determine if the
     * transition is triggered.
     */
    public class ConditionalTransitionMixin
    {
        /**
         * Holds the condition used to determine if the transition
         * should trigger.
         */
        public Condition Condition { get; set; }

        /**
         * Returns true if the transition wants to fire.
         */
        public virtual bool isTriggered()
        {
            return Condition.Test();
        }
    };