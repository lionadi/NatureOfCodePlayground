using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Assets.Scripts.AI;

    namespace Assets.Scripts.AI
{
    class Species
    {
        //this is the genome all other genomes in the population are
        //compared to see if they should be included in this species or not
        Host SampleGenome;

        List<Host> Members;

        //the number of generations that has passed without the fittest
        //member in the species showing an improvement.
        int numGensNoImprovement;

        float expectedNumberOfOffspring;

        float bestEverFitness;

        //the combined fitness scores of every member
        float totalFitness;

        //it's often useful to have an identity number for the species
        int id;



        public Species(Host firstMember, int id)
        {
            this.Members = new List<Host>();
            this.id = id;
            this.SampleGenome = firstMember;
            this.expectedNumberOfOffspring = 0;
            this.numGensNoImprovement = 0;
            Members.Add(firstMember);

            bestEverFitness = firstMember.Fitness();

            totalFitness += firstMember.Fitness();
        }

        public void AddGenome(Host genome)
        {
            Members.Add(genome);

            totalFitness += genome.Fitness();

            if (genome.Fitness() > bestEverFitness)
            {
                bestEverFitness = genome.Fitness();

                //fitness has improved so this can be reset
                numGensNoImprovement = 0;
            }
        }

        /// <summary>
        /// selects a genome from the species using tournament selection. 
        /// this method uses tournament selection to spawn genomes from the 
        ///  species.
        ///  
        ///  As it is set presently it uses a high selection pressure.
        /// </summary>
        /// <returns></returns>
        public Host SpawnGenome()
        {
            //first chose the number in the tournament. selection_pressure must be
            //between zero and 1.0
            int NumInComp = 0; float selection_pressure = 0.5F;

            while (NumInComp < 1)
            {
                NumInComp = (int)(NumMembers() * selection_pressure);

                selection_pressure += 0.1F;
            }

            int winner = 0;

            for (int i = 0; i < NumInComp; ++i)
            {
                int ThisTry = RandomProvider.RND.Next(0, Members.Count() - 1);

                if (Members[ThisTry].Fitness() > Members[winner].Fitness())
                {
                    winner = i;
                }
            }

            return Members[winner];
        }


        /// <summary>
        /// makes sure the sample genome is always the genome with the highest fitness found so far
        /// </summary>
        public void UpdateSampleGenome()
        {
            if (Members.Count > 0)
            {
                if (Members.Last().Fitness() > SampleGenome.Fitness())
                {
                    SampleGenome = Members.Last();
                }

                else
                {
                    Members[0] = SampleGenome;
                }
            }

            ++numGensNoImprovement;
        }

        public void Clear()
        {
            SampleGenome = Members[0];
            expectedNumberOfOffspring = 0.0F;
            Members.Clear();
            totalFitness = 0.0F;
        }

        public Host Sample() { return SampleGenome; }

        public float ExpectedOffspring() { return expectedNumberOfOffspring; }

        /// <summary>
        /// adjusts the fitness scores so they are set to the value of their expected number of offspring
        /// </summary>
        /// <param name="totalFitnessForPopoulation"></param>
        /// <param name="PopSize"></param>
        public void SetExpectedOffspring(float totalFitnessForPopoulation, int PopSize)
        {
            //check that we have some fitness scores to work with
            if (totalFitnessForPopoulation == 0.0) return;

            expectedNumberOfOffspring = 0.0F;

            for (int gen = 0; gen < Members.Count(); ++gen)
            {
                float ExpectedForThisIndividual =

                  (Members[gen].Fitness() / totalFitnessForPopoulation) * PopSize;

                expectedNumberOfOffspring += ExpectedForThisIndividual;
            }
        }

        public int GenerationsNoImprovement() {return numGensNoImprovement;}

        public bool Empty() {return (Members.Count() == 0);}

        public float BestEverFitness() {return bestEverFitness;}
        public float TotalFitness() {return totalFitness;}

        /// <summary>
        /// this method applies explicit fitness sharing by dividing each member's
        ///  fitness by the number of members in the species
        /// </summary>
        public void FitnessShare()
        {
            float NewTotal = 0.0F;

            //divide each member's fitness by the number in the species
            for (int m = 0; m < Members.Count(); ++m)
            {
                Members[m].SetFitness(Members[m].Fitness() / NumMembers());

                NewTotal += Members[m].Fitness();
            }

            totalFitness = NewTotal;
        }

        public int ID() {return id;}
        int NumMembers() {return Members.Count();}

        public bool IsLessThan(Species species)
        {
            return (this.BestEverFitness() < species.BestEverFitness());
        }

}
}
