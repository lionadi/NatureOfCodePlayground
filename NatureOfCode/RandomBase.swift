//
//  RandomBase.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 30/09/14.
//  Copyright (c) 2014 Adrian Simionescu. All rights reserved.
//

import Foundation

protocol RandomBaseBasic
{
    var randomNumberMode : RandomNumberMode { get set };
    var width : CGFloat { get set };
    var height : CGFloat { get set };
    
    func setRandomNumberMode( randomNumberMode : RandomNumberMode);
    func setConstrainsRange( width : CGFloat, height: CGFloat);
}

protocol RandomBaseUniform : RandomBaseBasic
{
    mutating func UniformCalculations();
}

protocol RandomBaseGaussian : RandomBaseBasic
{
    mutating func GaussianCalculations();
}

protocol RandomBasePerlinNoise : RandomBaseBasic
{
    mutating func PerlinNoiseCalculations();
}

protocol RandomBaseComplete : RandomBaseUniform, RandomBaseGaussian, RandomBasePerlinNoise
{
    
}

public class RandomBase : RandomBaseBasic
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