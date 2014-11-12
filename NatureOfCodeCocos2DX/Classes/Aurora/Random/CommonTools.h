#ifndef NatureOfCodeCocos2DX_CommonTools_h
#define NatureOfCodeCocos2DX_CommonTools_h
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <utility>

#include "..\Globals\GlobalDatatypes.h"
#include "..\..\Perlin Noise\noise\src\noise.h"
using namespace noise;
using namespace Aurora::DataTypes;

namespace Aurora {
    namespace Random {

#define ARC4RANDOM_MAX = 0x100000000;

		struct PerlinNoiseTool
		{
		    static Float Map( Float perlinNoiseValue, Float perlinNoiseMinValue, Float perlinNoiseMaxValue, Float targetMinValue, Float targetMaxValue)
		    {
		        return targetMinValue + (targetMaxValue - targetMinValue) * ((perlinNoiseValue - perlinNoiseMinValue) / (perlinNoiseMaxValue - perlinNoiseMinValue));
		    }
		};

		struct RandomNumberGenerator {
			static Float nextNextGaussian;
			static bool haveNextNextGaussian;

			static Float GetGaussianRandomNumber(Float m, Float s)
			{
			 
			    if (haveNextNextGaussian) {
			        haveNextNextGaussian = false;
			        return nextNextGaussian;
			    } else {
			        Float v1, v2, s;
			        do {
			            v1 = 2 * RandomNumberGenerator::GetRandomPositiveFloat(1) - 1;   // between -1.0 and 1.0
			            v2 = 2 * RandomNumberGenerator::GetRandomPositiveFloat(1) - 1;   // between -1.0 and 1.0
			            s = v1 * v1 + v2 * v2;
			        } while (s >= 1 || s == 0);
			        Float multiplier  = sqrt(-2 * log(s)/s);
			        nextNextGaussian = v2 * multiplier;
			        haveNextNextGaussian = true;
			        return v1 * multiplier;
			    }
			}

			// This will generate a number from 0.0 to 1.0, inclusive.
			static Float GetRandomPositiveFloat()
			{
				srand(time(NULL));
			    return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
			}

			// This will generate a number from 0.0 to some arbitrary float, X:
			static Float GetRandomPositiveFloat(Float  maxValue)
			{
				srand(time(NULL));
			    return (static_cast <Float> (rand()) / (static_cast <Float> (RAND_MAX/maxValue)));
			}

			// This will generate a number from some arbitrary LO to some arbitrary HI:
			static Float GetRandomPositiveFloat(Float minValue, Float  maxValue)
			{
				srand(time(NULL));
			    return (minValue + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxValue-minValue))));
			}

			static Float GetRandomFloat( Float maxValue) 
			{
			    Float minus  = -1;
			    
			    Float sign = RandomNumberGenerator::GetRandomPositiveFloat();
			    Float position = RandomNumberGenerator::GetRandomPositiveFloat(maxValue);
			    
			    Float finalPosition;
			    if(sign <= 0)
			    {
			        finalPosition = Float(position) * minus;
			    } else
			    {
			        finalPosition = Float(position);
			    }
			    
			    return finalPosition;
			}

			static Float GetRandomFloat(Float minValue, Float maxValue) 
			{
			    Float minus  = -1;
			    
			    Float sign = RandomNumberGenerator::GetRandomPositiveFloat();
			    Float position = RandomNumberGenerator::GetRandomPositiveFloat(minValue, maxValue);
			    
			    Float finalPosition;
			    if(sign <= 0)
			    {
			        finalPosition = Float(position) * minus;
			    } else
			    {
			        finalPosition = Float(position);
			    }
			    
			    return finalPosition;
			}
		};

   }; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora

#endif