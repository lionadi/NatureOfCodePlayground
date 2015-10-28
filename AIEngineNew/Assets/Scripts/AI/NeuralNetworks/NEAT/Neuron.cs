using UnityEngine;
using System.Collections;
using System.Collections.Generic;

namespace Assets.Scripts.AI.NeuralNetworks.NEAT
{
    public class Neuron
    {
        /// <summary>
        /// all the links coming into this neuron 
        /// </summary>
        public List<Link> LinksIn;

        /// <summary>
        /// and out 
        /// </summary>
        public List<Link> LinksOut;

        /// <summary>
        /// sum of weights x inputs 
        /// </summary>
        public double SumActivation;

        /// <summary>
        /// the output from this neuron 
        /// </summary>
        public double Output;

        /// <summary>
        /// what type of neuron is this? 
        /// </summary>
        public NeuronType NeuronTypeValue;

        /// <summary>
        /// its identification number 
        /// </summary>
        public int NeuronID;

        /// <summary>
        /// sets the curvature of the sigmoid function 
        /// </summary>
        public double ActivationResponse;

        /// <summary>
        /// used in visualization of the phenotype 
        /// </summary>
        public int PosX, PosY;


        public double SplitY, SplitX;

        public Neuron(NeuronType type, int id, double splitY, double splitX, double activationResponse)
        {
            this.NeuronTypeValue = type;
            NeuronID = id;
            SumActivation = 0;
            Output = 0;
            PosX = 0;
            PosY = 0;
            SplitY = splitY;
            SplitX = splitX;
            ActivationResponse = activationResponse;

            this.LinksIn = new List<Link>();
            this.LinksOut = new List<Link>();
        }
    }
}
