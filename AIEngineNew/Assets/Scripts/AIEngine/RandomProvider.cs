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


    /// <summary>
    /// returns a random number with a normal distribution. See method at
    /// http://www.taygeta.com/random/gaussian.html
    /// </summary>
    /// <param name="mean"></param>
    /// <param name="standard_deviation"></param>
    /// <returns></returns>
    public static float RandGaussian(float mean = 0.0F, float standard_deviation = 1.0F)
    {
        float x1, x2, w, y1;
        float y2 = 0;
        int use_last = 0;

        if (use_last > 0)               /* use value from previous call */
        {
            y1 = y2;
            use_last = 0;
        }
        else
        {
            do
            {
                x1 = 2.0F * ((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1)) - 1.0F;
                x2 = 2.0F * ((float)RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1)) - 1.0F;
                w = x1 * x1 + x2 * x2;
            }
            while (w >= 1.0);

            w = UnityEngine.Mathf.Sqrt((-2.0F * UnityEngine.Mathf.Log(w)) / w);
            y1 = x1 * w;
            y2 = x2 * w;
            use_last = 1;
        }

        return (mean + y1 * standard_deviation);
    }

    public static double RandomClamped() { return RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1) - RandomProvider.GetRandomNumber(RandomProvider.RND, 0, 1); }
}
