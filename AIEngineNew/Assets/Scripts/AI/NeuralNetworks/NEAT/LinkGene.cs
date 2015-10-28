using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace Assets.Scripts.AI.NeuralNetworks.NEAT
{
    /// <summary>
    /// this structure defines a link gene 
    /// </summary>
    public class LinkGene
    {
        /// <summary>
        /// the IDs of the two neurons this link connects: A.K.A Input Neuron		 
        /// </summary>
        public int FromNeuron;

        /// <summary>
        /// the IDs of the two neurons this link connects: A.K.A Ouput Neuron	 
        /// </summary>
        public int ToNeuron;

        public double Weight;

        /// <summary>
        /// flag to indicate if this link is currently enabled or not 
        /// </summary>
        public bool Enabled;

        /// <summary>
        /// flag to indicate if this link is recurrent or not 
        /// </summary>
        public bool Recurrent;

        public int InnovationID;

        private FieldInfo[] _FieldInfo = null;

        public LinkGene(int inputFromNeuron, int outputToNeuron, bool enable, int tag, double weight, bool recurrent = false)
        {
            this.Enabled = enable;
            this.InnovationID = tag;
            this.FromNeuron = inputFromNeuron;
            this.ToNeuron = outputToNeuron;
            this.Weight = weight;
            this.Recurrent = recurrent;
        }

        public bool IsSmallerThan(LinkGene linkGene)
        {
            return this.InnovationID < linkGene.InnovationID;
        }

        public override string ToString()
        {
            if (_FieldInfo == null)
                _FieldInfo = this.GetType().GetFields();

            var sb = new StringBuilder();

            foreach (var info in _FieldInfo)
            {
                var value = info.GetValue(this) ?? "(null)";
                sb.AppendFormat(" {0} : {1}", info.Name, value.ToString());
            }

            return sb.ToString();
        }

    }
}
