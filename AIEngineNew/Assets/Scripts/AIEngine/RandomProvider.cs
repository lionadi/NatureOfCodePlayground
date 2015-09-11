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

    /// <summary>
    /// Re-maps a number from one range to another.
    /// </summary>
    /// <param name="value">the incoming value to be converted</param>
    /// <param name="sourceMinValue">lower bound of the value's current range</param>
    /// <param name="sourceMaxValue">upper bound of the value's current range</param>
    /// <param name="targetMinValue">lower bound of the value's target range</param>
    /// <param name="targetMaxValue">upper bound of the value's target range</param>
    /// <returns></returns>
    public static float Map(float value, float sourceMinValue, float sourceMaxValue, float targetMinValue, float targetMaxValue)
    {
        return targetMinValue + (targetMaxValue - targetMinValue) * ((value - sourceMinValue) / (sourceMaxValue - sourceMinValue));
    }
}
