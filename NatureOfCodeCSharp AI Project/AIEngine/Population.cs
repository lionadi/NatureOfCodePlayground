using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AIEngine.DataStructures;

namespace AIEngine
{
    public class Population
    {
        /// <summary>
        /// Change this value to alter how fast a problem is solved
        /// </summary>
        private int populationCount = 1000;
        private String target = "TO BE OR NOT TO BE";
        private List<DNA> population;
        private List<DNA> matingPool;
        private int perfectScore;
        private Boolean finished;
        private int generations;

        /// <summary>
        /// Change this value to alter how fast a problem is solved
        /// </summary>
        private float mutationRate = 0.01F; // This value of 0.01 with a population count of 1000 seems to be generating the fastest result with monte carlo mating

        /// <summary>
        /// 
        /// </summary>
        /// <param name="target"></param>
        /// <param name="mutationRate"></param>
        /// <param name="populationCount"></param>
        public Population(String target, float mutationRate, int populationCount)
        {
            this.target = target;
            this.mutationRate = mutationRate;
            this.populationCount = populationCount;

            population = new List<DNA>();
            matingPool = new List<DNA>();
            for (int x = 0; x < this.populationCount; x++)
            {
                population.Add(new DNA(target.Length, target.ToUpper()));
            }

            this.CalculateFitness();

            this.finished = false;
            this.generations = 0;
            this.perfectScore = 1;
        }

        /// <summary>
        /// In each iteration we calculate the fitness of each DNA sequence to be used later in the algorithm logic
        /// </summary>
        public void CalculateFitness()
        {
            for (int x = 0; x < population.Count; x++)
            {
                population[x].EvalutateFitness();
            }
        }

        /// <summary>
        /// Here the algorithm implements a selection method for chosing the best DNA sequences from the population.
        /// </summary>
        public void NaturalSelection()
        {
            bool duplicateFound = true;
            matingPool.Clear();

            for (int x = 0; x < population.Count; x++)
            {
                //while (duplicateFound)
                {
                    // Monte carlo method(Faster than the below commented approach)
                    int a = RandomProvider.RND.Next(population.Count);
                    int b = RandomProvider.RND.Next(population.Count);

                    int populationIndexChosen = -1;

                    if (population[a].Fitness > population[b].Fitness)
                    {
                        populationIndexChosen = a;
                    }
                    else
                    {
                        populationIndexChosen = b;
                    }

                    matingPool.Add(population[populationIndexChosen]);

                    //if (!matingPool.Exists( o => o.ToString() == population[populationIndexChosen].ToString()))
                    //{
                    //    matingPool.Add(population[populationIndexChosen]);
                    //    duplicateFound = false;
                    //}

                    //int n = (int)(population[x].Fitness * 100);
                    //for (int j = 0; j < n; j++)
                    //{

                    //    matingPool.Add(population[x]);
                    //}
                }
            }
        }

        /// <summary>
        /// Next we will generate a new population based on algorithmic logic of crossover between two random DNA sequences and adding some mutation into it.
        /// </summary>
        public void Generate()
        {
            for (int i = 0; i < population.Count; i++)
            {
                {
                    int a = RandomProvider.RND.Next(matingPool.Count);
                    int b = RandomProvider.RND.Next(matingPool.Count);
                    // TODO: Avoid duplicates
                    DNA partnerA = matingPool[a];
                    DNA partnerB = matingPool[b];

                    DNA child = (DNA)partnerA.Crossover(partnerB);
                    child.Mutate(mutationRate);
                    child.EvalutateFitness();
                    population[i] = child;
                }
            }
            this.generations++;
        }

        public String GetBest()
        {
            float worldrecord = 0.0F;
            int index = 0;
            for (int i = 0; i < population.Count; i++)
            {
                if (population[i].Fitness > worldrecord)
                {
                    index = i;
                    worldrecord = population[i].Fitness;
                }
            }

            if (worldrecord == perfectScore) finished = true;
            return population[index].ToString();
        }

        public Boolean Finished()
        {
            return this.finished;
        }

        public int GetGenerations()
        {
            return generations;
        }

        // Compute average fitness for the population
        public float GetAverageFitness()
        {
            float total = 0;
            for (int i = 0; i < population.Count; i++)
            {
                total += population[i].Fitness;
            }
            return total / (population.Count);
        }

        public String AllPhrases()
        {
            StringBuilder everything = new StringBuilder();

            for (int i = population.Count -1; i > population.Count - 11; i--)
            {
                everything.AppendLine(population[i].ToString());
            }
            return everything.ToString();
        }
    }
}
