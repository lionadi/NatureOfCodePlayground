using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.AI.NeuralNetworks.NEAT
{
    public enum NeuronType
    {
        Input,
        Hidden,
        Output,
        Bias,
        None
    };

    /// <summary>
    /// this structure defines a neuron gene
    /// The neuron defined by Neuron contains much more information than its little
    /// brother NeuronGene.In addition, it holds the values for the sum of all the inputs ×
    /// weights, this value after it’s been put through the activation function (in other
    /// words, the output from this neuron), and two list —one for storing the
    /// links into the neuron, and the other for storing the links out of the neuron.
    /// </summary>
    public class NeuronGene
    {
        /// <summary>
        /// its identification 
        /// </summary>
        public int ID;

        /// <summary>
        /// its type 
        /// </summary>
        public NeuronType NeuronType;

        /// <summary>
        /// is it recurrent, pointing to itself
        /// </summary>
        public bool Recurrent;

        /// <summary>
        /// sets the curvature of the sigmoid function 
        /// </summary>
        public double ActivationResponse;

        /// <summary>
        /// position in network grid 
        /// </summary>
        public double SplitY, SplitX;

        public NeuronGene(NeuronType type, int id, double y, double x, bool r = false)
        {
            this.ID = id;
            this.SplitY = y;
            this.SplitX = x;
            this.Recurrent = r;
            this.NeuronType = type;
        }
    }
}
