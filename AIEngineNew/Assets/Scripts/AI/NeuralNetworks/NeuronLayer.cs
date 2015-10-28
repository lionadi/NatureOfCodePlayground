using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.AI.NeuralNetworks
{
    /// <summary>
    /// it defines a layer of Neurons
    /// </summary>
    public class NeuronLayer
    {
        /// <summary>
        /// the number of neurons in this layer
        /// </summary>
        public int NumberOfNeurons { get; set; }

        /// <summary>
        /// the layer of neurons
        /// </summary>
        public List<Neuron> Neurons { get; set; }

        public NeuronLayer(int numberOfNeurons, int numberOfInputs)
        {
            this.NumberOfNeurons = numberOfNeurons;
            this.Neurons = new List<Neuron>();
            for (int x = 0; x < numberOfNeurons; ++x)
            {
                this.Neurons.Add(new Neuron(numberOfInputs));
            }
        }
    }
}
