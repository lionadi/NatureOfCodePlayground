using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace AIEngine.DataStructures
{
    public interface IDNA
    {
        List<Vector2> Genes { get; set; }
        float Fitness { get; set; }
        String Target { get; set; }

        void InitializeGenes(int genesCount);
        
        IDNA Crossover(IDNA partner);
        void Mutate(float mutationRate);
    }
}
