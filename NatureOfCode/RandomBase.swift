//
//  RandomBase.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 30/09/14.
//  Copyright (c) 2014 Adrian Simionescu. All rights reserved.
//

import Foundation

protocol pRandomBase
{
    var randomNumberMode : RandomNumberMode { get set };
    
    func setRandomNumberMode( randomNumberMode : RandomNumberMode);
}

protocol pRandomBaseBasic : pRandomBase
{
    var width : CGFloat { get set };
    var height : CGFloat { get set };
    
    func setConstrainsRange( width : CGFloat, height: CGFloat);
}

protocol pRandomBaseUniform : pRandomBaseBasic
{
    mutating func UniformCalculations();
}

protocol pRandomBaseGaussian : pRandomBaseBasic
{
    mutating func GaussianCalculations();
}

protocol pRandomBasePerlinNoise : pRandomBaseBasic
{
    mutating func PerlinNoiseCalculations();
}

protocol pRandomBaseComplete : pRandomBaseUniform, pRandomBaseGaussian, pRandomBasePerlinNoise
{
    
}

public class RandomBase : pRandomBaseBasic
{
    var randomNumberMode : RandomNumberMode;
    var width : CGFloat = 0.0;
    var height : CGFloat = 0.0;
    
    init()
    {
        self.randomNumberMode = RandomNumberMode.Uniform;
    }
    
    func setRandomNumberMode( randomNumberMode : RandomNumberMode)
    {
        self.randomNumberMode = randomNumberMode;
    }
    
    func setConstrainsRange( width : CGFloat, height: CGFloat)
    {
        self.width = width;
        self.height = height;
    }
}