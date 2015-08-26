/**
 * Holds classes for making decisions based on a decision
 * tree. Decision trees consist of a series of decisions, arranged so
 * that the results of one decision lead to another, until finally a
 * decision is reached at the end of the tree.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

/**
     * A decision tree node is a base class for anything that makes a
     * decision.
     */
    public interface IDecisionTreeNode<T>
    {
    
        /**
         * The make decision method carries out a decision making
         * process and returns the new decision tree node that we've
         * reached in the tree.
         */
        IDecisionTreeNode<T> MakeDecision();
    };

    /**
     * An action is a decision tree node at the end of the tree. It
     * simply returns itself as the result of the next decision.
     */
   public class DecisionTreeAction<T> : IDecisionTreeNode<T>
    {
        /**
         * Makes the decision - in  this case there is no decision, so
         * this method returns the action back again..
         */
        public IDecisionTreeNode<T> MakeDecision()
        {
            return this;
        }
    };

    /**
     * Other than actions, the tree is made up of decisions, which
     * come up with some boolean result and choose a branch based on
     * that.
     */
   public class Decision<T> : IDecisionTreeNode<T>
    {
    
        public IDecisionTreeNode<T> TrueBranch { get; set; }
        public IDecisionTreeNode<T> FalseBranch { get; set; }

        /**
         * This method actually does the checking for the decision.
         */
        public virtual bool GetBranch()
        {
            return false;
        }

        /**
         * This is where the decision tree algorithm is located: it
         * recursively walks down the tree until it reaches the final
         * item to return (which is an action).
         */
        public virtual IDecisionTreeNode<T> MakeDecision()
        {
            // Choose a branch based on the getBranch method
            if (GetBranch())
            {
                // Make sure its not null before recursing.
                if (TrueBranch == null) return null;
                else return TrueBranch.MakeDecision();
            }
            else
            {
                // Make sure its not null before recursing.
                if (FalseBranch == null) return null;
                else return FalseBranch.MakeDecision();
            }
        }
    };

    /**
     * This class represents a stable random decision. As long as the
     * decision is reached at each frame, the decision will be made
     * the same way each time. Otherwise the decision will be made at
     * random.
     */
    public class RandomDecision<T> : Decision<T>
    {
        public RandomDecision()
        {
            LastDecisionFrame = 0;
            LastDecision = false;
        }

        /**
         * Holds the last decision that was made.
         */
        public bool LastDecision { get; set; }

        /**
         * Holds the number of the last frame at which the decision
         * was made.
         */
        public UInt32 LastDecisionFrame { get; set; }

        /** Creates a new random decision. */
        //RandomDecision();

        /**
         * Works out which branch to follow.
         */
        public override bool GetBranch()
        {
            // TODO: This should take into account the present frame, change
            Random rnd = new Random();
            UInt32 thisFrame = (uint)rnd.Next(0, 60);

            // If we didn't get here last time, then things may change
            if (thisFrame > LastDecisionFrame + 1)
            {
                if (rnd.Next(0, 1) == 1)
                    LastDecision = true;
                else
                    LastDecision = false;
            }

            // In any case, store the frame number
            LastDecisionFrame = thisFrame;

            // And return the stored value
            return LastDecision;
        }
    };

    /**
     * This class represents a stable random decision. As long as the
     * decision is reached at each frame, the decision will be made
     * the same way each time. Otherwise the decision will be made at
     * random.
     */
    public class RandomDecisionWithTimeOut<T> : RandomDecision<T>
    {
        public RandomDecisionWithTimeOut()
        {
            FirstDecisionFrame = 0;
        }

        /**
         * Holds the frame number that the current decision was made
         * on.
         */
        UInt32 FirstDecisionFrame { get; set; }

        /**
         * Holds the number of frames to wait before timing out the
         * decision.
         */
        UInt32 TimeOutDuration { get; set; }

        /** Creates a new random decision. */
        //RandomDecisionWithTimeOut();

        /**
         * Works out which branch to follow.
         */
        public override bool GetBranch()
        {
            // TODO: This should take into account the present frame, change
            Random rnd = new Random();
            UInt32 thisFrame = (uint)rnd.Next(0, 60);

            // Check if the stored decision is either too old, or if we
            // timed out.
            if (thisFrame > LastDecisionFrame + 1 ||
            thisFrame > FirstDecisionFrame + TimeOutDuration)
            {

                // Make a new decision
                if (rnd.Next(0, 1) == 1)
                    LastDecision = true;
                else
                    LastDecision = false;

                // And record that it was just made
                FirstDecisionFrame = thisFrame;
            }

            // Update the frame number
            LastDecisionFrame = thisFrame;

            // And return the stored value
            return LastDecision;
        }
    };

