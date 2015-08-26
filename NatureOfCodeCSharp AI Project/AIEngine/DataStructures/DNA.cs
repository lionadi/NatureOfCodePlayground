using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AIEngine.DataStructures
{
    public class DNA : IDNA
    {
        public List<Char> Genes { get; set; }
        public float Fitness { get; set; }
        public String Target { get; set; }

        public DNA()
        {
            this.Genes = new List<char>();
        }

        public DNA(int genesCount, String target)
        {
            this.InitializeGenes(genesCount);
            this.Target = target;
        }

        public void InitializeGenes(int genesCount)
        {
            this.Genes = new List<char>();
            if (genesCount < 0)
                throw new Exception("The genesCount must be larger than 0");
            else if (genesCount == 0)
                return;

            int index = 0;
            do
            {
                this.Genes.Add((char)RandomProvider.RND.Next(32, 128));
                index++;
            } while (index < genesCount);
        }

        public void EvalutateFitness()
        {
            int score = 0;
            for (int i = 0; i < this.Genes.Count; i++) 
            {
                //if (this.Target.LastIndexOf(this.Genes[i]) >= 0) {
                //    score++;
                //}
                if (this.Target[i] == this.Genes[i])
                    score++;
            }

            this.Fitness = (float)score/this.Target.Length;
        }

        public IDNA Crossover(IDNA partner)
        {
            DNA child = new DNA(0, this.Target);
            int midpoint = RandomProvider.RND.Next(this.Genes.Count);

            for(int x = 0; x < this.Genes.Count; ++x)
            {
                if (x > midpoint)
                    child.Genes.Insert(x,this.Genes[x]);
                else
                    child.Genes.Insert(x, partner.Genes[x]);
            }

            return child;
        }

        public void Mutate(float mutationRate)
        {
            for (int i = 0; i < this.Genes.Count; i++) {
                float rndValue = (float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1);
                if (rndValue < mutationRate)
                {
                    this.Genes[i] = (char)RandomProvider.RND.Next(32, 128);
                }
            }
        }

        public override string ToString()
        {
            return new StringBuilder().Append(this.Genes.ToArray()).ToString();
        }
    }
}
