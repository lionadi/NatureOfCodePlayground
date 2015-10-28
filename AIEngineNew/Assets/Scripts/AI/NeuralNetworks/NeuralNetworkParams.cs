using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.AI.NeuralNetworks
{

    public enum NeuralNetworkMode { LEARNING, ACTIVE, UNREADY, TRAINING };

    public static class NeuralNetworkParams
    {
        public static double Pi                 = 3.14159265358979F;
        public static double HalfPi             = Pi / 2;
        public static double TwoPi              = Pi* 2;
        public static int WindowWidth            = 400;
        public static int WindowHeight           = 400;
        public static int FramesPerSecond       = 0;
        public static int NumInputs             = 0;
        public static int NumHidden             = 0;
        public static int NeuronsPerHiddenLayer = 0;
        public static int NumOutputs            = 0;
        public static double ActivationResponse = 0;
        public static double Bias               = 0;
        /// <summary>
        /// limits how fast the sweepers can turn
        /// </summary>
        public static double MaxTurnRate        = 0;
        public static double MaxSpeed           = 0;
        public static int SweeperScale          = 0;
        public static int NumSweepers           = 0;
        public static int NumMines              = 0;
        /// <summary>
        /// number of time steps we allow for each generation to live
        /// </summary>
        public static int NumTicks              = 0;
        /// <summary>
        /// scaling factor for mines
        /// </summary>
        public static double MineScale          = 0;
        public static double CrossoverRate      = 0;
        public static double MutationRate       = 0;
        /// <summary>
        /// the maximum amount the ga may mutate each weight by
        /// </summary>
        public static double MaxPerturbation    = 0;
        public static int NumElite              = 0;
        public static int NumCopiesElite        = 0;
        /// <summary>
        /// total number of built in patterns 
        /// </summary>
        public static int NUM_PATTERNS          = 11;

        /// <summary>
        /// how much the input data is perturbed by to make additional training sets 
        /// </summary>
        public static double MAX_NOISE_TO_ADD = 0.1f;

        /// <summary>
        /// how many vectors each pattern contains 
        /// </summary>
        public static int NUM_VECTORS = 12;

        /// <summary>
        /// output has to be above this value for the program to agree on a pattern. Below this value and it  will try to guess the pattern 
        /// </summary>
        public static double MATCH_TOLERANCE = 0.98f;

        /// <summary>
        /// for tweeking the sigmoid function
        /// </summary>
        public static double ACTIVATION_RESPONSE = 1.0f;

        /// <summary>
        /// the learning rate for the backprop. 
        /// </summary>
        public static int LEARNING_RATE = 2;

        /// <summary>
        /// when the total error is below this value the backprop stops training 
        /// </summary>
        public static double ERROR_THRESHOLD = 0.05f;

        public static double MOMENTUM = 0.9;

        public static NeuralNetworkMode Mode = NeuralNetworkMode.ACTIVE;
    }
}
