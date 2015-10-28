using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.AI.GeneticAlgorithms
{
    public class GeneticAlgorithm
    {
        public int PopulationSize;
        public double CrossoverRate;
        public double MutationRate;
        public int ChromosomeLength;
        public Genome FittestGenome { get; set; }
        public int FittestGenomeIndex { get; set; }
        public double BestFitnessScore;
        public double WorstFitnessScore;
        public double AverageFitnessScore;
        public double TotalFitnessScore;
        public int Generation;
        public double BoltzmannTemperature = 550;

        List<int> SplitPoints = new List<int>();

        /// <summary>
        /// the lower this value, the more species you will get.
        /// </summary>
        public double CompatibilityTolerance = 0.32F;

        /// <summary>
        /// this is the number of generations a species is allowed to live 
        ///without showing any fitness improvement.
        /// </summary>
        public int GenerationsAllowedWithoutImprovement = 20;

        private double BOLTZMANN_DT = 0.05F;
        private double BOLTZMANN_MIN_TEMP = 1;

        private List<Host> Population;


        public int NextGenomeID = 0;
        public int NextSpeciesID = 0;

        public List<Host> GetHosts()
        {
            return this.Population;
        }

        public void PutSplitPoints(List<int> splitPoints)
        {
            this.SplitPoints = splitPoints;
        }

        /// <summary>
        /// takes a population of chromosones and runs the algorithm through one cycle
        /// </summary>
        /// <returns>Returns a new population of chromosones.</returns>
        public List<Host> ProcessToNextGeneration(List<Host> oldPopulation)
        {
            //assign the given population to the classes population
            this.Population = oldPopulation;

            //reset the appropriate variables
            this.Reset();

            //calculate best, worst, average and total fitness
            this.CalculateBestWorstAverageTotalFitnessScore(ref this.Population);

            //create a temporary storage to store new chromosones
            List<Host> newPopulation = new List<Host>();

            //Now to add a little elitism we shall add in some copies of the
            //fittest genomes. Make sure we add an EVEN number or the roulette
            //wheel sampling will crash
            if ((NeuralNetworks.NeuralNetworkParams.NumCopiesElite * NeuralNetworks.NeuralNetworkParams.NumElite % 2) == 0)
            {
                this.GrabNBest(NeuralNetworks.NeuralNetworkParams.NumElite, NeuralNetworks.NeuralNetworkParams.NumCopiesElite, ref this.Population, ref newPopulation, false);
            }

            // now we enter the GA loop
            //repeat until a new population is generated
            while(newPopulation.Count < this.PopulationSize)
            {
                Host mum = this.MonteCarloSelection(ref this.Population);
                Host dad = this.MonteCarloSelection(ref this.Population);

                Host baby1 = new Host(0, () => { return RandomProvider.RandomClamped(); });
                Host baby2 = new Host(0, () => { return RandomProvider.RandomClamped(); });

                this.CrossoverAtNeuralNetworkSplits(ref mum.Genome.Chromosomes, ref dad.Genome.Chromosomes, ref baby1.Genome.Chromosomes, ref baby2.Genome.Chromosomes, ref this.SplitPoints);

                this.MutateReplace(ref baby1.Genome.Chromosomes, () => { return RandomProvider.RandomClamped() * NeuralNetworks.NeuralNetworkParams.MaxPerturbation; });
                this.MutateReplace(ref baby2.Genome.Chromosomes, () => { return RandomProvider.RandomClamped() * NeuralNetworks.NeuralNetworkParams.MaxPerturbation; });

                //now copy into vecNewPop population
                newPopulation.Add(baby1);
                newPopulation.Add(baby2);
            }

            this.Population = newPopulation;

            return this.Population;
        }

        public void Reset()
        {
            this.TotalFitnessScore = 0;
            this.BestFitnessScore = 0;
            this.WorstFitnessScore = 0;
            this.AverageFitnessScore = 0;
        }

        public GeneticAlgorithm(int populationSize, double mutationRate, double crossoverRate, int numberOfWeights)
        {
            this.Population = new List<Host>();
            this.PopulationSize = populationSize;
            this.MutationRate = mutationRate;
            this.CrossoverRate = crossoverRate;
            this.ChromosomeLength = numberOfWeights;

            for(int x = 0; x < this.PopulationSize; ++x)
            {
                this.Population.Add(new Host(this.ChromosomeLength, () => { return RandomProvider.RandomClamped(); }));
                
            }

            this.Reset();
            this.WorstFitnessScore = 99999999;
        }

        #region CommonFunctions
        /// <summary>
        /// calculates the fittest and weakest genome and the average/total 
        ///  fitness scores.
        /// </summary>
        /// <param name="source"></param>
        public void CalculateBestWorstAverageTotalFitnessScore(ref List<Host> source)
        {
            this.TotalFitnessScore = 0;
            this.BestFitnessScore = 0;
            this.WorstFitnessScore = float.MaxValue;
            foreach (Host host in source)
            {
                double normalizedFitnessScore = host.Genome.Fitness;

                if (normalizedFitnessScore < this.WorstFitnessScore)
                    this.WorstFitnessScore = normalizedFitnessScore;

                if (normalizedFitnessScore > this.BestFitnessScore)
                    this.BestFitnessScore = normalizedFitnessScore;

                this.TotalFitnessScore += normalizedFitnessScore;
            }

            this.AverageFitnessScore = this.TotalFitnessScore / source.Count;
        }

        /// <summary>
        /// this function calculates the variance of the population
        /// </summary>
        /// <param name="hosts"></param>
        /// <returns></returns>
        double CalculateVariance(ref List<Host> hosts)
        {
            double RunningTotal = 0.0F;

            //first iterate through the population to calculate the standard
            //deviation
            for (int gen = 0; gen < hosts.Count; ++gen)
            {
                RunningTotal += (hosts[gen].Genome.Fitness - this.AverageFitnessScore) *
                                (hosts[gen].Genome.Fitness - this.AverageFitnessScore);
            }

            return RunningTotal / hosts.Count;
        }

        public double AverageFitness() {  return this.TotalFitnessScore / this.PopulationSize;}
        public double BestFitness() {return this.BestFitnessScore; }

#endregion

#region MutatioOperators

/// <summary>
/// Mutates a chromosome by adding a value to the chromosome
/// </summary>
/// <param name="genes"></param>
/// <param name="geneInitializationFunction">NOTICE: That you must provice an anonymous function which will be called for every chromosome when the mutation takes place.</param>
public void MutateReplace(ref List<double> genes, Func<double> geneInitializationFunction)
        {
            for (int i = 0; i < genes.Count; i++)
            {
                if ((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) < MutationRate)
                {
                    genes[i] += geneInitializationFunction();
                }
            }
        }


        #endregion

        #region SelectionOperators

        public Host MonteCarloSelection(ref List<Host> source)
        {
            Host selectionHost = null;

            while (selectionHost == null)
            {
                int a = RandomProvider.RND.Next(0, source.Count - 1);
                int b = RandomProvider.RND.Next(0, source.Count - 1);

                int populationIndexChosen = -1;

                if (source[a].Genome.Fitness > source[b].Genome.Fitness)
                {
                    populationIndexChosen = a;
                }
                else
                {
                    populationIndexChosen = b;
                }

                if (populationIndexChosen >= 0)
                    selectionHost = source[populationIndexChosen];
            }

            return selectionHost;
        }
        #endregion

        #region CrossoverOperators

        /// <summary>
        /// genetic algorithm
        /// uses these split points to implement a two-point crossover operator
        /// </summary>
        /// <param name="mum"></param>
        /// <param name="dad"></param>
        /// <param name="baby1"></param>
        /// <param name="baby2"></param>
        public void CrossoverAtNeuralNetworkSplits(ref List<double> mum, ref List<double> dad, ref List<double> baby1, ref List<double> baby2, ref List<int> neuralNetworkSplitPoints)
        {
            if (((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) > CrossoverRate) || (mum == dad) || mum.Count <= 0 || dad.Count <= 0 || neuralNetworkSplitPoints.Count <= 0)
            {
                baby1 = mum;
                baby2 = dad;
                return;
            }

            //determine two crossover points
            int Index1 = RandomProvider.RND.Next(0, neuralNetworkSplitPoints.Count - 2);
            int Index2 = RandomProvider.RND.Next(Index1, neuralNetworkSplitPoints.Count - 1);
            int cp1 = neuralNetworkSplitPoints[Index1];
            int cp2 = neuralNetworkSplitPoints[Index2];
            //create the offspring
            for (int i = 0; i < mum.Count; ++i)
            {
                if ((i < cp1) || (i >= cp2))
                {
                    //keep the same genes if outside of crossover points
                    baby1.Add(mum[i]);
                    baby2.Add(dad[i]);
                }
                else
                {
                    //switch over the belly block
                    baby1.Add(dad[i]);
                    baby2.Add(mum[i]);
                }
            }
            return;
        }

        /// <summary>
        /// given parents and storage for the offspring this method performs
        ///	crossover according to the GAs crossover rate
        /// </summary>
        /// <param name="mum"></param>
        /// <param name="dad"></param>
        /// <param name="baby1"></param>
        /// <param name="baby2"></param>
        public void CrossoverSinglePoint(ref List<double> mum, ref List<double> dad, ref List<double> baby1, ref List<double> baby2)
        {
            if (((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) > CrossoverRate) || (mum == dad) || mum.Count <= 0 || dad.Count <= 0)
            {
                baby1 = mum;
                baby2 = dad;
                return;
            }

            int cp = RandomProvider.RND.Next(0, this.ChromosomeLength - 1);

            for (int i = 0; i < cp; i++)
            {
                baby1.Add(mum[i]);
                baby2.Add(dad[i]);
            }
            for (int i = cp; i < mum.Count; i++)
            {
                baby1.Add(dad[i]);
                baby2.Add(mum[i]);
            }
        }

        #endregion

        #region SelectionOperators

        /// <summary>
        /// This works like an advanced form of elitism by inserting NumCopies
        ///  copies of the NBest most fittest genomes into a population vector
        /// </summary>
        /// <param name="NBest"></param>
        /// <param name="numCopies"></param>
        /// <param name="source"></param>
        /// <param name="target"></param>
        public void GrabNBest(int NBest, int numCopies, ref List<Host> source, ref List<Host> target, bool isSorted = false)
        {
            IEnumerable<Host> hostToGrab;
            if (!isSorted)
                hostToGrab = source.OrderByDescending(o => o.Genome.Fitness).Take(NBest);
            else
                hostToGrab = source.Take(NBest);

            foreach (Host host in hostToGrab)
                for (int x = 0; x < numCopies; ++x)
                    target.Add(host);
        }

        #endregion

    }
}
