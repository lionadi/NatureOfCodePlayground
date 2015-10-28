using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;
using Assets.Scripts.AI.NeuralNetworks;

namespace Assets.Scripts.AI.NeuralNetworks.NEAT
{
    enum parent_type { MUM, DAD, };

    public class GeneticAlgorithm
    {
        /// <summary>
        /// current population 
        /// </summary>
        //List<Genome> Genomes;
        Genome[] Genomes;

        /// <summary>
        /// keep a record of the last generations best genomes. (used to render 
        /// the best performers to the display if the user presses the 'B' key) 
        /// </summary>
        List<Genome> BestGenomes;

        /// <summary>
        /// all the species 
        /// </summary>
        List<Species> Species;

        /// <summary>
        /// to keep track of innovations 
        /// </summary>
        Innovation Innovation;

        /// <summary>
        /// current generation 
        /// </summary>
        int Generation;

        int NextGenomeID;

        int NextSpeciesID;

        int PopSize;

        /// <summary>
        /// adjusted fitness scores 
        /// </summary>
        double TototalFitnessAdjusted,
                          AverageFitnessAdjusted;

        /// <summary>
        /// index into the genomes for the fittest genome 
        /// </summary>
        int FittestGenome;

        double BestEverFitness;

        /// <summary>
        /// local copies of client area 
        /// </summary>
        int WindowClientWidth, WindowClientHeight;

        //this holds the precalculated split depths. They are used  
        //to calculate a neurons x/y position for rendering and also 
        //for calculating the flush depth of the network when a 
        //phenotype is working in 'snapshot' mode. 
        List<SplitDepth> vecSplits;


        /// <summary>
        /// used in Crossover 
        /// </summary>
        /// <param name="nodeID"></param>
        /// <param name=""></param>
        /// <param name=""></param>
        void AddNeuronID(int nodeID, List<int> vec)
        {
            for (int i = 0; i < vec.Count; i++)
            {
                if (vec[i] == nodeID)
                {
                    //already added   
                    return;
                }
            }

            vec.Add(nodeID);

            return;
        }

        /// <summary>
        /// this function resets some values ready for the next epoch, kills off  all the phenotypes and any poorly performing species. 
        /// </summary>
        void ResetAndKill()
        {
            this.TototalFitnessAdjusted = 0;
            this.AverageFitnessAdjusted = 0;

            //purge the species   

            Species curSp = null;

            int curSpIndex = 0;

            while (curSpIndex != this.Species.Count)
            {
                curSp = this.Species[curSpIndex];
                curSp.Purge();

                //kill off species if not improving and if not the species which contains    
                //the best genome found so far   
                if ((curSp.GensNoImprovement() > NeuralNetworkParams.NumGensAllowedNoImprovement) &&
                     (curSp.GetBestFitness() < this.BestEverFitness))
                {
                    this.Species.RemoveAt(curSpIndex);
                    --curSpIndex;
                    curSp = this.Species[curSpIndex];
                }

                ++curSpIndex;
                
            }

            //we can also delete the phenotypes   
            for (int gen = 0; gen < this.Genomes.Length; ++gen)
            {
                this.Genomes[gen].DeletePhenotype();
            }
        }

        /// <summary>
        /// separates each individual into its respective species by calculating 
        /// a compatibility score with every other member of the population and
        /// niching accordingly.The function then adjusts the fitness scores of
        /// each individual by species age and by sharing and also determines
        /// how many offspring each individual should spawn.
        /// </summary>
        void SpeciateAndCalculateSpawnLevels()
        {
            bool bAdded = false;

            //iterate through each genome and speciate   
            for (int gen = 0; gen < this.Genomes.Length; ++gen)
            {
                //calculate its compatibility score with each species leader. If   
                //compatible add to species. If not, create a new species   
                for (int spc = 0; spc < this.Species.Count; ++spc)
                {
                    double compatibility = this.Genomes[gen].GetCompatibilityScore(this.Species[spc].GetLeader());

                    //if this individual is similar to this species add to species   
                    if (compatibility <= NeuralNetworkParams.CompatibilityThreshold)
                    {
                        this.Species[spc].AddMember(this.Genomes[gen]);

                        //let the genome know which species it's in   
                        this.Genomes[gen].SetSpecies(this.Species[spc].ID());

                        bAdded = true;

                        break;
                    }
                }

                if (!bAdded)
                {
                    //we have not found a compatible species so let's create a new one   
                    this.Species.Add(new Species(this.Genomes[gen], this.NextSpeciesID++));
                }

                bAdded = false;
            }

            //now all the genomes have been assigned a species the fitness scores    
            //need to be adjusted to take into account sharing and species age.   
            AdjustSpeciesFitnesses();

            //calculate new adjusted total & average fitness for the population   
            for (int gen = 0; gen < this.Genomes.Length; ++gen)
            {
                this.TototalFitnessAdjusted += this.Genomes[gen].GetAdjFitness();
            }

            this.AverageFitnessAdjusted = TototalFitnessAdjusted / this.Genomes.Length;

            //calculate how many offspring each member of the population   
            //should spawn   
            for (int gen = 0; gen < this.Genomes.Length; ++gen)
            {
                double ToSpawn = this.Genomes[gen].GetAdjFitness() / this.AverageFitnessAdjusted;

                this.Genomes[gen].SetAmountToSpawn(ToSpawn);
            }

            //iterate through all the species and calculate how many offspring   
            //each species should spawn   
            for (int spc = 0; spc < this.Species.Count; ++spc)
            {
                this.Species[spc].CalculateSpawnAmount();
            }
        }

        /// <summary>
        /// adjusts the fitness scores depending on the number sharing the species and the age of the species. 
        /// </summary>
        void AdjustSpeciesFitnesses()
        {
            for (int sp = 0; sp < this.Species.Count; ++sp)
            {
                this.Species[sp].AdjustFitnesses();
            }
        }

        Genome Crossover(Genome mum, Genome dad)
        {
            // TODO: Test the Crossover in Unity

            //helps make the code clearer   
            //first, calculate the genome we will using the disjoint/excess   
            //genes from. This is the fittest genome.   
            parent_type best;

            //if they are of equal fitness use the shorter (because we want to keep   
            //the networks as small as possible)   
            if (mum.GetFitnessValue() == dad.GetFitnessValue())
            {
                //if they are of equal fitness and length just choose one at   
                //random   
                if (mum.GetNumGenes() == dad.GetNumGenes())
                {
                    best = (parent_type)RandomProvider.RND.Next(0, 1);
                }

                else
                {
                    if (mum.GetNumGenes() < dad.GetNumGenes())
                    {
                        best = parent_type.MUM;
                    }

                    else
                    {
                        best = parent_type.DAD;
                    }
                }
            }

            else
            {
                if (mum.GetFitnessValue() > dad.GetFitnessValue())
                {
                    best = parent_type.MUM;
                }

                else
                {
                    best = parent_type.DAD;
                }
            }

            //these vectors will hold the offspring's nodes and genes   
            List<NeuronGene> BabyNeurons = new List<NeuronGene>();
            List<LinkGene> BabyGenes = new List<LinkGene>();

            //temporary List to store all added node IDs   
            List<int> vecNeurons = new List<int>();

            //create iterators so we can step through each parents genes and set   
            //them to the first gene of each parent   
            LinkGene curMum = mum.GetStartOfGenes();
            LinkGene curDad = dad.GetStartOfGenes();
            //int curMumIndex = 0;
            //int curDadIndex = 0;

            //this will hold a copy of the gene we wish to add at each step   
            LinkGene SelectedGene = null;
            int mumActualItemCount = mum.Links.Count - 1;
            int dadActualItemCount = dad.Links.Count - 1;

            //step through each parents genes until we reach the end of both   
            //while (!((curMumIndex > mumActualItemCount) && (curDadIndex > dadActualItemCount)))
            for (int curMumIndex = 0, curDadIndex = 0; curMumIndex < mum.Links.Count && curDadIndex < dad.Links.Count;)
            {
                if (curDadIndex > dadActualItemCount)
                    curDadIndex = dadActualItemCount;

                if (curMumIndex > mumActualItemCount)
                    curMumIndex = mumActualItemCount;

                curMum = mum.Links[curMumIndex];
                curDad = dad.Links[curDadIndex];

                //the end of mum's genes have been reached   
                if (((curMumIndex >= mumActualItemCount) && (curDadIndex != dadActualItemCount)))
                {
                    //if dad is fittest   
                    if (best == parent_type.DAD)
                    {
                        //add dads genes   
                        SelectedGene = curDad;
                    }

                    //move onto dad's next gene   
                    ++curDadIndex;
                }

                //the end of dads's genes have been reached   
                else if ((curDadIndex >= dadActualItemCount) && (curMumIndex != mumActualItemCount))
                {
                    //if mum is fittest   
                    if (best == parent_type.MUM)
                    {
                        //add mums genes   
                        SelectedGene = curMum;
                    }

                    //move onto mum's next gene   
                    ++curMumIndex;
                }

                //if mums innovation number is less than dads   
                else if (curMum.InnovationID < curDad.InnovationID)
                {
                    //if mum is fittest add gene   
                    if (best == parent_type.MUM)
                    {
                        SelectedGene = curMum;
                    }

                    //move onto mum's next gene   
                    ++curMumIndex;
                }

                //if dads innovation number is less than mums   
                else if (curDad.InnovationID < curMum.InnovationID)
                {
                    //if dad is fittest add gene   
                    if (best == parent_type.DAD)
                    {
                        SelectedGene = curDad;
                    }

                    //move onto dad's next gene   
                    ++curDadIndex;
                }

                //if innovation numbers are the same   
                else if (curDad.InnovationID == curMum.InnovationID)
                {
                    //grab a gene from either parent   
                    if (RandomProvider.RandomFloat() < 0.5f)
                    {
                        SelectedGene = curMum;
                    }

                    else
                    {
                        SelectedGene = curDad;
                    }

                    //move onto next gene of each parent   
                    ++curMumIndex;
                    ++curDadIndex;
                    
                }

                if(SelectedGene == null)
                {
                    int x = 0;
                    continue;
                }

                //add the selected gene if not already added   
                if (BabyGenes.Count == 0)
                {
                    BabyGenes.Add(SelectedGene);
                }

                else
                {
                    if (BabyGenes[BabyGenes.Count - 1].InnovationID !=
                        SelectedGene.InnovationID)
                    {
                        BabyGenes.Add(SelectedGene);
                    }
                }

                

                //Check if we already have the nodes referred to in SelectedGene.   
                //If not, they need to be added.           
                AddNeuronID(SelectedGene.FromNeuron, vecNeurons);
                AddNeuronID(SelectedGene.ToNeuron, vecNeurons);

                if (vecNeurons.Count == 13 && !vecNeurons.Contains(11))
                {
                    int yyy = 0;
                }

            }//end while   

            //now create the required nodes. First sort them into order   
            vecNeurons.Sort(delegate (int x, int y)
            {
                return x.CompareTo(y);
            });

            for (int i = 0; i < vecNeurons.Count; i++)
            {
                BabyNeurons.Add(Innovation.CreateNeuronFromID(vecNeurons[i]));
            }

            //finally, create the genome   
            Genome babyGenome = new Genome(NextGenomeID++,
                               BabyNeurons,
                               BabyGenes,
                               mum.GetNumInputs(),
                               mum.GetNumOutputs());

            return babyGenome;
        }

        Genome TournamentSelection(int NumComparisons)
        {
            double BestFitnessSoFar = 0;

            int ChosenOne = 0;

            //Select NumComparisons members from the population at random testing     
            //against the best found so far   
            for (int i = 0; i < NumComparisons; ++i)
            {
                int ThisTry = RandomProvider.RND.Next(0, this.Genomes.Length - 1);

                if (this.Genomes[ThisTry].GetFitnessValue() > BestFitnessSoFar)
                {
                    ChosenOne = ThisTry;

                    BestFitnessSoFar = this.Genomes[ThisTry].GetFitnessValue();
                }
            }

            //return the champion   
            return this.Genomes[ChosenOne];
        }

        /// <summary>
        /// searches the lookup table for the dSplitY value of each node in the genome and returns the depth of the network based on this figure 
        /// </summary>
        /// <param name="gen"></param>
        /// <returns></returns>
        int CalculateNetDepth(Genome gen)
        {
            int MaxSoFar = 0;

            for (int nd = 0; nd < gen.GetNumNeurons(); ++nd)
            {
                for (int i = 0; i < vecSplits.Count; ++i)
                {

                    if ((gen.GetSplitY(nd) == vecSplits[i].Value) &&
                        (vecSplits[i].Depth > MaxSoFar))
                    {
                        MaxSoFar = vecSplits[i].Depth;
                    }
                }
            }
            return MaxSoFar + 2;
        }
        
        /// <summary>
        /// sorts the population into descending fitness, keeps a record of the best n genomes and updates any fitness statistics accordingly  
        /// </summary>
        public void SortAndRecord()
        {
            //sort the genomes according to their unadjusted (no fitness sharing)   
            //fitnesses   
            //this.Genomes.Sort(delegate (Genome x, Genome y)
            // {
            //     if (x.GetFitnessValue() == y.GetFitnessValue())
            //         return 0;

            //     return x.GetFitnessValue() > y.GetFitnessValue() ? -1 : 1;
            // });
            
            foreach(Genome genome in this.Genomes)
            {
                if(genome.GetFitnessValue() > BestEverFitness)
                {
                    BestEverFitness = genome.GetFitnessValue();
                }
            }

            //is the best genome this generation the best ever?   
            if (this.Genomes[0].GetFitnessValue() > BestEverFitness)
            {
                BestEverFitness = this.Genomes[0].GetFitnessValue();
            }

            //keep a record of the n best genomes   
            StoreBestGenomes();
        }

        /// <summary>
        /// a recursive function used to calculate a lookup table of split depths 
        /// this function is used to create a lookup table that is used to calculate the depth of the network.
        /// </summary>
        /// <param name="low"></param>
        /// <param name="high"></param>
        /// <param name="depth"></param>
        /// <returns></returns>
        List<SplitDepth> Split(double low, double high, int depth)
        {
            List<SplitDepth> vecSplits = new List<SplitDepth>();

            double span = high - low;

            vecSplits.Add(new SplitDepth(low + span / 2, depth + 1));

            if (depth > 6)
            {
                return vecSplits;
            }

            else
            {
                Split(low, low + span / 2, depth + 1);
                Split(low + span / 2, high, depth + 1);

                return vecSplits;
            }
        }

        public GeneticAlgorithm(int size, int inputs, int outputs, int cx, int cy)
        {
            this.PopSize = size;
            this.Generation = 0;
            this.Innovation = null;
            this.NextGenomeID = 0;
            this.NextSpeciesID = 0;
            this.FittestGenome = 0;
            this.BestEverFitness = 0;
            this.TototalFitnessAdjusted = 0;
            this.AverageFitnessAdjusted = 0;
            this.WindowClientWidth = cx;
            this.WindowClientHeight = cy;

            //this.Genomes = new List<Genome>();
            this.Genomes = new Genome[this.PopSize];
            this.BestGenomes = new List<Genome>();
            this.Species = new List<NEAT.Species>();

            //create the population of genomes   
            for (int i = 0; i < this.PopSize; ++i)
            {
                //this.Genomes.Add(new Genome(this.NextGenomeID++, inputs, outputs));
                this.Genomes[i] = new Genome(this.NextGenomeID++, inputs, outputs);
            }

            //create the innovation list. First create a minimal genome   
            Genome genome = new Genome(1, inputs, outputs);

            //create the innovations   
            this.Innovation = new Innovation(genome.GetGenes(), genome.GetNeurons());

            //create the network depth lookup table   
            vecSplits = Split(0, 1, 0);
        }

        /// <summary>
        /// This function performs one epoch of the genetic algorithm and returns a vector of pointers to the new phenotypes 
        /// </summary>
        /// <param name="FitnessScores"></param>
        /// <returns></returns>
        public List<NeuralNet> Epoch(List<double> FitnessScores)
        {
            // 21.10.2015 TODO: IF THE FITNESS IF ZERO THE GA WILL NOT WORK AND BEHAVE UN EXPECTEDLY THIS NEEDS FAIL SAFE MACHANISM
            //first check to make sure we have the correct amount of fitness scores   
            if (FitnessScores.Count != this.Genomes.Length)
            {
                Debug.Log("Cga::Epoch(scores/ genomes mismatch)!");
            }
            //Debug.Log(" Befiore ResetAndKill");
            //reset appropriate values and kill off the existing phenotypes and   
            //any poorly performing species   
            ResetAndKill();

            //Debug.Log("ResetAndKill");
            /*
            First of all, any phenotypes created during the previous generation are deleted. The
            program then examines each species in turn and deletes all of its members apart
            from the best performing one. (You use this individual as the genome to be tested
            against when the compatibility distances are calculated). If a species hasn’t made
            any fitness improvement in CParams::iNumGensAllowedNoImprovement generations, the
            species is killed off.*/
            //update the genomes with the fitnesses scored in the last run   
            // BUG HERE WITH C# value not set???
            for (int gen = 0; gen < this.Genomes.Length; ++gen)
            {
                this.Genomes[gen].SetFitness(FitnessScores[gen]);
            }
            

            //sort genomes and keep a record of the best performers   
            SortAndRecord();

            //separate the population into species of similar topology, adjust   
            //fitnesses and calculate spawn levels   
            SpeciateAndCalculateSpawnLevels();
            
            //Debug.Log("SpeciateAndCalculateSpawnLevels");
            /*
            SpeciateAndCalculateSpawnLevels commences by calculating the compatibility distance
            of each genome against the representative genome from each live species. If the
            value is within a set tolerance, the individual is added to that species. If no species
            match is found, then a new species is created and the genome added to that.
            When all the genomes have been assigned to a species
            SpeciateAndCalculateSpawnLevels calls the member function AdjustSpeciesFitnesses to
            adjust and share the fitness scores as discussed previously.
            
            Next, SpeciateAndCalculateSpawnLevels calculates how many offspring each individual
            is predicted to spawn into the new generation. This is a floating-point value calculated
            by dividing each genome’s adjusted fitness score with the average adjusted
            fitness score for the entire population. For example, if a genome had an adjusted
            fitness score of 4.4 and the average is 8.0, then the genome should spawn 0.525
            offspring. Of course, it’s impossible for an organism to spawn a fractional part of
            itself, but all the individual spawn amounts for the members of each species are
            summed to calculate an overall spawn amount for that species. Table 11.3 may help
            clear up any confusion you may have with this process. It shows typical spawn values
            for a small population of 20 individuals. The epoch function can now simply iterate
            through each species and spawn the required amount of offspring.
*/

            //this will hold the new population of genomes   
            Genome[] NewPop = new Genome[this.PopSize];
            int currentNewGenomeIndex = 0;

            //request the offspring from each species. The number of children to    
            //spawn is a double which we need to convert to an int.    
            int NumSpawnedSoFar = 0;

            Genome baby = null;

            //now to iterate through each species selecting offspring to be mated and    
            //mutated    
            for (int spc = 0; spc < this.Species.Count; ++spc)
            {
                //because of the number to spawn from each species is a double   
                //rounded up or down to an integer it is possible to get an overflow   
                //of genomes spawned. This statement just makes sure that doesn't   
                //happen   
                if (NumSpawnedSoFar < NeuralNetworkParams.UnityInstantiatedNumSweepers)
                {
                    //this is the amount of offspring this species is required to   
                    // spawn. Rounded simply rounds the double up or down.   
                    int NumToSpawn = Mathf.RoundToInt((float)this.Species[spc].NumToSpawn());

                    bool bChosenBestYet = false;

                    while (NumToSpawn-- > 0)
                    {
                        //first grab the best performing genome from this species and transfer   
                        //to the new population without mutation. This provides per species   
                        //elitism   
                        if (!bChosenBestYet)
                        {
                            baby = this.Species[spc].GetLeader();

                            bChosenBestYet = true;
                        }

                        else
                        {
                            //if the number of individuals in this species is only one   
                            //then we can only perform mutation   
                            if (this.Species[spc].NumMembers() == 1)
                            {
                                //spawn a child   
                                baby = this.Species[spc].Spawn();
                            }

                            //if greater than one we can use the crossover operator   
                            else
                            {
                                //spawn1   
                                Genome g1 = this.Species[spc].Spawn();

                                if (RandomProvider.RandomFloat() < NeuralNetworkParams.CrossoverRate)
                                {

                                    //spawn2, make sure it's not the same as g1   
                                    Genome g2 = this.Species[spc].Spawn();

                                    //number of attempts at finding a different genome   
                                    int NumAttempts = 5;

                                    while ((g1.GetID() == g2.GetID()) && (NumAttempts-- >= 0))
                                    {
                                        g2 = this.Species[spc].Spawn();
                                    }

                                    if (g1.GetID() != g2.GetID())
                                    {
                                        baby = Crossover(g1, g2);
                                        
                                    }

                                    /*Because the number of individuals in a species may be small and because only the
                                    best 20% (default value) are retained to be parents, it is sometimes impossible (or
                                    slow) to find a second genome to mate with. The code shown here tries five times to
                                    find a different genome and then aborts.*/
                                }

                                else
                                {

                                    baby = g1;
                                }
                            }

                            

                            ++this.NextGenomeID;

                            baby.SetID(this.NextGenomeID);

                            //now we have a spawned child lets mutate it! First there is the   
                            //chance a neuron may be added   
                            if (baby.GetNumNeurons() < NeuralNetworkParams.MaxPermittedNeurons)
                            {
                                baby.AddNeuron(NeuralNetworkParams.ChanceAddNode,
                                               Innovation,
                                               NeuralNetworkParams.NumTrysToFindOldLink);
                            }

                            ////now there's the chance a link may be added   
                            baby.AddLink(NeuralNetworkParams.ChanceAddLink,
                                         NeuralNetworkParams.ChanceAddRecurrentLink,
                                         Innovation,
                                         NeuralNetworkParams.NumTrysToFindLoopedLink,
                                         NeuralNetworkParams.NumAddLinkAttempts);

                            //mutate the weights   
                            baby.MutateWeights(NeuralNetworkParams.MutationRate,
                                               NeuralNetworkParams.ProbabilityWeightReplaced,
                                               NeuralNetworkParams.MaxWeightPerturbation);

                            baby.MutateActivationResponse(NeuralNetworkParams.ActivationMutationRate,
                                                          NeuralNetworkParams.MaxActivationPerturbation);
                        }

                        //sort the babies genes by their innovation numbers   
                        baby.SortLinkGenes();

                        //add to new pop   
                        NewPop[currentNewGenomeIndex]= baby;
                        currentNewGenomeIndex++;

                        ++NumSpawnedSoFar;

                        if (NumSpawnedSoFar == NeuralNetworkParams.UnityInstantiatedNumSweepers)
                        {
                            NumToSpawn = 0;
                        }

                    }//end while   

                }//end if   

            }//next species   
            //Debug.Log("SPECIES COMPLETE");

            //if there is an underflow due to the rounding error and the amount   
            //of offspring falls short of the population size additional children   
            //need to be created and added to the new population. This is achieved   
            //simply, by using tournament selection over the entire population.   
            if (NumSpawnedSoFar < NeuralNetworkParams.UnityInstantiatedNumSweepers)
            {

                //calculate amount of additional children required   
                int Rqd = NeuralNetworkParams.UnityInstantiatedNumSweepers - NumSpawnedSoFar;

                //grab them   
                while (Rqd-- > 0)
                {
                    NewPop[currentNewGenomeIndex] = TournamentSelection(this.PopSize / 5);
                    currentNewGenomeIndex++;
                }
            }

            //Debug.Log("numspawned");
            
            //replace the current population with the new one   
            // BUG HERE
            //this.Genomes = NewPop.ToArray();

            //create the new phenotypes   
            List<NeuralNet> new_phenotypes = new List<NeuralNet>();
            for (int gen = 0; gen < this.Genomes.Length; ++gen)
            {
                //calculate max network depth   
                int depth = CalculateNetDepth(this.Genomes[gen]);

                NeuralNet phenotype = this.Genomes[gen].CreatePhenotype(depth);

                new_phenotypes.Add(phenotype);
            }


            //Debug.Log("before gen counter");
            //increase generation counter   
            ++this.Generation;
            
            return new_phenotypes;
        }

        /// <summary>
        /// iterates through the population and creates the phenotypes 
        /// cycles through all the members of the population and creates their 
        ///  phenotypes. Returns a vector containing pointers to the new phenotypes
        /// </summary>
        /// <returns></returns>
        public List<NeuralNet> CreatePhenotypes()
        {
            List<NeuralNet> networks = new List<NeuralNet>();

            for (int i = 0; i < this.PopSize; i++)
            {
                //calculate max network depth 
                int depth = CalculateNetDepth(Genomes[i]);

                //create new phenotype 
                NeuralNet net = Genomes[i].CreatePhenotype(depth);

                networks.Add(net);
            }

            return networks;
        }

        /// <summary>
        /// keeps a record of the n best genomes from the last population. (used to display the best genomes) 
        /// </summary>
        public void StoreBestGenomes()
        {
            //clear old record   
            this.BestGenomes.Clear();

            for (int gen = 0; gen < NeuralNetworkParams.NumBestSweepers; ++gen)
            {
                this.BestGenomes.Add(this.Genomes[gen]);
            }
        }

        /// <summary>
        /// renders the best performing species statistics and a visual aid showing the distribution. 
        /// </summary>
        /// <param name=""></param>
        /// <param name=""></param>
        /// <param name="db"></param>
        public void RenderSpeciesInfo()
        {

        }

        /// <summary>
        /// returns a List of the n best phenotypes from the previous generation 
        /// </summary>
        /// <returns></returns>
        public List<NeuralNet> GetBestPhenotypesFromLastGeneration()
        {
            List<NeuralNet> brains = new List<NeuralNet>();

            for (int gen = 0; gen < this.BestGenomes.Count; ++gen)
            {
                //calculate max network depth   
                int depth = CalculateNetDepth(this.BestGenomes[gen]);

                brains.Add(this.BestGenomes[gen].CreatePhenotype(depth));
            }

            return brains;
        }


        //----------------------------------------------------accessor methods 
        public int NumSpecies() {return this.Species.Count;}

        public double GetBestEverFitness() {return BestEverFitness;}
    }

    /*RenderSpeciesInfo(HDC &surface, RECT db)
{
  if (m_vecSpecies.size() < 1) return;
  
  int numColours = 255/m_vecSpecies.size();

  double SlicePerSweeper = (double)(db.right-db.left)/(double)(CParams::iPopSize-1);

  double left = db.left;

  //now draw a different colored rectangle for each species
  for (int spc=0; spc<m_vecSpecies.size(); ++spc)
  {

     //choose a brush to draw with
     HBRUSH PieBrush = CreateSolidBrush(RGB(numColours*spc, 255, 255 - numColours*spc));

     HBRUSH OldBrush = (HBRUSH)SelectObject(surface, PieBrush);
     
     if (spc == m_vecSpecies.size()-1)
     {
       Rectangle(surface, 
                  left,
                  db.top,
                  db.right,
                  db.bottom);
     }

     else
     {
       Rectangle(surface, 
                  left,
                  db.top,
                  left+SlicePerSweeper*m_vecSpecies[spc].NumMembers(),
                  db.bottom);
     }

     left += SlicePerSweeper * m_vecSpecies[spc].NumMembers();

     SelectObject(surface, OldBrush);
     DeleteObject(PieBrush);

     //display best performing species stats in the same color as displayed
     //in the distribution bar
     if ( m_vecSpecies[spc].BestFitness() == m_dBestEverFitness)
     {
       string s = "Best Species ID: " + itos(m_vecSpecies[spc].ID());
       TextOut(surface, 5, db.top - 80, s.c_str(), s.size());
       
       s = "Species Age: " + itos(m_vecSpecies[spc].Age());          
       TextOut(surface, 5, db.top - 60, s.c_str(), s.size());

       s = "Gens no improvement: " + itos(m_vecSpecies[spc].GensNoImprovement());
       TextOut(surface, 5, db.top - 40, s.c_str(), s.size());

       s = "Threshold: " + ftos(CParams::dCompatibilityThreshold);
       TextOut(surface, 5, db.top - 100, s.c_str(), s.size());
     }
  }
  
  string s = "Species Distribution Bar";
	TextOut(surface, 5, db.top - 20, s.c_str(), s.size());
}*/
}
