using UnityEngine;
using System.Collections;
using System.Collections.Generic;
//using Assets.Scripts.AI.NeuralNetworks;
using Assets.Scripts.AI.NeuralNetworks.NEAT;
//using Assets.Scripts.AI.GeneticAlgorithms;
using System.Linq;
using System.Text;

/*
In summary, here’s what the program is doing each epoch:
1. For each MinesweeperNEAT and for NumTicks iterations, call the Update function
and increment the MinesweeperNEAT’s fitness score accordingly.
2. Retrieve the vector of weights for the MinesweeperNEAT’s ANN.
3. Use the genetic algorithm to evolve a new population of network weights.
4. Insert the new weights into the MinesweeperNEAT’s ANN.
5. Go to Step 1 until reasonable performance is achieved.

*/

/// <summary>
/// Things which the Controller class does:
/// - The MinesweeperNEAT objects are created.
/// - The number of weights used in the neural networks is calculated and then this
/// figure is used in the initialization of an instance of the genetic algorithm class.
/// - The random chromosomes(the weights) from the GA object are retrieved
/// and inserted(by careful brain surgery) into the MinesweeperNEAT’s neural nets.
/// - The mines are created and scattered about in random locations.
/// - The vertex buffers for the MinesweeperNEAT shape and mine shape are created.
/// </summary>
public class ControllerNEAT : MonoBehaviour {

    /// <summary>
    /// storage for the population of genomes
    /// </summary>
    //List<Host> ThePopulation;

    List<MinesweeperNEAT> Sweepers;

    /// <summary>
    /// array of best sweepers from last generation (used for display purposes when 'B' is pressed by the user) 
    /// </summary>
    List<MinesweeperNEAT> BestSweepers;

    List<Target> Mines;

    GeneticAlgorithm GA;

    public Camera targetCamera;
    public List<GameObject> VisibleUnityNeurons;

    public Grid MapperGridForVisualization;

    #region InitializerValues

    public int NumberOfMines;

    public int FramesPerSecond = 60;

    public double MaxTurnRate = 2;

    public double MaxSpeed = 2;

    public int SweeperScale = 5;

    public int NumMines = 40;

    public int NumSweepers = 30;

    public int NumTicks = 2000;

    public double MineScale = 2;

    /// <summary>
    /// the number of best performing sweepers shown when 'B' is selected. (you will see copies from the previous generation 
    /// </summary>
    public int NumBestSweepers = 4;

    #region Phenotype/NeuralNetworkClass

    public int NumInputs = 4;

    //public int NumHidden = 1;

    //public int NeuronsPerHiddenLayer = 6;

    public int NumOutputs = 2;

    public double ActivationSigmoindResponse = 1;

    public double Bias = -1;

    #endregion

    #region GeneticAlgorithmNEATClass

    public double MutationRate = 0.3;

    public double CrossoverRate = 0.7;

    /// <summary>
    /// how long we allow a species to exist without any improvement
    /// </summary>
    public int NumGensAllowedNoImprovement = 15;

    /// <summary>
    /// maximum number of neurons permitted in the network 
    /// </summary>
    public int MaxPermittedNeurons = 100;

    #endregion

    #region SpeciesClass
    /// <summary>
    /// during fitness adjustment this is how much the fitnesses of young species are boosted (eg 1.2 is a 20% boost) 
    /// </summary>
    public double YoungFitnessBonus = 1.4;

    /// <summary>
    /// if the species are below this age their fitnesses are boosted 
    /// </summary>
    public int YoungBonusAgeThreshhold = 10;

    /// <summary>
    /// number of population to survive each epoch. (0.2 = 20%) 
    /// </summary>
    public double SurvivalRate = 0.2;

    /// <summary>
    /// if the species is above this age their fitness gets penalized 
    /// </summary>
    public int OldAgeThreshold = 50;

    /// <summary>
    /// by this much 
    /// </summary>
    public double OldAgePenalty = 0.7;

    #endregion

    #region GenotypeClass

    /// <summary>
    /// number of times we try to find 2 unlinked nodes when adding a link. see Genome::AddLink() 
    /// </summary>
    public int NumAddLinkAttempts = 5;

    /// <summary>
    /// number of attempts made to choose a node that is not an input node and that does not already have a recurrently looped connection to itself. See CGenome::AddLink() 
    /// </summary>
    public int NumTrysToFindLoopedLink = 5;

    /// <summary>
    /// the number of attempts made to find an old link to prevent chaining in Genome::AddNeuron 
    /// </summary>
    public int NumTrysToFindOldLink = 5;

    /// <summary>
    /// the chance, each epoch, that a neuron or link will be added to the genome 
    /// </summary>
    public double ChanceAddLink = 0.07;
    /// <summary>
    /// the chance, each epoch, that a neuron or link will be added to the genome 
    /// </summary>
    public double ChanceAddNode = 0.04;
    /// <summary>
    /// the chance, each epoch, that a neuron or link will be added to the genome 
    /// </summary>
    public double ChanceAddRecurrentLink = 0.05;

    
    /// <summary>
    /// mutation probabilities for mutating the weights in Genome::Mutate() 
    /// </summary>
    public double MaxWeightPerturbation = 0.5;
    /// <summary>
    /// mutation probabilities for mutating the weights in Genome::Mutate() 
    /// </summary>
    public double ProbabilityWeightReplaced = 0.1;

    /// <summary>
    /// probabilities for mutating the activation response 
    /// </summary>
    public double ActivationMutationRate = 0.1;
    /// <summary>
    /// probabilities for mutating the activation response 
    /// </summary>
    public double MaxActivationPerturbation = 0.1;

    /// <summary>
    /// the smaller the number the more species will be created 
    /// </summary>
    public double CompatibilityThreshold = 0.26;

    #endregion

    //public int NumElite = 4;

    //public int NumCopiesElite = 1;

    #endregion

    /// <summary>
    /// stores the average fitness per generation for use 
    /// in graphing.
    /// </summary>
    List<double> AverageFitnessValuesInGeneration;

    /// <summary>
    /// stores the best fitness per generation
    /// </summary>
    List<double> BestFitnessValuesInGeneration;

    /// <summary>
    /// toggles the speed at which the simulation runs
    /// </summary>
    public bool FastRender;

    public int TicksCount = 0;

    /// <summary>
    /// cycles per generation
    /// </summary>
    //public int Ticks;

    /// <summary>
    /// generation counter
    /// </summary>
    public int Generations;

    public Transform Mine;
    public Transform Sweeper;

    public void StartInitialization()
    {
        //initilaize the sweepers, their brains and the GA factory
        this.VisibleUnityNeurons = new List<GameObject>();
        this.Mines = new List<Target>();
        this.Sweepers = new List<MinesweeperNEAT>();
        this.BestSweepers = new List<MinesweeperNEAT>();
        //this.ThePopulation = new List<Host>();
        this.AverageFitnessValuesInGeneration = new List<double>();
        this.BestFitnessValuesInGeneration = new List<double>();

        this.GrabInitializationValues();
        this.Generations = 0;
        this.FastRender = false;

        if (this.Mine == null || this.Sweeper == null)
            return;

        for (int i = 0; i < NeuralNetworkParams.NumMines; i++)
        {
            Instantiate(this.Mine, this.GetNewMineLocation(), Quaternion.identity);
        }

        for (int i = 0; i < this.NumSweepers; i++)
        {
            Instantiate(this.Sweeper, this.GetNewMineLocation(), Quaternion.identity);
        }

        //Find/create mines in scene
        this.Mines.AddRange(GameObject.FindObjectsOfType<Target>());

        //Find/create sweepers in scene
        this.Sweepers.AddRange(GameObject.FindObjectsOfType<MinesweeperNEAT>());

        if (this.Sweepers.Count <= 0 || this.Mines.Count <= 0)
            return;

        for (int i = 0; i < NeuralNetworkParams.UnityInstantiatedNumSweepers; i++)
        {
            this.Sweepers[i].StartInitialization();

        }
        // get the total number of weights used in the sweepers
        //NN so we can initialise the GA
        //this.NumberOfWeightsInNeuralNetwork = this.Sweepers[0].GetNumberOfWeights();

        //initialize the Genetic Algorithm class
        this.GA = new GeneticAlgorithm(NeuralNetworkParams.UnityInstantiatedNumSweepers, NeuralNetworkParams.NumInputs, NeuralNetworkParams.NumOutputs, NeuralNetworkParams.WindowWidth, NeuralNetworkParams.WindowHeight);

        //create the phenotypes   
        List<NeuralNet> pBrains = this.GA.CreatePhenotypes();

        //assign the phenotypes   
        for (int i = 0; i < NeuralNetworkParams.UnityInstantiatedNumSweepers; i++)
        {
            this.Sweepers[i].InsertNewBrain(pBrains[i]);
        }

        //Get the weights from the GA and insert into the sweepers brains
        //this.ThePopulation = this.GA.GetHosts();
        //this.GA.PutSplitPoints(this.Sweepers[0].GetSplitPoints());

        //for (int i = 0; i < NeuralNetworkParams.NumSweepers; i++)
        //{
        //    this.Sweepers[i].PutWeights(ref this.ThePopulation[i].Genome.Chromosomes);
        //}

        //initialize mines in random positions within the application window
        for (int i = 0; i < this.NumberOfMines; ++i)
        {
            this.Mines[i].transform.position = GetNewMineLocation();
        }
    }

    public Vector2 GetNewMineLocation()
    {
        var newMinePosition = Camera.main.ScreenToWorldPoint(new Vector3((float)RandomProvider.RandomFloat() * NeuralNetworkParams.WindowWidth,
                                       (float)RandomProvider.RandomFloat() * NeuralNetworkParams.WindowHeight, 0));
        return new Vector2(newMinePosition.x, newMinePosition.y);
    }
    // Use this for initialization
    void Start () {
        this.StartInitialization();
    }

    /// <summary>
    /// Grabs the values defined in UnityEditor for the Neural Network demonstration to be used later
    /// </summary>
    private void GrabInitializationValues()
    {
        // Because of prefab initilization
        NeuralNetworkParams.NumSweepers = this.NumSweepers;
        NeuralNetworkParams.NumMines = this.NumberOfMines;
        NeuralNetworkParams.WindowWidth = Camera.main.pixelWidth;
        NeuralNetworkParams.WindowHeight = Camera.main.pixelHeight;
        NeuralNetworkParams.FramesPerSecond = this.FramesPerSecond;
        
        NeuralNetworkParams.MaxTurnRate = this.MaxTurnRate;
        NeuralNetworkParams.MaxSpeed = this.MaxSpeed;
        NeuralNetworkParams.SweeperScale = this.SweeperScale;
        NeuralNetworkParams.NumTicks = this.NumTicks;
        NeuralNetworkParams.MineScale = this.MineScale;

        // Phenotype/Neural Network class
        NeuralNetworkParams.NumInputs = this.NumInputs;
        NeuralNetworkParams.NumOutputs = this.NumOutputs;
        NeuralNetworkParams.Bias = this.Bias;
        NeuralNetworkParams.ActivationSigmoindResponse = this.ActivationSigmoindResponse;

        // Genetic Algorithm NEAT class
        NeuralNetworkParams.CrossoverRate = this.CrossoverRate;

        NeuralNetworkParams.MutationRate = this.MutationRate;

        NeuralNetworkParams.NumBestSweepers = this.NumBestSweepers;

        NeuralNetworkParams.MaxWeightPerturbation = this.MaxWeightPerturbation;

        NeuralNetworkParams.NumGensAllowedNoImprovement = this.NumGensAllowedNoImprovement;

        NeuralNetworkParams.MaxPermittedNeurons = this.MaxPermittedNeurons;

        // Species

        NeuralNetworkParams.YoungFitnessBonus = this.YoungFitnessBonus;

        NeuralNetworkParams.YoungBonusAgeThreshhold = this.YoungBonusAgeThreshhold;

        NeuralNetworkParams.SurvivalRate = this.SurvivalRate;

        NeuralNetworkParams.OldAgeThreshold = this.OldAgeThreshold;

        NeuralNetworkParams.OldAgePenalty = this.OldAgePenalty;

        // Genotype class
        NeuralNetworkParams.NumAddLinkAttempts = this.NumAddLinkAttempts;

        NeuralNetworkParams.NumTrysToFindLoopedLink = this.NumTrysToFindLoopedLink;

        NeuralNetworkParams.NumTrysToFindOldLink = this.NumTrysToFindOldLink;

        NeuralNetworkParams.ChanceAddLink = this.ChanceAddLink;

        NeuralNetworkParams.ChanceAddNode = this.ChanceAddNode;

        NeuralNetworkParams.ChanceAddRecurrentLink = this.ChanceAddRecurrentLink;

        NeuralNetworkParams.MaxWeightPerturbation = this.MaxWeightPerturbation;

        NeuralNetworkParams.ProbabilityWeightReplaced = this.ProbabilityWeightReplaced;

        NeuralNetworkParams.ActivationMutationRate = this.ActivationMutationRate;

        NeuralNetworkParams.MaxActivationPerturbation = this.MaxActivationPerturbation;

        NeuralNetworkParams.CompatibilityThreshold = this.CompatibilityThreshold;
}

	// Update is called once per frame
	void Update () {
        if (this.Mine == null || this.Sweeper == null)
            return;
        this.GrabInitializationValues();
        this.PerformCalculations();
	}

    /// <summary>
    /// This is the main workhorse. The entire simulation is controlled from here.
    /// This method is called each frame. The first half of the function iterates through the
    /// MinesweeperNEATs, calling their update functions and updating the MinesweeperNEATs’ fitness
    /// scores if a mine has been found.In addition, because m_vecThePopulation contains
    /// copies of all the genomes, the relevant fitness scores are adjusted here too.If the
    /// required number of frames has passed for the completion of a generation, the
    /// method runs an epoch of the genetic algorithm producing a new generation of
    /// weights.These weights are used to replace the old weights in the MinesweeperNEAT’s
    /// neural nets and each MinesweeperNEAT’s parameters are reset ready for a new generation.
    /// </summary>
    /// <returns></returns>
    public bool PerformCalculations()
    {
        //Debug.Log("start PerformCalculations");
        //run the sweepers through NeuralNetworkParams.NumTicks amount of cycles. During
        //this loop each sweepers NN is constantly updated with the appropriate
        //information from its surroundings. The output from the NN is obtained
        //and the sweeper is moved. If it encounters a mine its fitness is
        //updated appropriately,
        if (this.TicksCount++ < NeuralNetworkParams.NumTicks)
        {
            //Debug.Log("Before start of normal tick processing");
            for (int i = 0; i < NeuralNetworkParams.UnityInstantiatedNumSweepers; ++i)
            {
                // TODO_: Optimize this by passing the targets and not collecting the positions
                var minePositions = (from mine in Mines
                                    select new Vector2(mine.transform.position.x, mine.transform.position.y)).ToList();
                //-----------------------------------------------------

                
                //update the NN and position
                if (!this.Sweepers[i].UpdateANN(minePositions))
                {
                    //error in processing the neural net
                    Debug.Log("Wrong amount of NN inputs!");

                    return false;
                }

                //update the NNs of the last generations best performers   
                if (this.Generations > 0)
                {
                    for (int u = 0; u < this.BestSweepers.Count; ++u)
                    {
                        //Debug.Log("Before: update the NN and position");
                        //update the NN and position   
                        if (!this.BestSweepers[u].UpdateANN(minePositions))
                        {
                            //error in processing the neural net   
                            Debug.Log("Wrong amount of NN inputs!");

                            return false;
                        }
                    }
                }

                ////see if it's found a mine
                //int GrabHit = this.Sweepers[i].CheckForMine(minePositions,
                //                                            NeuralNetworkParams.MineScale);

                //// Fitness calculation for a sweeper
                //// ----------------------------------------
                //if (GrabHit >= 0)
                //{
                //    //we have discovered a mine so increase fitness
                //    this.Sweepers[i].IncrementFitness();

                //    //mine found so replace the mine with another at a random 
                //    //position
                //    this.Mines[GrabHit].transform.position = GetNewMineLocation();
                //}

                //// increase the fitness by a ratio of total cells visited compared to total cells in memory map. In other words the more adventurous the sweeper is the better fitness score, the more new locations it explores the better fitness.
                //if(this.Sweepers[i].GetNumberOfVisitedCellsInMemoryMap() > 0)
                //    this.Sweepers[i].IncrementFitness(this.Sweepers[i].GetRatioOfNumberOfVisitedCellsInMemoryMap());

                //// Prefer sweepers which do not hit obstacles
                //if (!this.Sweepers[i].HasHitObstacle)
                //    this.Sweepers[i].IncrementFitnessMediumImpact();

                //// Prefer sweepers which do not rotate like crazy
                //if(this.Sweepers[i].Rotation > -this.Sweepers[i].RotationTolerance && this.Sweepers[i].Rotation < this.Sweepers[i].RotationTolerance)
                //    this.Sweepers[i].IncrementFitnessMediumImpact();

                // ----------------------------------------
                this.Sweepers[i].RealTimeRunCalculations();
                //update the chromos fitness score
                //this.ThePopulation[i].Genome.Fitness = this.Sweepers[i].Fitness;
                


            }
            foreach (MinesweeperNEAT mineS in this.Sweepers)
                mineS.GetComponent<SpriteRenderer>().color = Color.white;

            foreach (MinesweeperNEAT mineS in this.Sweepers.OrderByDescending(o => o.RealTimeFitness).Take(10))
                mineS.GetComponent<SpriteRenderer>().color = Color.green;

            foreach (MinesweeperNEAT mineS in this.Sweepers.OrderByDescending(o => o.RealTimeFitness).Take(5))
                mineS.GetComponent<SpriteRenderer>().color = Color.yellow;

            foreach (MinesweeperNEAT mineS in this.Sweepers.OrderByDescending(o => o.RealTimeFitness).Take(1))
                mineS.GetComponent<SpriteRenderer>().color = Color.red;
        }

        //Another generation has been completed.

        //Time to run the GA and update the sweepers with their new NNs
        else
        {
            //Debug.Log("Before sweepers EndOfRunCalculations");
            //this.ThePopulation = this.GA.ProcessToNextGeneration(this.ThePopulation);

            //first add up each sweepers fitness scores. (remember for this task   
            //there are many different sorts of penalties the sweepers may incur   
            //and each one has a coefficient)   
            for (int swp = 0; swp < this.Sweepers.Count; ++swp)
            {
                this.Sweepers[swp].EndOfRunCalculations();
            }
            //Debug.Log("Before sweepers Sort");
            this.Sweepers.Sort(delegate (MinesweeperNEAT x, MinesweeperNEAT y)
           {
               if (x.Fitness == y.Fitness)
                   return 0;

               if (x.Fitness < y.Fitness)
                   return 1;

               return -1;
           });

            //this.MapperGridForVisualization.Mapper = this.Sweepers[0].MemoryMap;
            //this.MapperGridForVisualization.Generate();
            //Debug.Log("Before Epoch");
            //perform an epoch and grab the new brains   
            List<NeuralNet> pBrains = this.GA.Epoch(GetFitnessScores());

            //insert the new  brains back into the sweepers and reset their   
            //positions   
            for (int i = 0; i < pBrains.Count; ++i)
            {
                this.Sweepers[i].InsertNewBrain(pBrains[i]);

                this.Sweepers[i].Reset();
            }

            foreach (GameObject gObject in VisibleUnityNeurons)
            {
                DestroyImmediate(gObject);
            }
            VisibleUnityNeurons.Clear();

            //grab the NNs of the best performers from the last generation   
            List<NeuralNet> pBestBrains = this.GA.GetBestPhenotypesFromLastGeneration();
            // Delete the old unity neural network on screen
            for (int i = 0; i < pBestBrains.Count; ++i)
            {
                

                pBestBrains[i].DrawNet(
                   Camera.main.ScreenToWorldPoint(new Vector3(Camera.main.pixelWidth, Camera.main.pixelHeight, Camera.main.transform.position.z)),
                   Camera.main.ScreenToWorldPoint(new Vector3(0, 0, Camera.main.transform.position.z)), this.VisibleUnityNeurons);
            }

            //Debug.Log("after neural network draw");

            //put them into our record of the best sweepers   
            //for (int i = 0; i < this.BestSweepers.Count; ++i)
            //{


            //    this.BestSweepers[i].InsertNewBrain(pBestBrains[i]);



            //    this.BestSweepers[i].Reset();
            //}

            //update the stats to be used in our stat window
            //this.AverageFitnessValuesInGeneration.Add(this.GA.getAverageFitness());
            //this.BestFitnessValuesInGeneration.Add(this.GA.BestFitness());
            this.BestFitnessValuesInGeneration.Add(this.GA.GetBestEverFitness());
            //Debug.Log("This Gen average=>    " + this.AverageFitnessValuesInGeneration[this.AverageFitnessValuesInGeneration.Count - 1]);
            Debug.Log("This Gen best=>    " + this.BestFitnessValuesInGeneration[this.BestFitnessValuesInGeneration.Count - 1]);
            //StringBuilder sb = new StringBuilder();
            ////foreach (double d in this.AverageFitnessValuesInGeneration)
            ////    sb.AppendFormat("{0};", d);
            ////sb.AppendLine();
            //foreach (double d in this.BestFitnessValuesInGeneration)
            //    sb.AppendFormat("{0};", d);
            //sb.AppendLine();
            //Debug.Log(sb.ToString());

            //increment the generation counter
            ++this.Generations;

            //reset cycles
            this.TicksCount = 0;

            foreach (MinesweeperNEAT mineS in this.Sweepers)
                mineS.GetComponent<SpriteRenderer>().color = Color.white;

            foreach (MinesweeperNEAT mineS in this.Sweepers.OrderByDescending(o => o.Fitness).Take(10))
                mineS.GetComponent<SpriteRenderer>().color = Color.green;

            foreach (MinesweeperNEAT mineS in this.Sweepers.OrderByDescending(o => o.Fitness).Take(5))
                mineS.GetComponent<SpriteRenderer>().color = Color.yellow;

            foreach (MinesweeperNEAT mineS in this.Sweepers.OrderByDescending(o => o.Fitness).Take(1))
                mineS.GetComponent<SpriteRenderer>().color = Color.red;

            //run the GA to create a new population


            //insert the new (hopefully)improved brains back into the sweepers
            //and reset their positions etc
            //for (int i = 0; i < NeuralNetworkParams.NumSweepers; ++i)
            //{
            //    this.Sweepers[i].PutWeights(ref this.ThePopulation[i].Genome.Chromosomes);

            //    this.Sweepers[i].Reset();
            //}
        }

        
        //Debug.Log("Before main loop wend");
        return true;
    }

    List<double> GetFitnessScores()
    {
        List<double> scores = new List<double>();   
       
        for (int i = 0; i< this.Sweepers.Count; ++i)   
        {   
            scores.Add(this.Sweepers[i].Fitness);   
        }   
        return scores;   
    }

    public void PlotStats()
    {

    }

    public void FastRenderToggle()
    {
        this.FastRender = !this.FastRender;
    }
}
