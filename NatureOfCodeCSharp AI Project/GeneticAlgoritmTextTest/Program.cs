using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AIEngine.DataStructures;
using AIEngine;

namespace GeneticAlgoritmTextTest
{
    class Program
    {
        /// <summary>
        /// Change this value to alter how fast a problem is solved
        /// </summary>
        public static int PopulationCount = 1000;
        public static String target = "TO BE OR NOT TO BE";

        /// <summary>
        /// Change this value to alter how fast a problem is solved
        /// </summary>
        public static float mutationRate = 0.01F;
        static void Main(string[] args)
        {
            bool exit = false;

            // Create the population which is responsible for solving the problem.
            Population population = new Population(target, mutationRate, PopulationCount);
            while (!exit)
            {
                // In each iteration we calculate the fitness of each DNA sequence to be used later in the algorithm logic
                population.CalculateFitness();
                // Here the algorithm implements a selection method for chosing the best DNA sequences from the population.
                population.NaturalSelection();
                // Next we will generate a new population based on algorithmic logic of crossover between two random DNA sequences and adding some mutation into it.
                population.Generate();
                

                Console.WriteLine();
                Console.WriteLine(population.AllPhrases());
                Console.WriteLine("Cycle average fitness: " + population.GetAverageFitness());
                Console.WriteLine("Total generations: " + population.GetGenerations());
                Console.WriteLine("Best fitness in cycle: " + population.GetBest());

                // And before we go to the next iteration we check to see if the text puzzle has been solved.
                exit = population.Finished();
            }
            Console.ReadLine();
        }
    }
}
