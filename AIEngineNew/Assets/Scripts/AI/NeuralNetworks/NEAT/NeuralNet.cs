using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;
using Assets.Scripts.AI.DataStructures;

namespace Assets.Scripts.AI.NeuralNetworks.NEAT
{
    //define a type for an input or output vector(used in the training method)
    using IOList = List<double>;

    /// <summary>
    /// you have to select one of these types when updating the network 
    /// If snapshot is chosen the network depth is used to completely 
    /// flush the inputs through the network. active just updates the 
    /// network each timestep 
    /// </summary>
    public enum RunType { Snapshot, Active };

    /// <summary>
    /// This is the class that creates the neural network object.
    /// Up until now, all the networks you’ve seen have run the inputs through the complete
    /// network, layer by layer, until an output is produced.With NEAT however, a
    /// network can assume any topology with connections between neurons leading
    /// backward, forward, or even looping back on themselves.This makes it next to
    /// mpossible to use a layer-based update function because there aren’t really any
    /// layers! Because of this, the NEAT update function runs in one of two modes:
    /// 
    /// active: When using the active update mode, each neuron adds up all the activations
    /// calculated during the preceeding time-step from all its incoming neurons.This means
    /// that the activation values, instead of being flushed through the entire network like a
    /// conventional ANN each time-step, only travel from one neuron to the next. To get
    /// the same result as a layer-based method, this process would have to be repeated as
    /// many times as the network is deep in order to flush all the neuron activations
    /// completely through the network.This mode is appropriate to use if you are using
    /// the network dynamically(like for controlling the minesweepers for instance).
    /// 
    /// snapshot: If, however, you want NEAT’s update function to behave like a regular
    /// neural network update function, you have to ensure that the activations are flushed
    /// all the way through from the input neurons to the output neurons.To facilitate this,
    /// snapshot: If, however, you want NEAT’s update function to behave like a regular
    /// neural network update function, you have to ensure that the activations are flushed
    /// all the way through from the input neurons to the output neurons.To facilitate this,
    /// Update iterates through all the neurons as many times as the network is deep before
    /// spitting out the output. This is why calculating those splitY values was so important.
    /// You would use this type of update if you were to train a NEAT network using a
    /// training set. (Like “A Supervised Training Approach”).
    /// Here is the code for CNeuralNet::Update, which
    /// </summary>
    public class NeuralNet
    {
       

        List<Neuron> Neurons;
        

        /// <summary>
        /// the depth of the network 
        /// </summary>
        int Depth;

        
        public NeuralNet(List<Neuron> neurons, int depth)
        {
            this.Neurons = neurons;
            this.Depth = depth;
            
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
            var value = activation;
            if (response != 0)
            {
                value = -activation / response;
            }

            return (1 / (1 + Mathf.Exp((float)(value))));
        }



        /// <summary>
        /// takes a list of doubles as inputs into the network then steps through  
        ///  the neurons calculating each neurons next output. 
        /// 
        ///	. 
        /// </summary>
        /// <param name="inputs"></param>
        /// <returns> finally returns a list of doubles as the output from the net</returns>
        public List<double> Update(List<double> inputs, RunType type)
        {
            //create a vector to put the outputs into 
            List<double> outputs = new List<double>();

            //if the mode is snapshot then we require all the neurons to be 
            //iterated through as many times as the network is deep. If the  
            //mode is set to active the method can return an output after 
            //just one iteration 
            int FlushCount = 0;

            if (RunType.Snapshot == type)
            {
                FlushCount = this.Depth;
            }
            else
            {
                FlushCount = 1;
            }

            //iterate through the network FlushCount times 
            for (int i = 0; i < FlushCount; ++i)
            {
                //clear the output vector 
                outputs.Clear();

                //this is an index into the current neuron 
                int cNeuron = 0;

                //first set the outputs of the 'input' neurons to be equal 
                //to the values passed into the function in inputs 
                while (this.Neurons[cNeuron].NeuronTypeValue == NeuronType.Input)
                {
                    this.Neurons[cNeuron].Output = inputs[cNeuron];

                    ++cNeuron;
                }

                //set the output of the bias to 1 
                this.Neurons[cNeuron++].Output = 1;

                //then we step through the network a neuron at a time 
                while (cNeuron < this.Neurons.Count)
                {
                    //this will hold the sum of all the inputs x weights  
                    double sum = 0;

                    //sum this neuron's inputs by iterating through all the links into 
                    //the neuron 
                    for (int lnk = 0; lnk < this.Neurons[cNeuron].LinksIn.Count; ++lnk)
                    {
                        //get this link's weight 
                        double Weight = this.Neurons[cNeuron].LinksIn[lnk].Weight;

                        //get the output from the neuron this link is coming from 
                        double NeuronOutput =
                        this.Neurons[cNeuron].LinksIn[lnk].Input.Output;

                        //add to sum 
                        sum += Weight * NeuronOutput;
                    }

                    //now put the sum through the activation function and assign the  
                    //value to this neuron's output 
                    this.Neurons[cNeuron].Output =
                    Sigmoid(sum, this.Neurons[cNeuron].ActivationResponse);
                    if(double.IsNaN(this.Neurons[cNeuron].Output))
                    {
                        int yyy = 0;
                    }

                    if (this.Neurons[cNeuron].NeuronTypeValue== NeuronType.Output)
                    {
                        //add to our outputs 
                        outputs.Add(this.Neurons[cNeuron].Output);
                    }

                    //next neuron 
                    ++cNeuron;
                }

            }//next iteration through the network 

            //the network needs to be flushed if this type of update is performed 
            //otherwise it is possible for dependencies to be built on the order 
            //the training data is presented 
            if (type == RunType.Snapshot)
            {
                for (int n = 0; n < this.Neurons.Count; ++n)
                {
                    this.Neurons[n].Output = 0;
                }
            }

            //return the outputs 
            return outputs;

        }

        /// <summary>
        /// This is a fix to prevent neurons overlapping when they are displaye
        /// </summary>
        /// <param name=""></param>
        /// <param name=""></param>
        void TidyXSplits(List<Neuron> neurons)
        {
            //stores the index of any neurons with identical splitY values 
            List<int> SameLevelNeurons = new List<int>();

            //stores all the splitY values already checked
            List<double> DepthsChecked = new List<double>();


            //for each neuron find all neurons of identical ySplit level
            for (int n = 0; n < neurons.Count; ++n)
            {
                double ThisDepth = neurons[n].SplitY;

                //check to see if we have already adjusted the neurons at this depth
                bool bAlreadyChecked = false;

                for (int i = 0; i < DepthsChecked.Count; ++i)
                {
                    if (DepthsChecked[i] == ThisDepth)
                    {
                        bAlreadyChecked = true;

                        break;
                    }
                }

                //add this depth to the depths checked.
                DepthsChecked.Add(ThisDepth);

                //if this depth has not already been adjusted
                if (!bAlreadyChecked)
                {
                    //clear this storage and add the neuron's index we are checking
                    SameLevelNeurons.Clear();
                    SameLevelNeurons.Add(n);

                    //find all the neurons with this splitY depth
                    for (int i = n + 1; i < neurons.Count; ++i)
                    {
                        if (neurons[i].SplitY == ThisDepth)
                        {
                            //add the index to this neuron
                            SameLevelNeurons.Add(i);
                        }
                    }

                    //calculate the distance between each neuron
                    double slice = 1.0 / (SameLevelNeurons.Count + 1);


                    //separate all neurons at this level
                    for (int i = 0; i < SameLevelNeurons.Count; ++i)
                    {
                        int idx = SameLevelNeurons[i];

                        neurons[idx].SplitX = (i + 1) * slice;
                    }
                }

            }//next neuron to check

        }


        public void DrawNet(Vector3 maxScreenTopRight, Vector3 minScreenBottomLeft,List<GameObject> VisibleUnityNeurons)
        {
            

            
                
            //Vector3 maxScreenBottomRight = targetCamera.ScreenToWorldPoint(new Vector3(targetCamera.pixelWidth, targetCamera.pixelHeight, targetCamera.transform.position.z));
            //Vector3 minScreenTopLeft = targetCamera.ScreenToWorldPoint(new Vector3(0,0, targetCamera.transform.position.z));
            //var yyt = new Cell(maxScreenBottomRight.y, minScreenTopLeft.y, minScreenTopLeft.x, maxScreenBottomRight.x);

            int Left = (int)minScreenBottomLeft.x;
            int Right = (int)maxScreenTopRight.x;
            int Top = (int)maxScreenTopRight.y;
            int Bottom = (int)minScreenBottomLeft.y;

            float lineVisibleTime = NeuralNetworkParams.NumTicks / 100;
            if (lineVisibleTime < 2)
                lineVisibleTime = 2;
            //the border width
            const int border = 1;

            //max line thickness
            const int MaxThickness = 2;

            TidyXSplits(this.Neurons);

            //go through the neurons and assign x/y coords
            int spanX = Right - Left;
            int spanY = Top - Bottom;
            spanX = (int)(spanX * 0.5f);
            spanY = (int)(spanY * 0.5f);

            for (int cNeuron = 0; cNeuron < this.Neurons.Count; ++cNeuron)
            {
                this.Neurons[cNeuron].PosX = (int)((double)Left + (double)spanX * this.Neurons[cNeuron].SplitX);
                this.Neurons[cNeuron].PosY = -1 * (int)((Top - border) - ((double)spanY * this.Neurons[cNeuron].SplitY));
            }

            //create some pens and brushes to draw with
            //HPEN GreyPen  = CreatePen(PS_SOLID, 1, RGB(200, 200, 200));
            //HPEN RedPen   = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            //HPEN GreenPen = CreatePen(PS_SOLID, 1, RGB(0, 200, 0));
            //HPEN OldPen   = NULL;

            ////create a solid brush
            //HBRUSH RedBrush = CreateSolidBrush(RGB(255, 0, 0));
            //HBRUSH OldBrush = NULL;

            //OldPen =   (HPEN)  SelectObject(surface, RedPen);
            //OldBrush = (HBRUSH)SelectObject(surface, GetStockObject(HOLLOW_BRUSH));

            Color GreyPen = Color.grey;
            Color RedPen = Color.red;
            Color GreenPen = Color.green;
            Color OldPen = Color.black;

            //radius of neurons
            int radNeuron = spanX / 60;
            int radLink = (int)((double)radNeuron * 1.5);

            //now we have an X,Y pos for every neuron we can get on with the
            //drawing. First step through each neuron in the network and draw
            //the links
            for (int cNeuron = 0; cNeuron < this.Neurons.Count; ++cNeuron)
            {
                //grab this neurons position as the start position of each
                //connection
                int StartX = this.Neurons[cNeuron].PosX;
                int StartY = this.Neurons[cNeuron].PosY;
                Color penColor = Color.green;

                //is this a bias neuron? If so, draw the link in green
                bool bBias = false;

                if (this.Neurons[cNeuron].NeuronTypeValue == NeuronType.Bias)
                {
                    bBias = true;
                }

                //now iterate through each outgoing link to grab the end points
                for (int cLnk = 0; cLnk < this.Neurons[cNeuron].LinksOut.Count; ++cLnk)
                {
                    int EndX = this.Neurons[cNeuron].LinksOut[cLnk].Output.PosX;
                    int EndY = this.Neurons[cNeuron].LinksOut[cLnk].Output.PosY;

                    //if link is forward draw a straight line
                    if ((!this.Neurons[cNeuron].LinksOut[cLnk].Recurrent) && !bBias)
                    {
                        int thickness = (int)(Mathf.Abs((float)this.Neurons[cNeuron].LinksOut[cLnk].Weight));

                        Mathf.Clamp(thickness, 0, MaxThickness);

                        //HPEN Pen;

                        //create a yellow pen for inhibitory weights
                        if (this.Neurons[cNeuron].LinksOut[cLnk].Weight <= 0)
                        {
                            //Pen  = CreatePen(PS_SOLID, thickness, RGB(240, 230, 170));
                            penColor = Color.yellow;
                        }

                        //grey for excitory
                        else
                        {
                            //Pen  = CreatePen(PS_SOLID, thickness, RGB(200, 200, 200));
                            penColor = Color.magenta;
                        }
                        
                        Debug.DrawLine(new Vector3(StartX, StartY), new Vector3(EndX, EndY), penColor, lineVisibleTime);
                        //HPEN tempPen = (HPEN)SelectObject(surface, Pen);

                        ////draw the link
                        //MoveToEx(surface, StartX, StartY, NULL);
                        //LineTo(surface, EndX, EndY);

                        //SelectObject(surface, tempPen);

                        //DeleteObject(Pen);
                    }
                    else if ((!this.Neurons[cNeuron].LinksOut[cLnk].Recurrent) && bBias)
                    {
                        Debug.DrawLine(new Vector3(StartX, StartY), new Vector3(EndX, EndY), GreenPen, lineVisibleTime);
                        //SelectObject(surface, GreenPen);

                        ////draw the link
                        //MoveToEx(surface, StartX, StartY, NULL);
                        //LineTo(surface, EndX, EndY);
                    } // ENF OF 
                    //recurrent link draw in red
                    else
                    {
                        if ((StartX == EndX) && (StartY == EndY))
                        {

                            int thickness = (int)(Mathf.Abs((float)this.Neurons[cNeuron].LinksOut[cLnk].Weight));

                            Mathf.Clamp(thickness, 0, MaxThickness);

                            //HPEN Pen;

                            //blue for inhibitory
                            if (this.Neurons[cNeuron].LinksOut[cLnk].Weight <= 0)
                            {
                                //Pen  = CreatePen(PS_SOLID, thickness, RGB(0,0,255));
                                penColor = Color.blue;
                            }

                            //red for excitory
                            else
                            {
                                //Pen  = CreatePen(PS_SOLID, thickness, RGB(255, 0, 0));
                                penColor = Color.red;
                            }

                            //HPEN tempPen = (HPEN)SelectObject(surface, Pen);

                            //we have a recursive link to the same neuron draw an ellipse
                            int x = this.Neurons[cNeuron].PosX;
                            int y = (int)(this.Neurons[cNeuron].PosY - (1.5 * (double)radNeuron));

                            VisibleUnityNeurons.Add(GameObject.CreatePrimitive(PrimitiveType.Capsule));
                            VisibleUnityNeurons[VisibleUnityNeurons.Count - 1].transform.position = new Vector3(x, y);
                            VisibleUnityNeurons[VisibleUnityNeurons.Count - 1].transform.localScale *= 0.5F;
                            // TODO SET NEURON COLOR
                            //this.VisibleUnityNeurons[VisibleUnityNeurons.Count - 1].GetComponent<Renderer>.penColor = penColor;
                            //Ellipse(surface, x-radLink, y-radLink, x+radLink, y+radLink);

                            //SelectObject(surface, tempPen);

                            //DeleteObject(Pen);
                        } // END OF - recurrent link draw in red
                        else
                        {
                            int thickness = (int)(Mathf.Abs((float)this.Neurons[cNeuron].LinksOut[cLnk].Weight));

                            Mathf.Clamp(thickness, 0, MaxThickness);

                            //HPEN Pen;

                            //blue for inhibitory
                            if (this.Neurons[cNeuron].LinksOut[cLnk].Weight <= 0)
                            {
                                //Pen  = CreatePen(PS_SOLID, thickness, RGB(0,0,255));
                                penColor = Color.blue;
                            }

                            //red for excitory
                            else
                            {
                                //Pen  = CreatePen(PS_SOLID, thickness, RGB(255, 0, 0));
                                penColor = Color.red;
                            }

                            Debug.DrawLine(new Vector3(StartX, StartY), new Vector3(EndX, EndY), penColor, lineVisibleTime);
                            //HPEN tempPen = (HPEN)SelectObject(surface, Pen);

                            ////draw the link
                            //MoveToEx(surface, StartX, StartY, NULL);
                            //LineTo(surface, EndX, EndY);

                            //SelectObject(surface, tempPen);

                            //DeleteObject(Pen);
                        }
                    }

                } // ENF OF FOR - outgoing link end points
            } // END OF WHILE - step through each neuron in the network and draw the links

            //now draw the neurons and their IDs
            //SelectObject(surface, RedBrush);
            //SelectObject(surface, GetStockObject(BLACK_PEN));

            for (int cNeuron = 0; cNeuron < this.Neurons.Count; ++cNeuron)
            {
                int x = this.Neurons[cNeuron].PosX;
                int y = this.Neurons[cNeuron].PosY;
                //display the neuron
                VisibleUnityNeurons.Add(GameObject.CreatePrimitive(PrimitiveType.Sphere));
                VisibleUnityNeurons[VisibleUnityNeurons.Count - 1].transform.position = new Vector3(x, y);
                VisibleUnityNeurons[VisibleUnityNeurons.Count - 1].transform.localScale *= 0.5F;
                
                //Ellipse(surface, x-radNeuron, y-radNeuron, x+radNeuron, y+radNeuron); 
            }

            //cleanup
            //SelectObject(surface, OldPen);
            //SelectObject(surface, OldBrush);

            //DeleteObject(RedPen);
            //DeleteObject(GreyPen);
            //DeleteObject(GreenPen);
            //DeleteObject(OldPen);
            //DeleteObject(RedBrush);
            //DeleteObject(OldBrush);
        }


    }
}
