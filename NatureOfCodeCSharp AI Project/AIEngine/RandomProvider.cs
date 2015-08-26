using System;
using System.Threading;

public static class RandomProvider
{
    private static int seed = Environment.TickCount;

    public static Random RND = new Random(RandomProvider.seed);

    public static double GetRandomNumber(Random random, double minimum, double maximum)
    {
        return random.NextDouble() * (maximum - minimum) + minimum;
    }
}
