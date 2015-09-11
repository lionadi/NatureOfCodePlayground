using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AIEngine.DataStructures
{
    public interface IMovingHost
    {
        IDNA Dna { get; set; }

        /// <summary>
        /// FITNESS FUNCTION
        /// </summary>
        void EvalutateFitness();

        /// <summary>
        /// Run in relation to all the obstacles
        /// If I'm stuck, don't bother updating or checking for intersection
        /// </summary>
        /// <param name="targets"></param>
        void Run();

        float GetFitness();

        IDNA GetDNA();
    }
}
