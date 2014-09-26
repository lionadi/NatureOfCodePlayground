//
//  CommonTools.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 24/09/14.
//  Copyright (c) 2014 Test. All rights reserved.
//

import Foundation

/// Static value for calculating float based random values
let ARC4RANDOM_MAX  : Float = 0x100000000;

/// This a Random Number generator helper
public struct RandomNumberGenerator {
    
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