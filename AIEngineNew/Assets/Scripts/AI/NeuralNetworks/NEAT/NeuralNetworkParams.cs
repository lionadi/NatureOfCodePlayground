using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.AI.NeuralNetworks.NEAT
{

    public enum NeuralNetworkMode { LEARNING, ACTIVE, UNREADY, TRAINING };

    public static class NeuralNetworkParams
    {
        //-------------------------------------------
        // General parameters
        //-------------------------------------------
        public static double Pi                 = 3.14159265358979F;
        public static double HalfPi             = Pi / 2;
        public static double TwoPi              = Pi* 2;
        public static int WindowWidth            = 400;
        public static int WindowHeight           = 400;
        public static int FramesPerSecond       = 0;
        //-------------------------------------------

        

        //-------------------------------------------
        // used to define the sweepers
        //-------------------------------------------
        /// <summary>
        /// limits how fast the sweepers can turn
        /// </summary>
        public static double MaxTurnRate        = 0;
        public static double MaxSpeed           = 0;
        /// <summary>
        /// for controlling the size
        /// </summary>
        public static int SweeperScale          = 0;
        public static int NumSweepers           = 0;
        public static int UnityInstantiatedNumSweepers
        {
            get { return NumSweepers + 1; }
        }
        public static int NumMines              = 0;

        /// <summary>
        /// amount of sensors 
        /// </summary>
        public static int NumSensors = 0;

        /// <summary>
        /// range of sensors
        /// </summary>
        public static double SensorRange = 0;

        /// <summary>
        /// distance 0 < d < 1 for collision detection. The smaller the value is the closer the sweeper has to be to an object. 
        /// </summary>
        public static double CollisionDist = 1;

        //-------------------------------------------

        //-------------------------------------------
        // controller parameters
        //-------------------------------------------
        /// <summary>
        /// number of time steps we allow for each generation to live
        /// </summary>
        public static int NumTicks              = 0;

        //-------------------------------------------
        // Mapper class
        //-------------------------------------------
        public static double CellSize = 0;

        //-------------------------------------------
        // Phenotype/Neural Network class
        //-------------------------------------------
        public static int NumInputs = 0;
        public static int NumOutputs = 0;
        public static double ActivationSigmoindResponse = 1;
        public static double Bias = -1;

        //-------------------------------------------
        // Genotype class
        //-------------------------------------------

        /// <summary>
        /// number of times we try to find 2 unlinked nodes when adding a link. see Genome::AddLink() 
        /// </summary>
        public static int NumAddLinkAttempts = 0;

        /// <summary>
        /// number of attempts made to choose a node that is not an input node and that does not already have a recurrently looped connection to itself. See CGenome::AddLink() 
        /// </summary>
        public static int NumTrysToFindLoopedLink = 5;

        /// <summary>
        /// the number of attempts made to find an old link to prevent chaining in Genome::AddNeuron 
        /// </summary>
        public static int NumTrysToFindOldLink = 5;

        /// <summary>
        /// the chance, each epoch, that a neuron or link will be added to the genome 
        /// </summary>
        public static double ChanceAddLink = 0;
        /// <summary>
        /// the chance, each epoch, that a neuron or link will be added to the genome 
        /// </summary>
        public static double ChanceAddNode = 0;
        /// <summary>
        /// the chance, each epoch, that a neuron or link will be added to the genome 
        /// </summary>
        public static double ChanceAddRecurrentLink = 0;

        /// <summary>
        /// mutation probabilities for mutating the weights in Genome::Mutate() 
        /// </summary>
        public static double MutationRate = 0;
        /// <summary>
        /// mutation probabilities for mutating the weights in Genome::Mutate() 
        /// </summary>
        public static double MaxWeightPerturbation = 0;
        /// <summary>
        /// mutation probabilities for mutating the weights in Genome::Mutate() 
        /// </summary>
        public static double ProbabilityWeightReplaced = 0;

        /// <summary>
        /// probabilities for mutating the activation response 
        /// </summary>
        public static double ActivationMutationRate = 0;
        /// <summary>
        /// probabilities for mutating the activation response 
        /// </summary>
        public static double MaxActivationPerturbation = 0;

        /// <summary>
        /// the smaller the number the more species will be created 
        /// </summary>
        public static double CompatibilityThreshold = 0;

        //-------------------------------------------
        // Species class
        //-------------------------------------------

        /// <summary>
        /// during fitness adjustment this is how much the fitnesses of young species are boosted (eg 1.2 is a 20% boost) 
        /// </summary>
        public static double YoungFitnessBonus = 0;

        /// <summary>
        /// if the species are below this age their fitnesses are boosted 
        /// </summary>
        public static int YoungBonusAgeThreshhold = 0;

        /// <summary>
        /// number of population to survive each epoch. (0.2 = 20%) 
        /// </summary>
        public static double SurvivalRate = 0;

        /// <summary>
        /// if the species is above this age their fitness gets penalized 
        /// </summary>
        public static int OldAgeThreshold = 0;

        /// <summary>
        /// by this much 
        /// </summary>
        public static double OldAgePenalty = 0;

        //-------------------------------------------
        // Genetic Algorithm NEAT class
        //-------------------------------------------
        /// <summary>
        /// how long we allow a species to exist without any improvement
        /// </summary>
        public static int NumGensAllowedNoImprovement;

        /// <summary>
        /// maximum number of neurons permitted in the network 
        /// </summary>
        public static int MaxPermittedNeurons;

        /// <summary>
        /// the number of best performing sweepers shown when 'B' is selected. (you will see copies from the previous generation 
        /// </summary>
        public static int NumBestSweepers;

        public static double CrossoverRate;

        /// <summary>
        /// scaling factor for mines
        /// </summary>
        public static double MineScale          = 0;


        public static NeuralNetworkMode Mode = NeuralNetworkMode.ACTIVE;
    }
}
