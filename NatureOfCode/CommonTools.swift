//
//  CommonTools.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 24/09/14.
//  Copyright (c) 2014 Test. All rights reserved.
//

import Foundation

public struct RandomNumberGenerator {
    public static func GetRandomFloat( maxValue : UInt32) -> Float
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
        
        return finalPosition;
    }
    
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
    
    public static func GetRandomUInt32( maxValue : UInt32) -> UInt32
    {
        return UInt32(arc4random_uniform(maxValue));
    }
}