using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace Assets.Scripts.AI.NeuralNetworks.NEAT
{
    public enum InnovationType
    {
        NewNeuron,
        NewLink
    };

    /// <summary>
    /// Is a container of innovation data
    /// </summary>
    public class InnovationContainer
    {
        private FieldInfo[] _FieldInfo = null;
        /// <summary>
        /// new neuron or new link? 
        /// </summary>
        public InnovationType InnovationTypevalue;

        public int InnovationID;

        public int NeuronIn;
        public int NeuronOut;

        public int NeuronID;

        public NeuronType NeuronTypeValue;

        /// <summary>
        /// if the innovation is a neuron we need to keep a record 
        /// of its position in the tree (for display purposes)
        /// </summary>
        public double SplitY, SplitX;

    public InnovationContainer(int input, int output, InnovationType innovationType, int inov_id)
        {
            NeuronIn = input;
            NeuronOut = output;
            InnovationTypevalue = innovationType;
            InnovationID = inov_id;
            NeuronID = 0;
            SplitX = 0;
            SplitY = 0;
            NeuronTypeValue = NeuronType.None;
        }
        
        public InnovationContainer(NeuronGene neuron, int innovation_id, int neuron_id)
        {
            InnovationID = innovation_id;
            NeuronID = neuron_id;
            SplitX = neuron.SplitX;
            SplitY = neuron.SplitY;
            NeuronTypeValue = neuron.NeuronType;
            NeuronIn = -1;
            NeuronOut = -1;
        }
        
        public InnovationContainer(int         input, int         output, InnovationType innovationType, int inovation_id, NeuronType neuronType, double x, double y)    
        {
            NeuronIn = input;
            NeuronOut = output;
            this.InnovationTypevalue = innovationType;
            InnovationID = inovation_id;
            NeuronID = 0;
            NeuronTypeValue = neuronType;
            SplitX = x;
            SplitY = y;
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
