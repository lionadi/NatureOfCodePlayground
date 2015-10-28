using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.AI.GeneticAlgorithms
{
    public class Host
    {
        public Genome Genome { get; set; }
        public event FitnessFunctioEventHandler FitnessFunction;

        public double Fitness()
        {
            return this.Genome.Fitness;
        }

        public void SetFitness(double fitness)
        {
            this.Genome.Fitness = fitness;
        }

        public Host(int geneLength, Func<double> geneInitializationFunction)
        {
            this.Genome = new Genome(geneLength, geneInitializationFunction);
        }

        protected virtual void OnFitnessFunction(FitnessFunctionEventArgs e)
        {
            FitnessFunctioEventHandler handler = FitnessFunction;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        public void CalculateFitness()
        {
            FitnessFunctionEventArgs args = new FitnessFunctionEventArgs();
            OnFitnessFunction(args);
        }
    }

    public class FitnessFunctionEventArgs : EventArgs
    {
        
    }

    public delegate void FitnessFunctioEventHandler(Object sender, FitnessFunctionEventArgs e);
}
