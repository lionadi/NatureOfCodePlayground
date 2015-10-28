using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Assets.Scripts.AI.NeuralNetworks.NEAT
{
    public class SplitDepth
    {
        public double Value;

        public int Depth;

        public SplitDepth(double value, int depth)
        {
            this.Value = value;
            this.Depth = depth;
        }
    }
}
