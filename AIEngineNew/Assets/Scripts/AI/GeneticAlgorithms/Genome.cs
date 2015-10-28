using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;
using Assets.Scripts.Constants;

namespace Assets.Scripts.AI.GeneticAlgorithms
{
    public class Genome
    {
        public List<double> Chromosomes;
        public List<int> SplitPoints;
        public double Fitness { get; set; }
        
        /// <summary>
        /// Create a genome and initialize the genes with a given anonymous function.
        /// </summary>
        /// <param name="chromosomesCount"></param>
        /// <param name="geneInitializationFunction">NOTICE: That you must provice an anonymous function which will be called for every gene when created.</param>
        public Genome(int chromosomesCount, Func<double> geneInitializationFunction)
        {
            this.InitializeGenes(chromosomesCount, geneInitializationFunction);
        }

        private void InitializeGenes(int genesCount, Func<double> geneInitializationFunction)
        {
            // Initialize the fitness to zero only and only if it is a numeric value
            //if(this.Fitness.IsNumericType())
                //this.Fitness = (T)Convert.ChangeType(0, typeof(T));

            this.Chromosomes = new List<double>();
            if (genesCount < 0)
                throw new Exception("The genesCount must be larger than 0");
            else if (genesCount == 0)
                return;

            int index = 0;
            do
            {
                this.Chromosomes.Add(geneInitializationFunction());
                index++;
            } while (index < genesCount);
        }

        public bool IsGreaterThan(ref Genome genome)
        {
            if(this.Fitness > genome.Fitness)
                return true;

            return false;
        }

    }
}
