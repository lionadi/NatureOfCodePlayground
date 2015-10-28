using UnityEngine;
using System.Collections;
using System.Collections.Generic;

namespace Assets.Scripts.AI.NeuralNetworks
{
    public class Neuron
    {
        /// <summary>
        /// the number of inputs into the neuron
        /// </summary>
        public int NumberOfInputs
        {
            get; set;
        }

        /// <summary>
        /// the error value
        /// </summary>
        public double Error { get; set; }

        /// <summary>
        /// the activation of this neuron
        /// </summary>
        public double Activation { get; set; }

        /// <summary>
        /// the weights for each input
        /// </summary>
        public List<double> Weight { get; set; }
        
        /// <summary>
        /// the previous timesteps weight update used  to add momentum
        /// </summary>
        public List<double> PreviousTimeStepsUpdate { get; set; }

        /// <summary>
        /// constructor takes the number of inputs going into the neuron as
        /// an argument and creates a vector of random weights—one weight for each input.
        /// All the weights are clamped between -1 and 1.
        /// </summary>
        /// <param name="numberOfInputs"></param>
        public Neuron(int numberOfInputs)
        {
            //we need an additional weight for the bias hence the +1
            this.NumberOfInputs = numberOfInputs + 1;
            this.Weight = new List<double>();
            this.Activation = 0;
            this.Error = 0;

            this.PreviousTimeStepsUpdate = new List<double>();
            this.PreviousTimeStepsUpdate.Add(0);

            for (int i = 0; i < this.NumberOfInputs; ++i)
            {
                //set up the weights with an initial random value
                this.Weight.Add(RandomProvider.RandomClamped());
            }
        }
    }
}
