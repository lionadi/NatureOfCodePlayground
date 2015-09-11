using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Assets.Scripts.AI
{
    public class Genome
    {
        public List<Vector2> Genes;
        public float Fitness { get; set; }
        // The maximum strength of the forces

        public Genome(int genesCount)
        {
            this.InitializeGenes(genesCount);
        }

        public void InitializeGenes(int genesCount)
        {
            this.Fitness = 0;
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
                this.Genes.Add((new Vector2(UnityEngine.Mathf.Cos(angle), UnityEngine.Mathf.Sin(angle))) * UnityEngine.Random.Range(0, AIConstants.maxforce));
                index++;
            } while (index < genesCount);
            this.Genes[0].Normalize();
        }

    }
}
