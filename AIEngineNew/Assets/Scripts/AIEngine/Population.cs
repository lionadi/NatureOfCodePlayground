using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AIEngine.DataStructures;
using UnityEngine;

namespace AIEngine
{
    public class Population
    {
        /// <summary>
        /// Change this value to alter how fast a problem is solved
        /// </summary>
        private int populationCount = 1;
        private Component target;
        public List<MovingHost> population;
        private List<MovingHost> matingPool;
        private int perfectScore;
        private Boolean finished;
        private int generations;
        private Vector2 screenSize = Vector2.zero;
        private int lifetime;  // How long should each generation live

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
        public Population(Component target, float mutationRate, int populationCount, int width, int height, int lifetime, Vector2 location)
        {
            this.target = target;
            this.lifetime = lifetime;
            this.mutationRate = mutationRate;
            this.populationCount = populationCount;

            this.screenSize = new Vector2(width, height);

            population = new List<MovingHost>();
            matingPool = new List<MovingHost>();
            for (int x = 0; x < this.populationCount; x++)
            {
                population.Add(new MovingHost(location, this.target, lifetime));
            }

            this.CalculateFitness();

            this.finished = false;
            this.generations = 0;
            this.perfectScore = 1;
        }

        public bool TargetReached()
        {
            for (int i = 0; i < population.Count; i++)
            {
                if (population[i].HitTarget) return true;
            }
            return false;
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

        public void Live()
        {
            for (int x = 0; x < population.Count; x++)
            {
                population[x].Run();
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
        public void Reproduction()
        {
            for (int i = 0; i < population.Count; i++)
            {
                {
                    int a = RandomProvider.RND.Next(matingPool.Count);
                    int b = RandomProvider.RND.Next(matingPool.Count);
                    // TODO: Avoid duplicates
                    MovingHost partnerA = matingPool[a];
                    MovingHost partnerB = matingPool[b];

                    IDNA child = partnerA.Dna.Crossover(partnerB.Dna);
                    child.Mutate(mutationRate);

                    population[i] = new MovingHost(new Vector2(this.screenSize.x / 2, this.screenSize.y / 2), child, this.target);
                }
            }
            this.generations++;
        }

        public int GetGenerations()
        {
            return generations;
        }

        // Find highest fintess for the population
        public MovingHost GetMaxFitness()
        {
            MovingHost returnHost = null;
            float record = 0;
            for (int i = 0; i < population.Count; i++)
            {
                if (population[i].GetFitness() > record)
                {
                    record = population[i].GetFitness();
                    returnHost = population[i];
                }
            }
            return returnHost;
        }
    }
}
