using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;
using Assets.Scripts.AI.DataStructures;

namespace Assets.Scripts.AI.NeuralNetworks
{
    //define a type for an input or output vector(used in the training method)
    using IOList = List<double>;

    /// <summary>
    /// you have to select one of these types when updating the network 
    /// If snapshot is chosen the network depth is used to completely 
    /// flush the inputs through the network. active just updates the 
    /// network each timestep 
    /// </summary>
    enum RunType { Snapshot, Active };

    /// <summary>
    /// This is the class that creates the neural network object.
    /// </summary>
    public class NeuralNet
    {
        private int NumberOfInputsPerNeuron { get; set; }
        private int NumberOfOutputs { get; set; }
        private int NumberOfHiddenLayers { get; set; }
        private int NeuronsPerHiddenLayer { get; set; }

        /// <summary>
        /// we must specify a learning rate for backprop
        /// </summary>
        public double LearningRate;
        /// <summary>
        /// cumulative error for the network (sum (outputs - expected))
        /// </summary>
        public double ErrorSum;
        /// <summary>
        /// true if the network has been trained
        /// </summary>
        public bool Trained;

        /// <summary>
        /// set TRUE if softmax output is required 
        /// </summary>
        public bool SoftMax;

        /// <summary>
        /// epoch counter
        /// </summary>
        int NumberOfUpdateIterations;

        List<Neuron> Neurons;

        /// <summary>
        /// the depth of the network 
        /// </summary>
        int Depth;

        /// <summary>
        /// storage for each layer of neurons including the output layer
        /// </summary>
        private List<NeuronLayer> NeuronLayers { get; set; }

        public NeuralNet(int numberOfInputsPerNeuron, int numberOfOutputs, int numberOfHiddenLayers, int neuronsPerHiddenLayer, double learningRate, bool softMax = false)
        {
            this.NumberOfInputsPerNeuron = numberOfInputsPerNeuron;
            this.NumberOfOutputs = numberOfOutputs;
            this.NumberOfHiddenLayers = numberOfHiddenLayers;
            this.NeuronsPerHiddenLayer = neuronsPerHiddenLayer;
            this.SoftMax = softMax;
            this.LearningRate = learningRate;
            this.ErrorSum = 9999;
            this.Trained = false;
            this.NumberOfUpdateIterations = 0;
            this.CreateNet();
        }

        public NeuralNet(List<Neuron> neurons, int depth)
        {
            this.Neurons = neurons;
            this.Depth = depth;
        }

        /// <summary>
        /// Builds the network from Neurons. builds the
        /// neural network from Neurons gathered together in NeuronLayers
        /// </summary>
        public void CreateNet()
        {
            this.NeuronLayers = new List<NeuronLayer>();
            //this.IOData = new List<double>();
            //create the layers of the network
            if (this.NumberOfHiddenLayers > 0)
            {
                //create first hidden layer
                this.NeuronLayers.Add(new NeuronLayer(this.NeuronsPerHiddenLayer, this.NumberOfInputsPerNeuron));
                for (int i = 0; i < NumberOfHiddenLayers - 1; ++i)
                {
                    NeuronLayers.Add(new NeuronLayer(NeuronsPerHiddenLayer,
                    NeuronsPerHiddenLayer));
                }
                //create output layer
                NeuronLayers.Add(new NeuronLayer(NumberOfOutputs, NeuronsPerHiddenLayer));
            }
            else
            {
                //create output layer
                NeuronLayers.Add(new NeuronLayer(NumberOfOutputs, NumberOfInputsPerNeuron));
            }
        }

        /// <summary>
        /// randomizes all the weights to values btween 0 and 1
        /// </summary>
        public void InitializeNetwork()
        {
            //for each layer 
            for (int i = 0; i < this.NumberOfHiddenLayers + 1; ++i)
            {
                //for each neuron 
                for (int n = 0; n < this.NeuronLayers[i].NumberOfNeurons; ++n)
                {
                    //for each weight 
                    for (int k = 0; k < this.NeuronLayers[i].Neurons[n].NumberOfInputs; ++k)
                    {
                        this.NeuronLayers[i].Neurons[n].Weight[k] = RandomProvider.RandomClamped();
                    }
                }
            }

            this.ErrorSum = 9999;
            this.NumberOfUpdateIterations = 0;

            return;
        }

        /// <summary>
        /// This function creates a
        /// list of all the network weight boundaries.
        /// The constructor of a master class calls this method when it’s creating a
        /// Neural Network for an object and passes the list of split points to the genetic algorithm class.
        /// </summary>
        /// <returns></returns>
        public List<int> CalculateSplitPoints()
        {
            List<int> SplitPoints = new List<int>();
            if (SplitPoints.Count <= 0)
            {
                int WeightCounter = 0;
                //for each layer
                for (int i = 0; i < NumberOfHiddenLayers + 1; ++i)
                {
                    //for each neuron
                    for (int j = 0; j < this.NeuronLayers[i].NumberOfNeurons; ++j)
                    {
                        //for each weight
                        for (int k = 0; k < this.NeuronLayers[i].Neurons[j].NumberOfInputs; ++k)
                        {
                            ++WeightCounter;
                        }
                        SplitPoints.Add(WeightCounter - 1);
                    }
                }
            }
            return SplitPoints;
        }

        /// <summary>
        /// gets the weights for the NN
        /// </summary>
        /// <returns></returns>
        List<double> GetWeights()
        {
            //this will hold the weights
            List<double> weights = new List<double>();

            //for each layer
            for (int i = 0; i < this.NumberOfHiddenLayers + 1; ++i)
            {

                //for each neuron
                for (int j = 0; j < NeuronLayers[i].NumberOfNeurons; ++j)
                {
                    //for each weight
                    for (int k = 0; k < NeuronLayers[i].Neurons[j].NumberOfInputs; ++k)
                    {
                        weights.Add(NeuronLayers[i].Neurons[j].Weight[k]);
                    }
                }
            }

            return weights;
        }

        /// <summary>
        /// returns total number of weights in net
        /// </summary>
        /// <returns></returns>
        public int GetNumberOfWeights()
        {
            int weights = 0;

            //for each layer
            for (int i = 0; i < this.NumberOfHiddenLayers + 1; ++i)
            {

                //for each neuron
                for (int j = 0; j < NeuronLayers[i].NumberOfNeurons; ++j)
                {
                    //for each weight
                    for (int k = 0; k < NeuronLayers[i].Neurons[j].NumberOfInputs; ++k)
                        weights++;
                }
            }

            return weights;
        }

        /// <summary>
        /// replaces the weights with new ones. an epoch of the genetic algorithm has
        /// been run, the new generation of weights has to be inserted back into the neural
        /// networks.
        /// </summary>
        /// <param name="weights"></param>
        public void PutWeights(ref List<double> weights)
        {
            int cWeight = 0;

            //for each layer
            for (int i = 0; i < this.NumberOfHiddenLayers + 1; ++i)
            {

                //for each neuron
                for (int j = 0; j < NeuronLayers[i].NumberOfNeurons; ++j)
                {
                    //for each weight
                    for (int k = 0; k < NeuronLayers[i].Neurons[j].NumberOfInputs; ++k)
                    {
                        NeuronLayers[i].Neurons[j].Weight[k] = weights[cWeight];
                        cWeight++;
                    }
                }
            }

            return;
        }

        /// <summary>
        /// sigmoid response curve. Given the sum of all the inputs × weights for a neuron, this method puts them
        /// through the sigmoid activation function.
        /// </summary>
        /// <param name="activation"></param>
        /// <param name="response"></param>
        /// <returns></returns>
        public float Sigmoid(double activation, double response)
        {
            return (1 / (1 + Mathf.Exp((float)(-activation / response))));
        }

        /// <summary>
        /// given a training set this method performs one iteration of the
        /// backpropagation algorithm. The training sets comprise of series
        /// of vector inputs and a series of expected vector outputs. Returns
        /// false if there is a problem.
        /// </summary>
        /// <param name="SetIn"></param>
        /// <param name="SetOut"></param>
        /// <returns>Returns false if there is a problem </returns>
        public bool NetworkTrainingEpoch(List<IOList> SetIn, List<IOList> SetOut)
        {
            //create some iterators 
            List<double> curWeight;
            List<Neuron> curNrnOut, curNrnHid;

            double WeightUpdate = 0;

            //this will hold the cumulative error value for the training set 
            this.ErrorSum = 0;

            //run each input pattern through the network, calculate the errors and update 
            //the weights accordingly 
            for (int vec = 0; vec < SetIn.Count; ++vec)
            {
                //first run this input vector through the network and retrieve the outputs 
                List<double> outputs = this.TrainUpdate(SetIn[vec]);

                //return if error has occurred 
                if (outputs.Count == 0)
                {
                    return false;
                }

                //for each output neuron calculate the error and adjust weights 
                //accordingly 
                for (int op = 0; op < this.NumberOfOutputs; ++op)
                {
                    //first calculate the error value 
                    double err = (SetOut[vec][op] - outputs[op]) * outputs[op]
                                 * (1 - outputs[op]);

                    //keep a record of the error value 
                    this.NeuronLayers[1].Neurons[op].Error = err;

                    curWeight = this.NeuronLayers[1].Neurons[op].Weight;
                    curNrnHid = this.NeuronLayers[0].Neurons;

                    int w = 0;
                    int weightsNeuronsIndex = 0;

                    //for each weight up to but not including the bias 
                    while (weightsNeuronsIndex < curWeight.Count)
                    {
                        //calculate weight update 
                        WeightUpdate = err * this.LearningRate * curNrnHid[weightsNeuronsIndex].Activation;

                        //calculate the new weight based on the backprop rules and adding in momentum 
                        curWeight[weightsNeuronsIndex] += WeightUpdate + this.NeuronLayers[1].Neurons[op].PreviousTimeStepsUpdate[w] * NeuralNetworkParams.MOMENTUM;

                        //keep a record of this weight update 
                        this.NeuronLayers[1].Neurons[op].PreviousTimeStepsUpdate[w] = WeightUpdate;

                        ++weightsNeuronsIndex; ++w;
                    }

                    //and the bias for this neuron 
                    WeightUpdate = err * this.LearningRate * NeuralNetworkParams.Bias;

                    curWeight[weightsNeuronsIndex] += WeightUpdate + this.NeuronLayers[1].Neurons[op].PreviousTimeStepsUpdate[w] * NeuralNetworkParams.MOMENTUM;

                    //keep a record of this weight update 
                    this.NeuronLayers[1].Neurons[op].PreviousTimeStepsUpdate[w] = WeightUpdate;


                }

                //update the error total. (when this value becomes lower than a 
                //preset threshold we know the training is successful) 
                double error = 0;

                if (!this.SoftMax) //Use SSE => Sum of squared errors
                {
                    for (int o = 0; o < this.NumberOfOutputs; ++o)
                    {

                        error += (SetOut[vec][o] - outputs[o]) *
                                 (SetOut[vec][o] - outputs[o]);
                    }
                }
                else  //use cross-entropy error 
                {
                    for (int o = 0; o < this.NumberOfOutputs; ++o)
                    {
                        error += SetOut[vec][o] * Mathf.Log((float)outputs[o]);
                    }

                    error = -error;
                }

                this.ErrorSum += error;

                //**moving backwards to the hidden layer** 
                curNrnHid = this.NeuronLayers[0].Neurons;

                int n = 0;
                int hiddenLayerNeuronIndex = 0;

                //for each neuron in the hidden layer calculate the error signal 
                //and then adjust the weights accordingly 
                while (hiddenLayerNeuronIndex < curNrnHid.Count)
                {
                    double err = 0;

                    curNrnOut = this.NeuronLayers[1].Neurons;
                    int outputLayerNeuronsIndex = 0;

                    //to calculate the error for this neuron we need to iterate through 
                    //all the neurons in the output layer it is connected to and sum 
                    //the error * weights 
                    while (outputLayerNeuronsIndex != curNrnOut.Count)
                    {
                        err += curNrnOut[outputLayerNeuronsIndex].Error * curNrnOut[outputLayerNeuronsIndex].Weight[n];

                        ++outputLayerNeuronsIndex;
                    }

                    //now we can calculate the error 
                    err *= curNrnHid[hiddenLayerNeuronIndex].Activation * (1 - curNrnHid[hiddenLayerNeuronIndex].Activation);
                    int w = 0;
                    //for each weight in this neuron calculate the new weight based 
                    //on the error signal and the learning rate 
                    for (w = 0; w < this.NumberOfInputsPerNeuron; ++w)
                    {
                        WeightUpdate = err * this.LearningRate * SetIn[vec][w];

                        //calculate the new weight based on the backprop rules and adding in momentum 
                        curNrnHid[hiddenLayerNeuronIndex].Weight[w] += WeightUpdate + curNrnHid[hiddenLayerNeuronIndex].PreviousTimeStepsUpdate[w] * NeuralNetworkParams.MOMENTUM;

                        //keep a record of this weight update 
                        curNrnHid[hiddenLayerNeuronIndex].PreviousTimeStepsUpdate[w] = WeightUpdate;

                    }

                    //and the bias 
                    WeightUpdate = err * this.LearningRate * NeuralNetworkParams.Bias;

                    curNrnHid[hiddenLayerNeuronIndex].Weight[this.NumberOfInputsPerNeuron] += WeightUpdate + curNrnHid[hiddenLayerNeuronIndex].PreviousTimeStepsUpdate[w] * NeuralNetworkParams.MOMENTUM;

                    //keep a record of this weight update 
                    curNrnHid[hiddenLayerNeuronIndex].PreviousTimeStepsUpdate[w] = WeightUpdate;

                    ++hiddenLayerNeuronIndex;
                    ++n;
                }

            }//next input vector 
            return true;
        }

        /// <summary>
        /// trains the network given a training set. Returns false if  there is an error with the data sets 
        /// Given some training data in the form of a Data object this function  trains the network until the error is within acceptable limits. 
        /// </summary>
        /// <param name="data"></param>
        /// <returns>Returns false if there is a problem </returns>
        public bool Train(Data data)
        {
            List<List<double>> SetIn = data.GetInputSet();
            List<List<double>> SetOut = data.GetOutputSet();

            //first make sure the training set is valid 
            if ((SetIn.Count != SetOut.Count) ||
                (SetIn[0].Count != this.NumberOfOutputs) ||
                (SetOut[0].Count != this.NumberOfOutputs))
            {
                Debug.LogError("Inputs != Outputs");

                return false;
            }

            //initialize all the weights to small random values 
            InitializeNetwork();

            //train using backprop until the SSE is below the user defined 
            //threshold 
            while (this.ErrorSum > NeuralNetworkParams.ERROR_THRESHOLD)
            {
                //return false if there are any problems 
                if (!NetworkTrainingEpoch(SetIn, SetOut))
                {
                    return false;
                }

                ++this.NumberOfUpdateIterations;

                //call the render routine to display the error sum 
                Debug.Log("Error sum:" + this.ErrorSum);
            }

            this.Trained = true;

            return true;
        }

        /// <summary>
        /// Calculates the outputs from a set of inputs. Is the main workhorse of the neural network.
        /// The Update function then
        /// loops through each layer processing each neuron summing up the inputs×weights
        /// and calculating each neuron’s activation by putting the total through the sigmoid
        /// function.
        /// </summary>
        /// <param name="inputs"></param>
        /// <returns> Returns a list of values that correspond to the outputs from the ANN.</returns>
        public List<double> Update(List<double> inputs)
        {
            //stores the resultant outputs from each layer
            List<double> outputs = new List<double>();

            int cWeight = 0;

            //first check that we have the correct amount of inputs
            if (inputs.Count != this.NumberOfInputsPerNeuron)
            {
                //just return an empty vector if incorrect.
                return outputs;
            }

            //For each layer....
            for (int i = 0; i < this.NumberOfHiddenLayers + 1; ++i)
            {

                // NOTICE: This version of the code updates the inputs with the previous iteration outputs to be carried on to the next iteration before the ouputs of the previous iteration is emptied
                if (i > 0)
                {
                    inputs = outputs.ToList(); ;
                }

                outputs.Clear();

                cWeight = 0;

                //for each neuron sum the (inputs * corresponding weights).Throw 
                //the total at our sigmoid function to get the output.
                for (int j = 0; j < this.NeuronLayers[i].NumberOfNeurons; ++j)
                {
                    double netinput = 0;

                    int NumInputs = this.NeuronLayers[i].Neurons[j].NumberOfInputs;

                    //for each weight
                    for (int k = 0; k < NumInputs - 1; ++k)
                    {
                        //sum the weights x inputs
                        netinput += this.NeuronLayers[i].Neurons[j].Weight[k] *
                            inputs[cWeight];
                        cWeight++;
                    }

                    //add in the bias
                    /*
                        Don’t forget that the last weight in each neuron’s weight vector is the weight for the
                        bias, which as we have already discussed, is always set to -1
                        */
                    netinput += this.NeuronLayers[i].Neurons[j].Weight[NumInputs - 1] *
                          NeuralNetworkParams.Bias;

                    //we can store the outputs from each layer as we generate them. 
                    //The combined activation is first filtered through the sigmoid 
                    //function
                    outputs.Add(Sigmoid(netinput,
                                        NeuralNetworkParams.ActivationResponse));

                    cWeight = 0;
                }
            }

            return outputs;

        }

        /// <summary>
        /// Calculates the outputs from a set of inputs. Is the main workhorse of the neural network.
        /// The Update function then
        /// loops through each layer processing each neuron summing up the inputs×weights
        /// and calculating each neuron’s activation by putting the total through the sigmoid
        /// function.
        /// </summary>
        /// <param name="inputs"></param>
        /// <returns> Returns a list of values that correspond to the outputs from the ANN.</returns>
        public List<double> TrainUpdate(List<double> inputs)
        {
            //stores the resultant outputs from each layer
            List<double> outputs = new List<double>();

            int cWeight = 0;

            //first check that we have the correct amount of inputs
            if (inputs.Count != this.NumberOfInputsPerNeuron)
            {
                //just return an empty vector if incorrect.
                return outputs;
            }

            //For each layer....
            for (int i = 0; i < this.NumberOfHiddenLayers + 1; ++i)
            {

                // NOTICE: This version of the code updates the inputs with the previous iteration outputs to be carried on to the next iteration before the ouputs of the previous iteration is emptied
                if (i > 0)
                {
                    inputs = outputs.ToList(); ;
                }

                outputs.Clear();

                cWeight = 0;

                //for each neuron sum the (inputs * corresponding weights).Throw 
                //the total at our sigmoid function to get the output.
                for (int j = 0; j < this.NeuronLayers[i].NumberOfNeurons; ++j)
                {
                    double netinput = 0;

                    int NumInputs = this.NeuronLayers[i].Neurons[j].NumberOfInputs;

                    //for each weight
                    for (int k = 0; k < NumInputs - 1; ++k)
                    {
                        //sum the weights x inputs
                        netinput += this.NeuronLayers[i].Neurons[j].Weight[k] *
                            inputs[cWeight];
                        cWeight++;
                    }

                    //add in the bias
                    /*
                        Don’t forget that the last weight in each neuron’s weight vector is the weight for the
                        bias, which as we have already discussed, is always set to -1
                        */
                    netinput += this.NeuronLayers[i].Neurons[j].Weight[NumInputs - 1] *
                          NeuralNetworkParams.Bias;

                    //we can store the outputs from each layer as we generate them. 

                    //softmax on output layers 
                    if (this.SoftMax && (i == this.NumberOfHiddenLayers))
                    {
                        this.NeuronLayers[i].Neurons[j].Activation = Mathf.Exp((float)netinput);

                    }
                    else
                    {
                        //The combined activation is first filtered through the sigmoid  
                        //function and a record is kept for each neuron
                        this.NeuronLayers[i].Neurons[j].Activation = Sigmoid(netinput, NeuralNetworkParams.ActivationResponse);
                    }

                    //store the outputs from each layer as we generate them. 
                    outputs.Add(this.NeuronLayers[i].Neurons[j].Activation);

                    cWeight = 0;
                }
            }

            if (this.SoftMax)
            {
                double expTot = 0;

                //first calculate the exp for the sum of the outputs 
                for (int o = 0; o < outputs.Count; ++o)
                {
                    expTot += outputs[o];
                }

                //now adjust each output accordingly 
                for (int o = 0; o < outputs.Count; ++o)
                {
                    outputs[o] = outputs[o] / expTot;

                    this.NeuronLayers[this.NeuronLayers.Count -1].Neurons[o].Activation = outputs[o];
                }
            }

            return outputs;

        }
    }
}
/*
www.pudn.com > AI.Techniques.for.Game.Programming.rar > CNeuralNet.cpp, change:2003-11-18,size:12826b


#include "CNeuralNet.h" 
 
 
 
 
//*************************** methods for Neuron ********************** 
// 
//--------------------------------------------------------------------- 
SNeuron::SNeuron(int NumInputs): this.NumberOfInputsPerNeuron(NumInputs+1), 
                                 Activation(0), 
                                 m_dError(0) 
											 
{ 
	//we need an additional weight for the bias hence the +1 
	for (int i=0; i<NumInputs+1; ++i) 
	{ 
		//set up the weights with an initial random value 
		Weight.push_back(RandomClamped()); 
 
    PreviousTimeStepsUpdate.push_back(0); 
	} 
} 
 
 
 
 
//************************ methods for NeuronLayer ********************** 
 
//----------------------------------------------------------------------- 
//	ctor creates a layer of neurons of the required size by calling the  
//	SNeuron ctor the rqd number of times 
//----------------------------------------------------------------------- 
SNeuronLayer::SNeuronLayer(int NumNeurons,  
                           int NumInputsPerNeuron):	m_iNumNeurons(NumNeurons) 
{ 
	for (int i=0; i<NumNeurons; ++i) 
 
		Neurons.push_back(SNeuron(NumInputsPerNeuron)); 
} 
 
 
 
 
//************************ methods forCNeuralNet ************************ 
 
 
 
//------------------------------- ctor ----------------------------------- 
// 
//------------------------------------------------------------------------ 
CNeuralNet::CNeuralNet(int NumInputs, 
                       int NumOutputs, 
                       int HiddenNeurons, 
                       double LearningRate, 
                       bool   softmax = false): this.NumberOfInputsPerNeuron(NumInputs), 
                                                this.NumberOfOutputs(NumOutputs), 
                                                m_iNumHiddenLayers(1), 
                                                m_bSoftMax(softmax), 
                                                m_iNeuronsPerHiddenLyr(HiddenNeurons), 
                                                this.LearningRate(LearningRate), 
                                                m_dErrorSum(9999), 
                                                m_bTrained(false), 
                                                m_iNumEpochs(0) 
                                              
{ 
	CreateNet(); 
} 
 
//------------------------------createNet()------------------------------ 
// 
//	this method builds the ANN. The weights are all initially set to  
//	random values -1 < w < 1 
//------------------------------------------------------------------------ 
void CNeuralNet::CreateNet() 
{ 
	//create the layers of the network 
	if (m_iNumHiddenLayers > 0) 
	{ 
		//create first hidden layer 
	  this.NeuronLayers.push_back(SNeuronLayer(m_iNeuronsPerHiddenLyr, this.NumberOfInputsPerNeuron)); 
     
    for (int i=0; i<m_iNumHiddenLayers-1; ++i) 
    { 
 
			this.NeuronLayers.push_back(SNeuronLayer(m_iNeuronsPerHiddenLyr, 
                                         m_iNeuronsPerHiddenLyr)); 
    } 
 
    //create output layer 
	  this.NeuronLayers.push_back(SNeuronLayer(this.NumberOfOutputs, m_iNeuronsPerHiddenLyr)); 
	} 
 
  else 
  { 
	  //create output layer 
	  this.NeuronLayers.push_back(SNeuronLayer(this.NumberOfOutputs, this.NumberOfInputsPerNeuron)); 
  } 
} 
 
 
//--------------------------- Initialize --------------------------------- 
// 
//  randomizes all the weights to values btween 0 and 1 
//------------------------------------------------------------------------ 
void CNeuralNet::InitializeNetwork() 
{ 
	//for each layer 
	for (int i=0; i<m_iNumHiddenLayers + 1; ++i) 
	{ 
		//for each neuron 
		for (int n=0; n<this.NeuronLayers[i].m_iNumNeurons; ++n) 
		{ 
			//for each weight 
			for (int k=0; k<this.NeuronLayers[i].Neurons[n].this.NumberOfInputsPerNeuron; ++k) 
			{ 
				this.NeuronLayers[i].Neurons[n].Weight[k] = RandomClamped(); 
			} 
		} 
	} 
 
  m_dErrorSum  = 9999; 
  m_iNumEpochs = 0; 
 
	return; 
} 
 
 
//----------------------------------------------------------------------- 
vector<double> CNeuralNet::Update(vector<double> inputs) 
{  
  
  //stores the resultant outputs from each layer 
	vector<double> outputs; 
 
	int cWeight = 0; 
	 
	//first check that we have the correct amount of inputs 
	if (inputs.size() != this.NumberOfInputsPerNeuron) 
  { 
		//just return an empty vector if incorrect. 
		return outputs; 
  } 
	 
	//For each layer... 
	for (int i=0; i<m_iNumHiddenLayers + 1; ++i) 
	{ 
		 
		if ( i > 0 ) 
    { 
			inputs = outputs; 
    } 
 
		outputs.clear(); 
		 
		cWeight = 0; 
 
		//for each neuron sum the (inputs * corresponding weights).Throw  
		//the total at our sigmoid function to get the output. 
		for (int n=0; n<this.NeuronLayers[i].m_iNumNeurons; ++n) 
		{ 
			double netinput = 0.0f; 
 
			int	NumInputs = this.NeuronLayers[i].Neurons[n].this.NumberOfInputsPerNeuron; 
			 
			//for each weight 
			for (int k=0; k<NumInputs - 1; ++k) 
			{ 
				//sum the weights x inputs 
				netinput += this.NeuronLayers[i].Neurons[n].Weight[k] *  
                    inputs[cWeight++]; 
			} 
 
			//add in the bias 
			netinput += this.NeuronLayers[i].Neurons[n].Weight[NumInputs-1] *  
                  BIAS; 
 
			  
      //softmax on output layers 
      if(m_bSoftMax && (i == m_iNumHiddenLayers)) 
      { 
        this.NeuronLayers[i].Neurons[n].Activation = exp(netinput); 
         
      } 
 
      else 
      { 
        //The combined activation is first filtered through the sigmoid  
        //function and a record is kept for each neuron  
        this.NeuronLayers[i].Neurons[n].Activation = Sigmoid(netinput, ACTIVATION_RESPONSE); 
      } 
 
			//store the outputs from each layer as we generate them. 
      outputs.push_back(this.NeuronLayers[i].Neurons[n].Activation); 
 
			cWeight = 0; 
		} 
	} 
 
  if (m_bSoftMax) 
  { 
    double expTot = 0; 
 
    //first calculate the exp for the sum of the outputs 
    for (int o=0; o<outputs.size(); ++o) 
    { 
      expTot += outputs[o]; 
    }     
 
    //now adjust each output accordingly 
    for (o=0; o<outputs.size(); ++o) 
    { 
      outputs[o] = outputs[o]/expTot; 
 
      this.NeuronLayers[m_iNumHiddenLayers].Neurons[o].Activation = outputs[o];     
    } 
  } 
 
	return outputs; 
} 
//----------------------------NetworkTrainingEpoch ----------------------- 
// 
//  given a training set this method trains the network using backprop. 
//  The training sets comprise of series of input vectors and a series 
//  of output vectors. 
//  Returns false if there is a problem 
//------------------------------------------------------------------------ 
bool CNeuralNet::NetworkTrainingEpoch(vector<iovector> &SetIn, 
                                      vector<iovector> &SetOut) 
{ 
  //create some iterators 
  vector<double>::iterator  curWeight; 
  vector<SNeuron>::iterator curNrnOut, curNrnHid; 
 
  double WeightUpdate = 0; 
 
  //this will hold the cumulative error value for the training set 
  m_dErrorSum = 0; 
 
  //run each input pattern through the network, calculate the errors and update 
  //the weights accordingly 
  for (int vec=0; vec<SetIn.size(); ++vec) 
  { 
    //first run this input vector through the network and retrieve the outputs 
    vector<double> outputs = Update(SetIn[vec]); 
 
    //return if error has occurred 
    if (outputs.size() == 0) 
    { 
      return false; 
    } 
 
    //for each output neuron calculate the error and adjust weights 
    //accordingly 
    for (int op=0; op<this.NumberOfOutputs; ++op) 
    { 
      //first calculate the error value 
      double err = (SetOut[vec][op] - outputs[op]) * outputs[op] 
                   * (1 - outputs[op]);       
 
      //keep a record of the error value 
      this.NeuronLayers[1].Neurons[op].m_dError = err; 
 
      curWeight = this.NeuronLayers[1].Neurons[op].Weight.begin(); 
      curNrnHid = this.NeuronLayers[0].Neurons.begin(); 
 
      int w = 0; 
 
      //for each weight up to but not including the bias 
      while(curWeight != this.NeuronLayers[1].Neurons[op].Weight.end()-1) 
      { 
        //calculate weight update 
        WeightUpdate = err * this.LearningRate * curNrnHid.Activation; 
         
        //calculate the new weight based on the backprop rules and adding in momentum 
        *curWeight += WeightUpdate + this.NeuronLayers[1].Neurons[op].PreviousTimeStepsUpdate[w] * NeuralNetworkParams.MOMENTUM; 
 
        //keep a record of this weight update 
        this.NeuronLayers[1].Neurons[op].PreviousTimeStepsUpdate[w] = WeightUpdate; 
 
        ++curWeight; ++curNrnHid; ++w; 
      } 
 
      //and the bias for this neuron 
      WeightUpdate = err * this.LearningRate * BIAS; 
 
      *curWeight += WeightUpdate + this.NeuronLayers[1].Neurons[op].PreviousTimeStepsUpdate[w] * NeuralNetworkParams.MOMENTUM;   
 
      //keep a record of this weight update 
      this.NeuronLayers[1].Neurons[op].PreviousTimeStepsUpdate[w] = WeightUpdate; 
       
       
    } 
 
    //update the error total. (when this value becomes lower than a 
    //preset threshold we know the training is successful) 
    double error = 0; 
 
    if (!m_bSoftMax) //Use SSE 
    { 
      for (int o=0; o<this.NumberOfOutputs; ++o) 
      { 
        
        error += (SetOut[vec][o] - outputs[o]) * 
                 (SetOut[vec][o] - outputs[o]); 
      } 
    } 
 
    else  //use cross-entropy error 
    { 
      for (int o=0; o<this.NumberOfOutputs; ++o) 
      { 
        error += SetOut[vec][o] * log(outputs[o]); 
      } 
 
      error = -error; 
    } 
      
    m_dErrorSum += error; 
 
 
   //**moving backwards to the hidden layer** 
    curNrnHid = this.NeuronLayers[0].Neurons.begin(); 
 
    int n = 0; 
     
    //for each neuron in the hidden layer calculate the error signal 
    //and then adjust the weights accordingly 
    while(curNrnHid != this.NeuronLayers[0].Neurons.end()) 
    { 
      double err = 0; 
 
      curNrnOut = this.NeuronLayers[1].Neurons.begin(); 
 
      //to calculate the error for this neuron we need to iterate through 
      //all the neurons in the output layer it is connected to and sum 
      //the error * weights 
      while(curNrnOut != this.NeuronLayers[1].Neurons.end()) 
      { 
        err += curNrnOut.m_dError * curNrnOut.Weight[n]; 
 
        ++curNrnOut; 
      } 
 
      //now we can calculate the error 
      err *= curNrnHid.Activation * (1 - curNrnHid.Activation);      
       
      //for each weight in this neuron calculate the new weight based 
      //on the error signal and the learning rate 
      for (int w=0; w<this.NumberOfInputsPerNeuron; ++w) 
      { 
        WeightUpdate = err * this.LearningRate * SetIn[vec][w]; 
 
        //calculate the new weight based on the backprop rules and adding in momentum 
        curNrnHid.Weight[w] += WeightUpdate + curNrnHid.PreviousTimeStepsUpdate[w] * NeuralNetworkParams.MOMENTUM; 
         
        //keep a record of this weight update 
        curNrnHid.PreviousTimeStepsUpdate[w] = WeightUpdate; 
 
      } 
 
      //and the bias 
      WeightUpdate = err * this.LearningRate * BIAS; 
 
      curNrnHid.Weight[this.NumberOfInputsPerNeuron] += WeightUpdate + curNrnHid.PreviousTimeStepsUpdate[w] * NeuralNetworkParams.MOMENTUM; 
 
      //keep a record of this weight update 
       curNrnHid.PreviousTimeStepsUpdate[w] = WeightUpdate; 
 
      ++curNrnHid; 
      ++n; 
    } 
 
  }//next input vector 
  return true; 
} 
 
//----------------------------- Train ------------------------------------ 
// 
//  Given some training data in the form of a CData object this function 
//  trains the network until the error is within acceptable limits. 
//  
//  the HWND is required to give some graphical feedback 
//------------------------------------------------------------------------ 
bool CNeuralNet::Train(CData* data, HWND hwnd) 
{ 
  vector<vector<double> > SetIn  = data.GetInputSet(); 
  vector<vector<double> > SetOut = data.GetOutputSet(); 
 
   //first make sure the training set is valid 
   if ((SetIn.size()     != SetOut.size())  ||  
       (SetIn[0].size()  != this.NumberOfInputsPerNeuron)   || 
       (SetOut[0].size() != this.NumberOfOutputs)) 
   { 
     MessageBox(NULL, "Inputs != Outputs", "Error", NULL); 
     
     return false; 
   } 
   
   //initialize all the weights to small random values 
   InitializeNetwork(); 
 
   //train using backprop until the SSE is below the user defined 
   //threshold 
   while( m_dErrorSum > ERROR_THRESHOLD ) 
   { 
     //return false if there are any problems 
     if (!NetworkTrainingEpoch(SetIn, SetOut)) 
     { 
       return false; 
     } 
 
     ++m_iNumEpochs; 
      
     //call the render routine to display the error sum 
     InvalidateRect(hwnd, NULL, TRUE); 
		 UpdateWindow(hwnd); 
   } 
 
   m_bTrained = true; 
    
   return true; 
} 
 
 
//-------------------------------Sigmoid function------------------------- 
// 
//------------------------------------------------------------------------ 
double CNeuralNet::Sigmoid(double netinput, double response) 
{ 
	return ( 1 / ( 1 + exp(-netinput / response))); 
} 
 
 
*/
