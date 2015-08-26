using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AIEngine.DataStructures
{
    public interface IDNA
    {
        List<Char> Genes { get; set; }
        float Fitness { get; set; }
        String Target { get; set; }

        void InitializeGenes(int genesCount);
        void EvalutateFitness();
        IDNA Crossover(IDNA partner);
        void Mutate(float mutationRate);
    }
}
