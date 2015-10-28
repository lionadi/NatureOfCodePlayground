using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.AI.NeuralNetworks.NEAT
{
    /// <summary>
    /// The structure for the links is very simple. It just has pointers to the two neurons it
    /// connects and a connection weight.
    /// </summary>
    public class Link
    {
        /// <summary>
        /// pointers to the neurons this link connects 
        /// </summary>
        public Neuron Input;

        /// <summary>
        /// pointers to the neurons this link connects 
        /// </summary>
        public Neuron Output;

        /// <summary>
        /// the connection weight 
        /// </summary>
        public double Weight;

        /// <summary>
        /// is this link a recurrent link? 
        /// </summary>
        public bool Recurrent;

        public Link(double weight, Neuron input, Neuron output, bool recurrent = false)
        {
            this.Weight = weight;
            this.Input = input;
            this.Output = output;
            this.Recurrent = recurrent;
        }
    }
}
