using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace AIEngine.DataStructures
{
    public class DNA : IDNA
    {
        public List<Vector2> Genes { get; set; }
        public float Fitness { get; set; }
        public String Target { get; set; }

        // The maximum strength of the forces
        float maxforce = 0.1F;

        public DNA()
        {
            this.Genes = new List<Vector2>();
        }

        public DNA(List<Vector2> genes)
        {
            this.Genes = genes;
        }

        public DNA(int genesCount)
        {
            this.InitializeGenes(genesCount);
        }

        public void InitializeGenes(int genesCount)
        {
            this.Genes = new List<Vector2>();
            if (genesCount < 0)
                throw new Exception("The genesCount must be larger than 0");
            else if (genesCount == 0)
                return;

            int index = 0;
            do
            {
                float angle = UnityEngine.Random.Range(0, AIConstants.TWO_PI);
                //float angle = (float)RandomProvider.GetRandomNumber(RandomProvider.RND, -AIEngine.AIConstants.TWO_PI, AIEngine.AIConstants.TWO_PI);
                this.Genes.Add((new Vector2(UnityEngine.Mathf.Cos(angle), UnityEngine.Mathf.Sin(angle))) * UnityEngine.Random.Range(0, this.maxforce));
                index++;
            } while (index < genesCount);
            this.Genes[0].Normalize();
        }

        public void EvalutateFitness()
        {
            //int score = 0;
            //for (int i = 0; i < this.Genes.Count; i++) 
            //{
            //    //if (this.Target.LastIndexOf(this.Genes[i]) >= 0) {
            //    //    score++;
            //    //}
            //    if (this.Target[i] == this.Genes[i])
            //        score++;
            //}

            //this.Fitness = (float)score/this.Target.Length;
        }

        public IDNA Crossover(IDNA partner)
        {
            DNA child = new DNA(0);
            int midpoint = RandomProvider.RND.Next(0, this.Genes.Count -1);

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
                float rndValue = UnityEngine.Random.Range(0, 1);

                if (rndValue < mutationRate)
                {
                    float angle = UnityEngine.Random.Range(0, AIConstants.TWO_PI);
                    this.Genes[i] = ((new Vector2(UnityEngine.Mathf.Cos(angle), UnityEngine.Mathf.Sin(angle))) * UnityEngine.Random.Range(0, this.maxforce));
                    if (i == 0) 
                        this.Genes[i].Normalize();
                }
            }
        }

        public override string ToString()
        {
            StringBuilder dnaSequnces = new StringBuilder();
            for (int i = 0; i < this.Genes.Count; i++)
            {
                dnaSequnces.AppendLine(this.Genes[i].ToString());
            }
            return dnaSequnces.ToString();
        }
    }
}
