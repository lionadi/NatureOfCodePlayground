using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace Assets.Scripts.AI.NeuralNetworks.NEAT
{
    /// <summary>
    /// Innovation class used to keep track of all innovations created during the populations evolution
    /// </summary>
    public class Innovation
    {
        private FieldInfo[] _FieldInfo = null;
        List<InnovationContainer> Innovations;

        int NextNeuronID;

        int NextInnovationNumber;

        /// <summary>
        /// given a series of start genes and start neurons this ctor adds all the appropriate innovations
        /// </summary>
        /// <param name="start_genes"></param>
        /// <param name="start_neurons"></param>
        public Innovation(List<LinkGene> start_genes, List<NeuronGene> start_neurons)
        {
            this.NextNeuronID = 0;
            this.NextInnovationNumber = 0;

            this.Innovations = new List<InnovationContainer>();

            //add the neurons 
            for (int nd = 0; nd < start_neurons.Count; ++nd)
            {
                this.Innovations.Add(new InnovationContainer(start_neurons[nd],
                                                  this.NextInnovationNumber++,
                                                  this.NextNeuronID++));
            }

            //add the links 
            for (int cGen = 0; cGen < start_genes.Count; ++cGen)
            {
                InnovationContainer NewInnov = new InnovationContainer(start_genes[cGen].FromNeuron,
                                 start_genes[cGen].ToNeuron,
                                 InnovationType.NewLink,
                                 this.NextInnovationNumber);

            this.Innovations.Add(NewInnov);

            ++this.NextInnovationNumber;

        }
    }

        /// <summary>
        /// checks to see if this innovation has already occurred. If it has it returns the innovation ID. If not it returns a negative value. 
        /// </summary>
        /// <param name="input"></param>
        /// <param name="output"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        public int CheckInnovation(int input, int output, InnovationType type)
        {
            //iterate through the innovations looking for a match on all 
            //three parameters 
            for (int inv = 0; inv < this.Innovations.Count; ++inv)
            {
                if ((this.Innovations[inv].NeuronIn == input)   && (this.Innovations[inv].NeuronOut == output) && (this.Innovations[inv].InnovationTypevalue == type)) 
		        {
                    //found a match so assign this innovation number to id 
                    return this.Innovations[inv].InnovationID;
                }
            }

            //if no match return a negative value 
            return -1;
        }

        /// <summary>
        /// creates a new innovation and returns its ID 
        /// </summary>
        /// <param name="input"></param>
        /// <param name="output"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        public int CreateNewInnovation(int input, int output, InnovationType type)
        {
            InnovationContainer new_innov = new InnovationContainer(input, output, type, this.NextInnovationNumber);

            if (type == InnovationType.NewNeuron)
            {
                new_innov.NeuronID = this.NextNeuronID;

                ++this.NextNeuronID;
            }

            this.Innovations.Add(new_innov);

            ++this.NextInnovationNumber;

            return (this.NextNeuronID - 1);
        }

        /// <summary>
        /// as above but includes adding x/y position of new neuron 
        /// </summary>
        /// <param name="from"></param>
        /// <param name="to"></param>
        /// <param name="InnovType"></param>
        /// <param name="NeuronType"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public int CreateNewInnovation(int from,
                                  int to,
                                  InnovationType innovType,
                                  NeuronType neuronType,
                                  double x,
                                  double y)
        {
            InnovationContainer new_innov = new InnovationContainer(from, to, innovType, this.NextInnovationNumber, neuronType, x, y);

            if (innovType == InnovationType.NewNeuron)
            {
                new_innov.NeuronID = this.NextNeuronID;

                ++this.NextNeuronID;
            }

            this.Innovations.Add(new_innov);

            ++this.NextInnovationNumber;

            return (this.NextNeuronID - 1);
        }

        /// <summary>
        /// creates a BasicNeuron from the given neuron ID, given a neuron ID this function returns a clone of that neuron
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public NeuronGene CreateNeuronFromID(int neuronID)
        {
            NeuronGene temp = new NeuronGene(NeuronType.Hidden,0, 0, 0);

            for (int inv = 0; inv < this.Innovations.Count; ++inv)
            {
                if (this.Innovations[inv].NeuronID == neuronID)
                {
                    temp.NeuronType = this.Innovations[inv].NeuronTypeValue;
                    temp.ID = this.Innovations[inv].NeuronID;
                    temp.SplitY = this.Innovations[inv].SplitY;
                    temp.SplitX = this.Innovations[inv].SplitX;

                    return temp;
                }
            }

            return temp;
        }


        //------------------------------------------------accessor methods 
        public int GetNeuronID(int inv)
        {
            return this.Innovations[inv].NeuronID;
        }

        public void Flush() { this.Innovations.Clear(); return; }

        public int NextNumber(int num = 0)
        {
            this.NextInnovationNumber += num;

            return this.NextInnovationNumber;
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
