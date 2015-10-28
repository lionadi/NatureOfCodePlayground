using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Assets.Scripts.AI.NeuralNetworks;
using Assets.Scripts.AI.GeneticAlgorithms;
using System.Linq;
using System.Text;

/*
In summary, here’s what the program is doing each epoch:
1. For each minesweeper and for NumTicks iterations, call the Update function
and increment the minesweeper’s fitness score accordingly.
2. Retrieve the vector of weights for the minesweeper’s ANN.
3. Use the genetic algorithm to evolve a new population of network weights.
4. Insert the new weights into the minesweeper’s ANN.
5. Go to Step 1 until reasonable performance is achieved.

*/

/// <summary>
/// Things which the Controller class does:
/// - The Minesweeper objects are created.
/// - The number of weights used in the neural networks is calculated and then this
/// figure is used in the initialization of an instance of the genetic algorithm class.
/// - The random chromosomes(the weights) from the GA object are retrieved
/// and inserted(by careful brain surgery) into the minesweeper’s neural nets.
/// - The mines are created and scattered about in random locations.
/// - The vertex buffers for the minesweeper shape and mine shape are created.
/// </summary>
public class Controller : MonoBehaviour {

    /// <summary>
    /// storage for the population of genomes
    /// </summary>
    List<Host> ThePopulation;

    List<Minesweeper> Sweepers;

    List<Target> Mines;

    GeneticAlgorithm GA;

    #region InitializerValues

    public int NumberOfMines;

    public int NumberOfWeightsInNeuralNetwork;

    public int FramesPerSecond = 60;

    public int NumInputs = 4;

    public int NumHidden = 1;

    public int NeuronsPerHiddenLayer = 6;

    public int NumOutputs = 2;

    public double ActivationResponse = 1;

    public double Bias = -1;

    public double MaxTurnRate = 0.3;

    public double MaxSpeed = 2;

    public int SweeperScale = 5;

    public int NumMines = 40;

    public int NumSweepers = 30;

    public int NumTicks = 2000;

    public double MineScale = 2;

    public double CrossoverRate = 0.7;

    public double MutationRate = 0.1;

    public double MaxPerturbation = 0.3;

    public int NumElite = 4;

    public int NumCopiesElite = 1;

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

    /// <summary>
    /// cycles per generation
    /// </summary>
    public int Ticks;

    /// <summary>
    /// generation counter
    /// </summary>
    public int Generations;

    public Transform Mine;
    public Transform Sweeper;

    public void StartInitialization()
    {
        //initilaize the sweepers, their brains and the GA factory

        this.Mines = new List<Target>();
        this.Sweepers = new List<Minesweeper>();
        this.ThePopulation = new List<Host>();
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
        this.Sweepers.AddRange(GameObject.FindObjectsOfType<Minesweeper>());

        if (this.Sweepers.Count <= 0 || this.Mines.Count <= 0)
            return;

        for (int i = 0; i < NeuralNetworkParams.NumSweepers; i++)
        {
            this.Sweepers[i].StartInitialization();

        }
        // get the total number of weights used in the sweepers
        //NN so we can initialise the GA
        this.NumberOfWeightsInNeuralNetwork = this.Sweepers[0].GetNumberOfWeights();

        //initialize the Genetic Algorithm class
        this.GA = new GeneticAlgorithm(NeuralNetworkParams.NumSweepers, NeuralNetworkParams.MutationRate, NeuralNetworkParams.CrossoverRate, this.NumberOfWeightsInNeuralNetwork);


        //Get the weights from the GA and insert into the sweepers brains
        this.ThePopulation = this.GA.GetHosts();
        this.GA.PutSplitPoints(this.Sweepers[0].GetSplitPoints());

        for (int i = 0; i < NeuralNetworkParams.NumSweepers; i++)
        {
            this.Sweepers[i].PutWeights(ref this.ThePopulation[i].Genome.Chromosomes);
        }

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
        NeuralNetworkParams.NumSweepers = this.NumSweepers +1;
        NeuralNetworkParams.NumMines = this.NumberOfMines;
        NeuralNetworkParams.WindowWidth = Camera.main.pixelWidth;
        NeuralNetworkParams.WindowHeight = Camera.main.pixelHeight;
        NeuralNetworkParams.FramesPerSecond = this.FramesPerSecond;
        NeuralNetworkParams.NumInputs = this.NumInputs;
        NeuralNetworkParams.NumHidden = this.NumHidden;
        NeuralNetworkParams.NeuronsPerHiddenLayer = this.NeuronsPerHiddenLayer;
        NeuralNetworkParams.NumOutputs = this.NumOutputs;
        NeuralNetworkParams.ActivationResponse = this.ActivationResponse;
        NeuralNetworkParams.Bias = this.Bias;
        NeuralNetworkParams.MaxTurnRate = this.MaxTurnRate;
        NeuralNetworkParams.MaxSpeed = this.MaxSpeed;
        NeuralNetworkParams.SweeperScale = this.SweeperScale;
        NeuralNetworkParams.NumTicks = this.NumTicks;
        NeuralNetworkParams.MineScale = this.MineScale;
        NeuralNetworkParams.CrossoverRate = this.CrossoverRate;
        NeuralNetworkParams.MutationRate = this.MutationRate;
        NeuralNetworkParams.MaxPerturbation = this.MaxPerturbation;
        NeuralNetworkParams.NumElite = this.NumElite;
        NeuralNetworkParams.NumCopiesElite = this.NumCopiesElite;
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
    /// minesweepers, calling their update functions and updating the minesweepers’ fitness
    /// scores if a mine has been found.In addition, because m_vecThePopulation contains
    /// copies of all the genomes, the relevant fitness scores are adjusted here too.If the
    /// required number of frames has passed for the completion of a generation, the
    /// method runs an epoch of the genetic algorithm producing a new generation of
    /// weights.These weights are used to replace the old weights in the minesweeper’s
    /// neural nets and each minesweeper’s parameters are reset ready for a new generation.
    /// </summary>
    /// <returns></returns>
    public bool PerformCalculations()
    {
        //run the sweepers through NeuralNetworkParams.NumTicks amount of cycles. During
        //this loop each sweepers NN is constantly updated with the appropriate
        //information from its surroundings. The output from the NN is obtained
        //and the sweeper is moved. If it encounters a mine its fitness is
        //updated appropriately,
        if (this.Ticks++ < NeuralNetworkParams.NumTicks)
        {
            for (int i = 0; i < NeuralNetworkParams.NumSweepers; ++i)
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

                //see if it's found a mine
                int GrabHit = this.Sweepers[i].CheckForMine(minePositions,
                                                            NeuralNetworkParams.MineScale);

                // Fitness calculation for a sweeper
                // ----------------------------------------
                if (GrabHit >= 0)
                {
                    //we have discovered a mine so increase fitness
                    this.Sweepers[i].IncrementFitness();

                    //mine found so replace the mine with another at a random 
                    //position
                    this.Mines[GrabHit].transform.position = GetNewMineLocation();
                }

                // increase the fitness by a ratio of total cells visited compared to total cells in memory map. In other words the more adventurous the sweeper is the better fitness score, the more new locations it explores the better fitness.
                if(this.Sweepers[i].GetNumberOfVisitedCellsInMemoryMap() > 0)
                    this.Sweepers[i].IncrementFitness(this.Sweepers[i].GetRatioOfNumberOfVisitedCellsInMemoryMap());

                // Prefer sweepers which do not hit obstacles
                if (!this.Sweepers[i].HasHitObstacle)
                    this.Sweepers[i].IncrementFitnessMediumImpact();

                // Prefer sweepers which do not rotate like crazy
                if(this.Sweepers[i].Rotation > -this.Sweepers[i].RotationTolerance && this.Sweepers[i].Rotation < this.Sweepers[i].RotationTolerance)
                    this.Sweepers[i].IncrementFitnessMediumImpact();

                // ----------------------------------------

                //update the chromos fitness score
                this.ThePopulation[i].Genome.Fitness = this.Sweepers[i].Fitness;

            }
        }

        //Another generation has been completed.

        //Time to run the GA and update the sweepers with their new NNs
        else
        {
            this.ThePopulation = this.GA.ProcessToNextGeneration(this.ThePopulation);

            //update the stats to be used in our stat window
            this.AverageFitnessValuesInGeneration.Add(this.GA.AverageFitness());
            this.BestFitnessValuesInGeneration.Add(this.GA.BestFitness());
            Debug.Log("This Gen average=>    " + this.AverageFitnessValuesInGeneration[this.AverageFitnessValuesInGeneration.Count - 1]);
            Debug.Log("This Gen best=>    " + this.BestFitnessValuesInGeneration[this.BestFitnessValuesInGeneration.Count - 1]);
            StringBuilder sb = new StringBuilder();
            foreach (double d in this.AverageFitnessValuesInGeneration)
                sb.AppendFormat("{0};", d);
            sb.AppendLine();
            foreach (double d in this.BestFitnessValuesInGeneration)
                sb.AppendFormat("{0};", d);
            sb.AppendLine();
            Debug.Log(sb.ToString());

            //increment the generation counter
            ++this.Generations;

            //reset cycles
            this.Ticks = 0;

            //run the GA to create a new population
            

            //insert the new (hopefully)improved brains back into the sweepers
            //and reset their positions etc
            for (int i = 0; i < NeuralNetworkParams.NumSweepers; ++i)
            {
                this.Sweepers[i].PutWeights(ref this.ThePopulation[i].Genome.Chromosomes);

                this.Sweepers[i].Reset();
            }
        }

        foreach (Minesweeper mineS in this.Sweepers)
            mineS.GetComponent<SpriteRenderer>().color = Color.white;

        foreach (Minesweeper mineS in this.Sweepers.OrderByDescending(o => o.Fitness).Take(10))
            mineS.GetComponent<SpriteRenderer>().color = Color.green;

        foreach (Minesweeper mineS in this.Sweepers.OrderByDescending(o => o.Fitness).Take(5))
            mineS.GetComponent<SpriteRenderer>().color = Color.yellow;

        foreach (Minesweeper mineS in this.Sweepers.OrderByDescending(o => o.Fitness).Take(1))
            mineS.GetComponent<SpriteRenderer>().color = Color.red;

        return true;
    }

    public void PlotStats()
    {

    }

    public void FastRenderToggle()
    {
        this.FastRender = !this.FastRender;
    }
}
