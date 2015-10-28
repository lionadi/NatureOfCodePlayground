using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;
using System.Reflection;

namespace Assets.Scripts.AI.NeuralNetworks.NEAT
{
    /// <summary>
    ///  CGenome class definition. A genome basically consists of a vector of  link genes, a vector of neuron genes and a fitness score. 
    /// </summary>
    public class Genome
    {
        /// <summary>
        /// its identification number 
        /// </summary>
        int GenomeID;

        /// <summary>
        /// all the neurons which make up this genome 
        /// </summary>
        public List<NeuronGene> Neurons;

        /// <summary>
        /// and all the the links 
        /// </summary>
        public List<LinkGene> Links;

        /// <summary>
        /// pointer to its phenotype 
        /// </summary>
        NeuralNet Phenotype;

        /// <summary>
        /// its raw fitness score 
        /// </summary>
        public double Fitness;

        /// <summary>
        /// its fitness score after it has been placed into a species and adjusted accordingly 
        /// </summary>
        double AdjustedFitness;

        /// <summary>
        /// the number of offspring this individual is required to spawn for the next generation 
        /// </summary>
        double AmountToSpawn;

        /// <summary>
        /// keep a record of the number of inputs and outputs 
        /// </summary>
        int NumberOfInputs, NumberOfOutputs;

        /// <summary>
        /// keeps a track of which species this genome is in (only used for display purposes) 
        /// </summary>
        int Species;

        /// <summary>
        /// tests if the passed ID is the same as any existing neuron IDs. Used in AddNeuron 
        /// </summary>
        /// <returns></returns>
        bool AlreadyHaveThisNeuronID(int ID)
        {
            for (int n = 0; n < this.Neurons.Count; ++n)
            {
                if (ID == this.Neurons[n].ID)
                {
                    return true;
                }
            }

            return false;
        }

        public Genome()
        {
            this.Phenotype = null;
            this.GenomeID = 0;
            this.Fitness = 0;
            this.AdjustedFitness = 0;
            this.NumberOfInputs = 0;
            this.NumberOfOutputs = 0;
            this.AmountToSpawn = 0;
            this.Species = 0;
        }

        /// <summary>
        /// this constructor creates a minimal genome where there are output & input neurons and every input neuron is connected to each output neuron 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="inputs"></param>
        /// <param name="outputs"></param>
        public Genome(int id, int inputs, int outputs)
        {
            this.Phenotype = null;
            this.GenomeID = id;
            this.Fitness = 0;
            this.AdjustedFitness = 0;
            this.NumberOfInputs = inputs;
            this.NumberOfOutputs = outputs;
            this.AmountToSpawn = 0;
            this.Species = 0;
            this.Neurons = new List<NeuronGene>();
            this.Links = new List<LinkGene>();

            //create the input neurons 
            double InputRowSlice = 1 / (double)(inputs + 2);

            for (int i = 0; i < inputs; i++)
            {
                this.Neurons.Add(new NeuronGene(NeuronType.Input, i, 0, (i + 2) * InputRowSlice));
            }

            //create the bias 
            this.Neurons.Add(new NeuronGene(NeuronType.Bias, inputs, 0, InputRowSlice));

            //create the output neurons 
            double OutputRowSlice = 1 / (double)(outputs + 1);

            for (int i = 0; i < outputs; i++)
            {
                this.Neurons.Add(new NeuronGene(NeuronType.Output, i + inputs + 1, 1, (i + 1) * OutputRowSlice));
            }

            //create the link genes, connect each input neuron to each output neuron and  
            //assign a random weight -1 < w < 1 
            for (int i = 0; i < inputs + 1; i++)
            {
                for (int j = 0; j < outputs; j++)
                {
                    this.Links.Add(new LinkGene(this.Neurons[i].ID,
                                                 this.Neurons[inputs + j + 1].ID,
                                                 true,
                                                 inputs + outputs + 1 + this.GetNumGenes(),
                                                 RandomProvider.RandomClamped()));
                }
            }
        }

        /// <summary>
        /// this constructor creates a genome from a vector of LinkGenes a vector of NeuronGenes and an ID number 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="neurons"></param>
        /// <param name="genes"></param>
        /// <param name="inputs"></param>
        /// <param name="outputs"></param>
        public Genome(int id, List<NeuronGene> neurons, List<LinkGene> genes, int inputs, int outputs)
        {
            this.Phenotype = null;
            this.GenomeID = id;
            this.Fitness = 0;
            this.AdjustedFitness = 0;
            this.NumberOfInputs = inputs;
            this.NumberOfOutputs = outputs;
            this.AmountToSpawn = 0;
            this.Species = 0;
            this.Links = genes;
            this.Neurons = neurons;
        }

        /// <summary>
        /// Creates a neural network based upon the information in the genome. 
        /// The method that actually creates all the SLinks and SNeurons required for a phenotype
        /// is Genome::CreatePhenotype.This function iterates through the genome and
        /// creates any appropriate neurons and all the required links required for pointing to
        /// those neurons.It then creates an instance of the CNeuralNet class.
        /// </summary>
        /// <param name="depth">Returns a pointer to the newly created ANN </param>
        /// <returns></returns>
        public NeuralNet CreatePhenotype(int depth)
        {
            //first make sure there is no existing phenotype for this genome 
            DeletePhenotype();

            //this will hold all the neurons required for the phenotype 
            List<Neuron> phenotypeNeurons = new List<Neuron>();

            //first, create all the required neurons 
            for (int i = 0; i < this.Neurons.Count; i++)
            {
                Neuron neuron = new Neuron(this.Neurons[i].NeuronType,
                                               this.Neurons[i].ID,
                                               this.Neurons[i].SplitY,
                                               this.Neurons[i].SplitX,
                                               this.Neurons[i].ActivationResponse);

                phenotypeNeurons.Add(neuron);
            }

            //now to create the links.  
            for (int cGene = 0; cGene < this.Links.Count; ++cGene)
            {
                //make sure the link gene is enabled before the connection is created 
                if (this.Links[cGene].Enabled)
                {
                    //get the pointers to the relevant neurons 
                    int element = GetElementPosition(this.Links[cGene].FromNeuron);
                    Neuron FromNeuron = phenotypeNeurons[element];

                    element = GetElementPosition(this.Links[cGene].ToNeuron);
                    Neuron ToNeuron = phenotypeNeurons[element];

                    //create a link between those two neurons and assign the weight stored 
                    //in the gene 
                    Link tmpLink = new Link(this.Links[cGene].Weight,
                                            FromNeuron,
                                            ToNeuron,
                                            this.Links[cGene].Recurrent);

                    //add new links to neuron 
                    FromNeuron.LinksOut.Add(tmpLink);
                    ToNeuron.LinksIn.Add(tmpLink);
                }
            }

            //now the neurons contain all the connectivity information, a neural 
            //network may be created from them. 
            Phenotype = new NeuralNet(phenotypeNeurons, depth); 
	 
            return Phenotype; 
        }

        /// <summary>
        /// delete the neural network 
        /// </summary>
        public void DeletePhenotype()
        {
            this.Phenotype = null;
        }

        /// <summary>
        /// given a neuron ID this little function just finds its position in Neurons
        /// </summary>
        /// <param name="neuron_id"></param>
        /// <returns></returns>
        public int GetElementPosition(int neuron_id)
        {
            for (int i = 0; i < this.Neurons.Count; i++)
            {
                if (this.Neurons[i].ID == neuron_id)
                {
                    return i;
                }
            }

            Debug.Log("Error in CGenome::GetElementPos, Problem! for requested neuron ID: " + neuron_id);

            return -1;
        }

        /// <summary>
        /// returns true if the link is already part of the genome 
        /// </summary>
        /// <param name="NeuronIn"></param>
        /// <param name="NeuronOut"></param>
        /// <returns></returns>
        public bool DuplicateLink(int NeuronIn, int NeuronOut)
        {
            for (int cGene = 0; cGene < this.Links.Count; ++cGene)
            {
                if ((this.Links[cGene].FromNeuron == NeuronIn) &&
                (this.Links[cGene].ToNeuron == NeuronOut))
                {
                    //we already have this link 
                    return true;
                }
            }

            return false;
        }

        /// <summary>
        /// Add a link to the genome dependent upon the mutation rate. This is used in the structural mutation of NEAT 
        /// </summary>
        /// <param name="MutationRate"></param>
        /// <param name="ChanceOfRecurrent"></param>
        /// <param name="innovation"></param>
        /// <param name="NumTrysToFindLoop"></param>
        /// <param name="NumTrysToAddLink"></param>
        public void AddLink(double MutationRate, double ChanceOfRecurrent, Innovation innovation, int NumTrysToFindLoop, int NumTrysToAddLink)
        {
            //just return dependent on the mutation rate 
            if (RandomProvider.RandomFloat() > MutationRate) return;

            //define holders for the two neurons to be linked. If we have find two  
            //valid neurons to link these values will become >= 0. 
            int ID_neuron1 = -1;
            int ID_neuron2 = -1;

            //flag set if a recurrent link is selected (looped or normal) 
            bool bRecurrent = false;

            //first test to see if an attempt shpould be made to create a  
            //link that loops back into the same neuron 
            if (RandomProvider.RandomFloat() < ChanceOfRecurrent)
            {
                //YES: try NumTrysToFindLoop times to find a neuron that is not an 
                //input or bias neuron and that does not already have a loopback 
                //connection 
                while (NumTrysToFindLoop-- > 0)
                {
                    //grab a random neuron 
                    int NeuronPos = RandomProvider.RND.Next(this.NumberOfInputs + 1, this.Neurons.Count - 1);

                    //check to make sure the neuron does not already have a loopback  
                    //link and that it is not an input or bias neuron 
                    if (!this.Neurons[NeuronPos].Recurrent &&
                       (this.Neurons[NeuronPos].NeuronType != NeuronType.Bias) &&
                       (this.Neurons[NeuronPos].NeuronType != NeuronType.Input))
                    {
                        ID_neuron1 = ID_neuron2 = this.Neurons[NeuronPos].ID;

                        this.Neurons[NeuronPos].Recurrent = true;

                        bRecurrent = true;

                        NumTrysToFindLoop = 0;
                    }
                }
            }
            /*
                First, the code checks to see if there is a chance of a looped recurrent link being
                added. If so, then it attempts NumTrysToFindLoop times to find an appropriate neuron. If
                no neuron is found, the program continues to look for two unconnected neurons.
            */
            else
            {
                //No: try to find two unlinked neurons. Make NumTrysToAddLink 
                //attempts 
                /*
                    Because some networks will already have existing connections between all its available
                    neurons, the code has to make sure it doesn’t enter an infinite loop when it
                    tries to find two unconnected neurons. To prevent this from happening, the program
                    only tries NumTrysToAddLink times to find two unlinked neurons.
                */
                while (NumTrysToAddLink-- > 0)
                {
                    //choose two neurons, the second must not be an input or a bias 
                    ID_neuron1 = this.Neurons[RandomProvider.RND.Next(0, this.Neurons.Count - 1)].ID;

                    ID_neuron2 =
                    this.Neurons[RandomProvider.RND.Next(this.NumberOfInputs + 1, this.Neurons.Count - 1)].ID;

                    if (ID_neuron2 == 2)
                    {
                        continue;
                    }

                    //make sure these two are not already linked and that they are 
                    //not the same neuron 
                    if (!(DuplicateLink(ID_neuron1, ID_neuron2) ||
                            (ID_neuron1 == ID_neuron2)))
                    {
                        NumTrysToAddLink = 0;
                    }

                    else
                    {
                        ID_neuron1 = -1;
                        ID_neuron2 = -1;
                    }
                }
            }

            //return if unsuccessful in finding a link 
            if ((ID_neuron1 < 0) || (ID_neuron2 < 0))
            {
                return;
            }

            //check to see if we have already created this innovation 
            /*
                Here, the code examines the innovation database to see if this link has already been
                discovered by another genome. CheckInnovation returns either the ID number of the
                innovation or, if the link is a new innovation, a negative value.
            */
            int id = innovation.CheckInnovation(ID_neuron1, ID_neuron2, InnovationType.NewLink);

            //is this link recurrent? 
            if (this.Neurons[GetElementPosition(ID_neuron1)].SplitY >
                this.Neurons[GetElementPosition(ID_neuron2)].SplitY)
            {
                bRecurrent = true;
            }

            /*
            Here, the split values for the two neurons are compared to see if the link feeds
            forward or backward.
            */
            if (id < 0)
            {
                //we need to create a new innovation 
                innovation.CreateNewInnovation(ID_neuron1, ID_neuron2, InnovationType.NewLink);

                //then create the new gene 
                id = innovation.NextNumber() - 1;

                /*
                    If the program enters this section of code, then the innovation is a new one. Before
                    the new gene is created, the innovation is added to the database and an identification
                    number is retrieved. The new gene will be tagged with this identification
                    number.
                */
                LinkGene NewGene = new LinkGene(ID_neuron1,
                                      ID_neuron2,
                                      true,
                                      id,
                                      RandomProvider.RandomClamped(),
                                      bRecurrent);

                this.Links.Add(NewGene);
            }

            else
            {
                //the innovation has already been created so all we need to 
                //do is create the new gene using the existing innovation ID 
                LinkGene NewGene = new LinkGene(ID_neuron1,
                                      ID_neuron2,
                                      true,
                                      id,
                                      RandomProvider.RandomClamped(),
                                      bRecurrent);

                this.Links.Add(NewGene);
            }

            return;
        }

        /// <summary>
        /// and a neuron. This is used in the structural mutation of NEAT
        /// </summary>
        /// <param name="MutationRate"></param>
        /// <param name="innovation"></param>
        /// <param name="NumTrysToFindOldLink"></param>
        public void AddNeuron(double MutationRate, Innovation innovation, int NumTrysToFindOldLink)
        {
            //just return dependent on mutation rate 
            if (RandomProvider.RandomFloat() > MutationRate) return;

            //if a valid link is found into which to insert the new neuron 
            //this value is set to true. 
            bool bDone = false;

            //this will hold the index into m_vecLinks of the chosen link gene 
            int ChosenLink = 0;

            //first a link is chosen to split. If the genome is small the code makes  
            //sure one of the older links is split to ensure a chaining effect does 
            //not occur. Here, if the genome contains less than 5 hidden neurons it 
            //is considered to be too small to select a link at random 
            int SizeThreshold = this.NumberOfInputs + this.NumberOfOutputs + 5;

            if (this.Links.Count< SizeThreshold)
            {
                while (NumTrysToFindOldLink-- > 0)
                {
                    //choose a link with a bias towards the older links in the genome  
                    ChosenLink = RandomProvider.RND.Next(0, GetNumGenes() - 1 - (int)Mathf.Sqrt(GetNumGenes()));

                    //make sure the link is enabled and that it is not a recurrent link  
                    //or has a bias input 
                    int FromNeuron = this.Links[ChosenLink].FromNeuron;

                    if ((this.Links[ChosenLink].Enabled) &&
                         (!this.Links[ChosenLink].Recurrent) &&
                         (this.Neurons[GetElementPosition(FromNeuron)].NeuronType != NeuronType.Bias))
                    {
                        bDone = true;

                        NumTrysToFindOldLink = 0;
                    }
                }

                if (!bDone)
                {
                    //failed to find a decent link 
                    return;
                }
            }
            /*
                Early on in the development of the networks, a problem can occur where the same
                link is split repeatedly creating a chaining effect.

                Obviously, this is undesirable, so the following code checks the number of neurons
                in the genome to see if the structure is below a certain size threshold. If it is, measures
                are taken to ensure that older links are selected in preference to newer ones.
            */
            else
            {
                int maxExitCounter = this.Links.Count + NeuralNetworkParams.NumTicks;
                int exitCounter = 0;
                //the genome is of sufficient size for any link to be acceptable
                // 20.10.2015 also there is an exit counter to exit the loop if nothing is found in a certain amount of time. This can happen with very low ticks, the neural network gets to messed up. Reason unknown at the moment
                while (!bDone && exitCounter < maxExitCounter)
                {
                    ChosenLink = RandomProvider.RND.Next(0, GetNumGenes() - 1);

                    //make sure the link is enabled and that it is not a recurrent link  
                    //or has a BIAS input 
                    int FromNeuron = this.Links[ChosenLink].FromNeuron;

                    if ((this.Links[ChosenLink].Enabled) &&
                         (!this.Links[ChosenLink].Recurrent) &&
                         (this.Neurons[GetElementPosition(FromNeuron)].NeuronType != NeuronType.Bias))
                    {
                        bDone = true;
                    }

                    exitCounter++;
                }
                if(exitCounter >= maxExitCounter)
                {
                    Debug.Log("No proper links where found!");
                }
            }

            //disable this gene 
            this.Links[ChosenLink].Enabled = false;

            //grab the weight from the gene (we want to use this for the weight of 
            //one of the new links so that the split does not disturb anything the  
            //NN may have already learned... 
            double OriginalWeight = this.Links[ChosenLink].Weight;

            /*
                When a link is disabled and two new links are created, the old weight from the
                disabled link is used as the weight for one of the new links, and the weight for the
                other link is set to 1. In this way, the addition of a neuron creates as little disruption
                as possible to any existing learned behavior
            */

            //identify the neurons this link connects 
            int from = this.Links[ChosenLink].FromNeuron;
            int to = this.Links[ChosenLink].ToNeuron;

            //calculate the depth and width of the new neuron. We can use the depth 
            //to see if the link feeds backwards or forwards 
            double NewDepth = (this.Neurons[GetElementPosition(from)].SplitY +
                               this.Neurons[GetElementPosition(to)].SplitY) / 2;

            double NewWidth = (this.Neurons[GetElementPosition(from)].SplitX +
                               this.Neurons[GetElementPosition(to)].SplitX) / 2;

            //Now to see if this innovation has been created previously by 
            //another member of the population 
            int id = innovation.CheckInnovation(from,
                                                 to,
                                                 InnovationType.NewNeuron);



            /*it is possible for NEAT to repeatedly do the following: 
             
                1. Find a link. Lets say we choose link 1 to 5 
                2. Disable the link, 
                3. Add a new neuron and two new links 
                4. The link disabled in Step 2 maybe re-enabled when this genome 
                   is recombined with a genome that has that link enabled. 
                5  etc etc 
 
            Therefore, this function must check to see if a neuron ID is already  
            being used. If it is then the function creates a new innovation 
            for the neuron. */


            if (id >= 0)
            {
                int NeuronID = innovation.GetNeuronID(id);

                if (AlreadyHaveThisNeuronID(NeuronID))
                {
                    id = -1;
                }
            }

            /*
                AlreadyHaveThisNeuronID returns true if (you guessed it) the genome already has a
                neuron with an identical ID. If this is the case, then a new innovation needs to be
                created, so id is reset to -1.
            */
            if (id < 0)
            {
                //add the innovation for the new neuron 
                int NewNeuronID = innovation.CreateNewInnovation(from,
                                                                  to,
                                                                  InnovationType.NewNeuron,
                                                                  NeuronType.Hidden,
                                                                  NewWidth,
                                                                  NewDepth);

                //create the new neuron gene and add it. 
                this.Neurons.Add(new NeuronGene(NeuronType.Hidden,
                                               NewNeuronID,
                                               NewDepth,
                                               NewWidth));

                //Two new link innovations are required, one for each of the  
                //new links created when this gene is split. 

                //-----------------------------------first link 

                //get the next innovation ID 
                int idLink1 = innovation.NextNumber();

                //create the new innovation 
                innovation.CreateNewInnovation(from,
                                                NewNeuronID,
                                                InnovationType.NewLink);

                //create the new link gene 
                LinkGene link1 = new LinkGene(from,
                                    NewNeuronID,
                                    true,
                                    idLink1,
                                    1.0);

                this.Links.Add(link1);

                //-----------------------------------second link 

                //get the next innovation ID 
                int idLink2 = innovation.NextNumber();

                //create the new innovation 
                innovation.CreateNewInnovation(NewNeuronID,
                                                to,
                                                InnovationType.NewLink);

                //create the new gene 
                LinkGene link2 = new LinkGene(NewNeuronID,
                                    to,
                                    true,
                                    idLink2,
                                    OriginalWeight);

                this.Links.Add(link2);
            }

            else
            {
                //this innovation has already been created so grab the relevant neuron  
                //and link info from the innovation database 
                int NewNeuronID = innovation.GetNeuronID(id);

                //get the innovation IDs for the two new link genes. 
                int idLink1 = innovation.CheckInnovation(from, NewNeuronID, InnovationType.NewLink);
                int idLink2 = innovation.CheckInnovation(NewNeuronID, to, InnovationType.NewLink);

                //this should never happen because the innovations *should* have already  
                //occurred 
                if ((idLink1 < 0) || (idLink2 < 0))
                {
                    Debug.Log("Error in CGenome::AddNeuron, Problem!");

                    return;
                }

                //now we need to create 2 new genes to represent the new links 
                LinkGene link1 = new LinkGene(from, NewNeuronID, true, idLink1, 1.0);
                LinkGene link2 = new LinkGene(NewNeuronID, to, true, idLink2, OriginalWeight);

                this.Links.Add(link1);
                this.Links.Add(link2);

                //create the new neuron 
                NeuronGene NewNeuron = new NeuronGene(NeuronType.Hidden, NewNeuronID, NewDepth, NewWidth);

                //and add it 
                this.Neurons.Add(NewNeuron);
            } 
        
        return;
    }

        /// <summary>
        /// this function mutates the connection weights
        /// Iterates through the genes and purturbs the weights given a  
        ///  probability mut_rate. 
        /// 
        ///	prob_new_mut is the chance that a weight may get replaced by a 
        ///  completely new weight. 
        /// 
        ///	dMaxPertubation is the maximum perturbation to be applied. 
        /// 
        ///	type is the type of random number algorithm we use 
        /// </summary>
        /// <param name="mut_rate"></param>
        /// <param name="prob_new_mut"></param>
        /// <param name="dMaxPertubation"></param>
        public void MutateWeights(double mut_rate, double prob_new_mut, double dMaxPertubation)
        {
            for (int cGen = 0; cGen < this.Links.Count; ++cGen)
            {
                //do we mutate this gene? 
                if (RandomProvider.RandomFloat() < mut_rate)
                {
                    //do we change the weight to a completely new weight? 
                    if (RandomProvider.RandomFloat() < prob_new_mut)
                    {
                        //change the weight using the random distribtion defined by 'type' 
                        this.Links[cGen].Weight = RandomProvider.RandomClamped();
                    }

                    else
                    {
                        //perturb the weight 
                        this.Links[cGen].Weight += RandomProvider.RandomClamped() * NeuralNetworkParams.MaxWeightPerturbation;
                    }
                }
            }

            return;
        }

        /// <summary>
        /// perturbs the activation responses of the neurons 
        /// </summary>
        /// <param name="mut_rate"></param>
        /// <param name="MaxPertubation"></param>
        public void MutateActivationResponse(double mut_rate, double MaxPertubation)
        {
            for (int cGen = 0; cGen < this.Neurons.Count; ++cGen)
            {
                if (RandomProvider.RandomFloat() < mut_rate)
                {
                    this.Neurons[cGen].ActivationResponse += RandomProvider.RandomClamped() * MaxPertubation;
                }
            }
        }


        /// <summary>
        /// calculates the compatibility score between this genome and another genome this function returns a score based on the compatibility of this genome with the passed genome
        /// </summary>
        /// <param name="genome"></param>
        /// <returns></returns>
        public double GetCompatibilityScore(Genome genome)
        {
            //travel down the length of each genome counting the number of  
            //disjoint genes, the number of excess genes and the number of 
            //matched genes 
            double NumDisjoint = 0;
            double NumExcess = 0;
            double NumMatched = 0;

            //this records the summed difference of weights in matched genes 
            double WeightDifference = 0;

            //position holders for each genome. They are incremented as we 
            //step down each genomes length. 
            int g1 = 0;
            int g2 = 0;

            while ((g1 < this.Links.Count - 1) || (g2 < genome.Links.Count - 1))
            {
                //we've reached the end of genome1 but not genome2 so increment 
                //the excess score 
                if (g1 == this.Links.Count - 1)
                {
                    ++g2;
                    ++NumExcess;

                    continue;
                }

                //and vice versa 
                if (g2 == genome.Links.Count - 1)
                {
                    ++g1;
                    ++NumExcess;

                    continue;
                }

                //get innovation numbers for each gene at this point 
                int id1 = this.Links[g1].InnovationID;
                int id2 = genome.Links[g2].InnovationID;

                //innovation numbers are identical so increase the matched score 
                if (id1 == id2)
                {
                    ++g1;
                    ++g2;
                    ++NumMatched;

                    //get the weight difference between these two genes 
                    WeightDifference += Mathf.Abs((float)(this.Links[g1].Weight - genome.Links[g2].Weight));
                }

                //innovation numbers are different so increment the disjoint score 
                if (id1 < id2)
                {
                    ++NumDisjoint;
                    ++g1;
                }

                if (id1 > id2)
                {
                    ++NumDisjoint;
                    ++g2;
                }

            }//end while 

            //get the length of the longest genome 
            int longest = genome.GetNumGenes();

            if (GetNumGenes() > longest)
            {
                longest = GetNumGenes();
            }

            //these are multipliers used to tweak the final score. 
            const double mDisjoint = 1;
            const double mExcess = 1;
            const double mMatched = 0.4;

            //finally calculate the scores  
            double score = (mExcess * NumExcess / (double)longest) +
                           (mDisjoint * NumDisjoint / (double)longest) +
                           (mMatched * WeightDifference / NumMatched);


            return score;
        }


    public void SortLinkGenes()
    {
            this.Links.Sort(delegate (LinkGene x, LinkGene y)
            {
                if (x.InnovationID == y.InnovationID)
                    return 0;

                return x.InnovationID < y.InnovationID ? -1 : 1;
            });
    }

    public bool HasSmallerFitness(Genome genome)
    {
        return this.Fitness < genome.Fitness;
    }

    public int GetID()
    {
        return GenomeID;
    }

    public void SetID(int val)
    {
        GenomeID = val;
    }

    public int GetNumGenes()
    {
        return this.Links.Count;
    }

    public int GetNumNeurons()
    {
        return this.Neurons.Count;
    }

    public int GetNumInputs()
    {
        return this.NumberOfInputs;
    }

    public int GetNumOutputs()
    {
        return this.NumberOfOutputs;
    }


    public double GetAmountToSpawn()
    {
        return AmountToSpawn;
    }

    public void SetAmountToSpawn(double num)
    {
        AmountToSpawn = num;
    }

    public void SetFitness(double num)
    {
        Fitness = num;
    }

    public void SetAdjFitness(double num)
    {
        AdjustedFitness = num;
    }

    public double GetFitnessValue()
    {
        return Fitness;
    }

    public double GetAdjFitness()
    {
        return AdjustedFitness;
    }

    public int GetSpecies()
    {
        return Species;
    }

    public void SetSpecies(int spc)
    {
        Species = spc;
    }


    public double GetSplitY(int val)
    {
        return Neurons[val].SplitY;
    }

    public List<LinkGene> GetGenes()
    {
        return Links;
    }
        private FieldInfo[] _FieldInfo = null;

        public List<NeuronGene> GetNeurons()
    {
        return Neurons;
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

        public LinkGene GetStartOfGenes() { return this.Links.Count > 0 ? Links.First() : null; }
    public LinkGene GetEndOfGenes() { return this.Links.Count > 0 ? Links.Last() : null; } 
}
}
