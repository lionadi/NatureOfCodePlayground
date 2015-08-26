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

            Population population = new Population(target, mutationRate, PopulationCount);
            while (!exit)
            {
                population.CalculateFitness();
                population.NaturalSelection();
                
                population.Generate();
                

                Console.WriteLine();
                Console.WriteLine(population.AllPhrases());
                Console.WriteLine("Cycle average fitness: " + population.GetAverageFitness());
                Console.WriteLine("Total generations: " + population.GetGenerations());
                Console.WriteLine("Best fitness in cycle: " + population.GetBest());

                exit = population.Finished();
            }
            Console.ReadLine();
        }
    }
}
