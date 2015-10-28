using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.AI.DataStructures
{
    using DoubleList = List<double>;
    /// <summary>
    /// Class to handle the neural network training data 
    /// </summary>
    public class Data
    {


        /// <summary>
        /// This will contain the training set when created. 
        /// </summary>
        List<DoubleList> SetIn;

        /// <summary>
        /// This will contain the training set when created. 
        /// </summary>
        List<DoubleList> SetOut;

        /// <summary>
        /// the names of the gestures 
        /// </summary>
        List<string> Names;

        /// <summary>
        /// the vectors which make up the gestures 
        /// </summary>
        List<DoubleList> Patterns;

        /// <summary>
        /// number of patterns loaded into database 
        /// </summary>
        int NumberOfPatterns;

        /// <summary>
        /// size of the pattern vector 
        /// </summary>
        int TotalPatternsSize;

        /// <summary>
        /// constant training data
        /// </summary>
        public List<DoubleList> InputVectors { get; set; }

        /// <summary>
        /// adds the predefined patterns and names to Names and Patterns 
        /// </summary>
        void Init()
        {
            this.CreateConstantTrainingData();
            //for each const pattern   
            for (int ptn = 0; ptn < this.NumberOfPatterns; ++ptn)
            {
                //add it to the vector of patterns 
                List<double> temp = new List<double>();

                this.Patterns.Add(this.InputVectors[ptn]);
            }
        }

        /// <summary>
        /// Create constant training data
        /// </summary>
        void CreateConstantTrainingData()
        {
            if (this.InputVectors == null)
                this.InputVectors = new List<DoubleList>();

            this.Names = new List<string>(){
                                              "Right",
                                              "Left",
                                              "Down",
                                              "Up",
                                              "Clockwise Square",
                                              "Anti-Clockwise Square",
                                              "Right Arrow",
                                              "Left Arrow",
                                              "South West",
                                              "South East",
                                              "Zorro"

                                           };

            this.InputVectors.Add(new DoubleList() { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }); //right
            this.InputVectors.Add(new DoubleList() { -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0 }); //left
            this.InputVectors.Add(new DoubleList() { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 }); //down
            this.InputVectors.Add(new DoubleList() { 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1 }); //up

            this.InputVectors.Add(new DoubleList() { 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, -1, 0, -1, 0, -1, 0, 0, -1, 0, -1, 0, -1 }); //clockwise square
            this.InputVectors.Add(new DoubleList() { -1, 0, -1, 0, -1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, -1, 0, -1, 0, -1 }); //anticlockwise square
            this.InputVectors.Add(new DoubleList() { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, -0.45, 0.9, -0.9, 0.45, -0.9, 0.45 }); //Right Arrow
            this.InputVectors.Add(new DoubleList() { -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, 0.45, 0.9, 0.9, 0.45, 0.9, 0.45 }); //Left Arrow
            this.InputVectors.Add(new DoubleList() { -0.7, 0.7, -0.7, 0.7, -0.7, 0.7, -0.7, 0.7, -0.7, 0.7, -0.7, 0.7, -0.7, 0.7, -0.7, 0.7, -0.7, 0.7, -0.7, 0.7, -0.7, 0.7, -0.7, 0.7 }); //south west
            this.InputVectors.Add(new DoubleList() { 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7, 0.7 }); //south east
            this.InputVectors.Add(new DoubleList() { 1, 0, 1, 0, 1, 0, 1, 0, -0.72, 0.69, -0.7, 0.72, 0.59, 0.81, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }); //zorro
        }

        public Data(int numStartPatterns, int totalPatternsSize)
        {
            this.NumberOfPatterns = numStartPatterns;
            this.TotalPatternsSize = totalPatternsSize;
            Init();

            CreateTrainingSetFromData();
        }

        /// <summary>
        /// returns the name of the pattern at val 
        /// </summary>
        /// <param name="val"></param>
        /// <returns></returns>
        public string GetPatternName(int index)
        {
            if (this.Names != null && this.Names.Count > 0 && index < this.Names.Count)
                return this.Names[index];

            return String.Format("No pattern name could be found with index: {0} Or no names where present", index);
        }

        /// <summary>
        /// this adds a new pattern and pattern name to the training data. 
        /// In addition, the function automatically adds the correct amount 
        /// of dirty versions of the pattern 
        /// </summary>
        /// <param name=""></param>
        /// <param name=""></param>
        /// <param name="NewName"></param>
        /// <returns></returns>
        public bool AddData(DoubleList data, string newName)
        {
            //check that the size is correct 
            if (data.Count != NeuralNetworks.NeuralNetworkParams.NUM_VECTORS * 2)
            {

                return false;
            }

            //add the name 
            this.Names.Add(newName);

            //add the data 
            this.Patterns.Add(data);

            //keep a track of number of patterns 
            ++this.NumberOfPatterns;

            //create the new training set 
            CreateTrainingSetFromData();

            return true;
        }

        /// <summary>
        /// this function creates a training set from the data defined as 
        /// constants in CData.h. From each pattern several additional patterns 
        /// are formed by adding random noise 
        /// </summary>
        public void CreateTrainingSetFromData()
        {
            //empty the vectors 
            this.SetIn.Clear();
            this.SetOut.Clear();

            //add each pattern 
            for (int ptn = 0; ptn < this.NumberOfPatterns; ++ptn)
            {
                //add the data to the training set 
                this.SetIn.Add(this.Patterns[ptn]);

                //create the output vector for this pattern. First fill a  
                //std::vector with zeros 
                List<double> outputs = Enumerable.Repeat((double)0, this.NumberOfPatterns).ToList();

                //set the relevant output to 1 
                outputs[ptn] = 1;

                //add it to the output set 
                this.SetOut.Add(outputs);
            }
        }

        public List<DoubleList> GetInputSet() { return SetIn; }
        public List<DoubleList> GetOutputSet() { return SetOut; }

    };
        
}
