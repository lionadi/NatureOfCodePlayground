using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.AI.NeuralNetworks.NEAT
{
    /// <summary>
    /// class to hold all the genomes of a given species
    /// </summary>
    public class Species
    {
        /// <summary>
        /// keep a local copy of the first member of this species 
        /// </summary>
        Genome Leader;

        /// <summary>
        /// pointers to all the genomes within this species 
        /// </summary>
        List<Genome> Members;

        /// <summary>
        /// the species needs an identification number 
        /// </summary>
        int SpeciesID;

        /// <summary>
        /// best fitness found so far by this species 
        /// </summary>
        double BestFitness;

        /// <summary>
        /// generations since fitness has improved, we can use this info to kill off a species if required 
        /// </summary>
        int GenerationssNoImprovement;

        /// <summary>
        /// age of species 
        /// </summary>
        int Age;

        /// <summary>
        /// how many of this species should be spawned for the next population 
        /// </summary>
        double SpawnsRequired;

        /// <summary>
        /// this ctor creates an instance of a new species. A local copy of  
        ///  the initializing genome is kept in m_Leader and the first element 
        ///  of this.Members is a pointer to that genome.
        /// </summary>
        /// <param name="FirstOrg"></param>
        /// <param name="SpeciesID"></param>
        public Species(Genome FirstOrg, int SpeciesID)
        {
            this.Members = new List<Genome>();
            this.Members.Add(FirstOrg);
            this.Leader = FirstOrg;

            this.SpeciesID = SpeciesID;
            this.BestFitness = FirstOrg.GetFitnessValue();
            this.GenerationssNoImprovement = 0;
            this.Age = 0;
            this.SpawnsRequired = 0;
        }
 
        /// <summary>
        /// This function adjusts the fitness of each individual by first   
        ///  examining the species age and penalising if old, boosting if young.   
        ///  Then we perform fitness sharing by dividing the fitness by the number   
        ///  of individuals in the species. This ensures a species does not grow    
        ///  too large
        /// </summary>
        public void AdjustFitnesses()
        {
            double total = 0;

            for (int gen = 0; gen < this.Members.Count; ++gen)
            {
                double fitness = this.Members[gen].GetFitnessValue();

                //boost the fitness scores if the species is young   
                if (this.Age < NeuralNetworkParams.YoungBonusAgeThreshhold)
                {
                    fitness *= NeuralNetworkParams.YoungFitnessBonus;
                }

                //punish older species   
                if (this.Age > NeuralNetworkParams.OldAgeThreshold)
                {
                    fitness *= NeuralNetworkParams.OldAgePenalty;
                }

                total += fitness;

                //apply fitness sharing to adjusted fitnesses   
                double AdjustedFitness = fitness / this.Members.Count;

                this.Members[gen].SetAdjFitness(AdjustedFitness);

            }
        }

        /// <summary>
        /// this function adds a new member to this species and updates the member variables according
        /// </summary>
        public void AddMember(Genome NewMember)
        {
            //is the new member's fitness better than the best fitness? 
            if (NewMember.GetFitnessValue() > this.BestFitness)
            {
                this.BestFitness = NewMember.GetFitnessValue();

                this.GenerationssNoImprovement = 0;

                this.Leader = NewMember;
            }


            this.Members.Add(NewMember);
        }

        /// <summary>
        /// this functions clears out all the members from the last generation, updates the age and gens no improvement.
        /// </summary>
        public void Purge()
        {
            this.Members.Clear();

            //update age etc 
            ++this.Age;

            ++this.GenerationssNoImprovement;

            this.SpawnsRequired = 0;
        }

        /// <summary>
        /// Simply adds up the expected spawn amount for each individual in the species to calculate the amount of offspring this species should spawn
        /// calculates how many offspring this species should
        /// </summary>    
        public void CalculateSpawnAmount()
        {
            for (int gen = 0; gen < this.Members.Count; ++gen)
            {
                this.SpawnsRequired += this.Members[gen].GetAmountToSpawn();

            }
        }

        /// <summary>
        /// spawns an individual from the species selected at random  from the best CParams::dSurvivalRate percent 
        /// </summary>
        /// <returns> Returns a random genome selected from the best individuals</returns>
        public Genome Spawn()
        {
            Genome baby;

            if (this.Members.Count== 1)
            {
                baby = this.Members[0];
            }

            else
            {
                int MaxIndexSize = (int)(NeuralNetworkParams.SurvivalRate * this.Members.Count) + 1;

                int TheOne = RandomProvider.RND.Next(0, MaxIndexSize);

                baby = this.Members[TheOne];
            }

            return baby;
        }


        //--------------------------------------accessor methods  
        public Genome GetLeader() {return Leader;}

        public double NumToSpawn() {return this.SpawnsRequired;}

        public int NumMembers() {return Members.Count;} 
   
        public int GensNoImprovement() {return this.GenerationssNoImprovement;} 
 
        public int ID() {return this.SpeciesID;} 
 
        public double SpeciesLeaderFitness() {return this.Leader.GetFitnessValue();} 
   
        public double GetBestFitness() {return this.BestFitness;} 
 
        public int GetAge() {return Age;} 
 
        public bool IsGreaterThan(Species specie)
        {
            return this.BestFitness > specie.BestFitness;
        }
    }
}
