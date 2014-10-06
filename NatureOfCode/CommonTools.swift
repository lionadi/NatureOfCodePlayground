//
//  CommonTools.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 24/09/14.
//  Copyright (c) 2014 Adrian Simionescu. All rights reserved.
//

import Foundation

/// Static value for calculating float based random values
let ARC4RANDOM_MAX  : Float = 0x100000000;

public struct PerlinNoiseTool
{
    public static func Map( perlinNoiseValue : Float, perlinNoiseMinValue : Float, perlinNoiseMaxValue : Float, targetMinValue : Float, targetMaxValue : Float) -> Float
    {
        return targetMinValue + (targetMaxValue - targetMinValue) * ((perlinNoiseValue - perlinNoiseMinValue) / (perlinNoiseMaxValue - perlinNoiseMinValue));
    }
    
    public static func MapCGFloat( perlinNoiseValue : CGFloat, perlinNoiseMinValue : CGFloat, perlinNoiseMaxValue : CGFloat, targetMinValue : CGFloat, targetMaxValue : CGFloat) -> CGFloat
    {
        return targetMinValue + (targetMaxValue - targetMinValue) * ((perlinNoiseValue - perlinNoiseMinValue) / (perlinNoiseMaxValue - perlinNoiseMinValue));
    }
}



/// This a Random Number generator helper
public struct RandomNumberGenerator {
    
    static var nextNextGaussian : Float = 0;
    static var haveNextNextGaussian : Bool = false;
    
    public static func GetGaussianRandomNumber( m : Float, s : Float) -> Float
    {
        /*
        boxmuller.c           Implements the Polar form of the Box-Muller
        Transformation
        
        (c) Copyright 1994, Everett F. Carter Jr.
        Permission is granted by the author to use
        this software for any application provided this
        copyright notice is preserved.
        ------------------------------------------
        float box_muller(float m, float s)	/* normal random variate generator */
        {				        /* mean m, standard deviation s */
        float x1, x2, w, y1;
        static float y2;
        static int use_last = 0;
        
        if (use_last)		        /* use value from previous call */
        {
        y1 = y2;
        use_last = 0;
        }
        else
        {
        do {
        x1 = 2.0 * ranf() - 1.0;
        x2 = 2.0 * ranf() - 1.0;
        w = x1 * x1 + x2 * x2;
        } while ( w >= 1.0 );
        
        w = sqrt( (-2.0 * log( w ) ) / w );
        y1 = x1 * w;
        y2 = x2 * w;
        use_last = 1;
        }
        
        return( m + y1 * s );
        }
        
        var x1 : Float;
        var x2 : Float;
        var w : Float;
        var y1 : Float;
        var y2 : Float;
        
        do {
        x1 = 2.0 * RandomNumberGenerator.GetRandomPositiveFloat(1) - 1.0;
        x2 = 2.0 * RandomNumberGenerator.GetRandomPositiveFloat(1) - 1.0;
        w = x1 * x1 + x2 * x2;
        } while ( w >= 1.0 );
        w = sqrt( (-2.0 * log( w ) ) / w );
        y1 = x1 * w;
        y2 = x2 * w;
        var a = y1 * s;
        return a + m;
*/
        if (haveNextNextGaussian) {
            haveNextNextGaussian = false;
            return nextNextGaussian;
        } else {
            var v1 : Float, v2 : Float, s : Float;
            do {
                //v1 = 2 * RandomNumberGenerator.GetRandomFloat(1) - 1;   // between -1.0 and 1.0
                //v2 = 2 * RandomNumberGenerator.GetRandomFloat(1) - 1;   // between -1.0 and 1.0
                v1 = 2 * RandomNumberGenerator.GetRandomPositiveFloat(1) - 1;   // between -1.0 and 1.0
                v2 = 2 * RandomNumberGenerator.GetRandomPositiveFloat(1) - 1;   // between -1.0 and 1.0
                s = v1 * v1 + v2 * v2;
            } while (s >= 1 || s == 0);
            var multiplier : Float = sqrt(-2 * log(s)/s);
            nextNextGaussian = v2 * multiplier;
            haveNextNextGaussian = true;
            return v1 * multiplier;
        }
    }
    
    /// Generates a signed float number
    public static func GetRandomFloat( maxValue : Float) -> Float
    {
        var minus : Float = -1;
        
        var sign = arc4random_uniform(1);
        var position = (Float(arc4random()) / ARC4RANDOM_MAX) * maxValue;
        
        var finalPosition : Float;
        if(sign <= 0)
        {
            finalPosition = Float(position) * minus;
        } else
        {
            finalPosition = Float(position);
        }
        
        return finalPosition;
    }
    
    public static func GetRandomPositiveFloat( maxValue : Float) -> Float
    {
        return (Float(arc4random()) / ARC4RANDOM_MAX) * maxValue;
    }
    
    /// Generates a signed float number
    public static func GetRandomCGFloat( maxValue : CGFloat) -> CGFloat
    {
        var minus : Float = -1;
        
        var sign = arc4random_uniform(1);
        var position = (CGFloat(arc4random()) / CGFloat(ARC4RANDOM_MAX)) * maxValue;
        
        var finalPosition : Float;
        if(sign <= 0)
        {
            finalPosition = Float(position) * minus;
        } else
        {
            finalPosition = Float(position);
        }
        
        return CGFloat(finalPosition);
    }
    
    /// Generates a signed Integer number
    public static func GetRandomInt( maxValue : UInt32) -> Int
    {
        var minus : Float = -1;
        
        var sign = arc4random_uniform(1);
        var position = arc4random_uniform(maxValue);
        
        var finalPosition : Float;
        if(sign <= 0)
        {
            finalPosition = Float(position) * minus;
        } else
        {
            finalPosition = Float(position);
        }
        
        return Int(finalPosition);
    }
    
    /// Generates a unsigned signed integer number
    public static func GetRandomUInt32( maxValue : UInt32) -> UInt32
    {
        return UInt32(arc4random_uniform(maxValue));
    }
}