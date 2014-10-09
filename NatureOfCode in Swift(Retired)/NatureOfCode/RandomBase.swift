//
//  RandomBase.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 30/09/14.
//  Copyright (c) 2014 Adrian Simionescu. All rights reserved.
//

import Foundation

public enum RandomNumberMode
{
    case Uniform, Gaussian, Perlin
}

protocol PRandomBase
{
    var RandomNumberModeValue : RandomNumberMode { get set };
    
    func SetRandomNumberMode( randomNumberMode : RandomNumberMode);
}

protocol PRandomBaseBasic : PRandomBase
{
    var Width : CGFloat { get set };
    var Height : CGFloat { get set };
    
    func SetConstrainsRange( width : CGFloat, height: CGFloat);
    func DoCalculations();
    func Constrain();
    func Normal();
}

protocol PRandomBaseUniform : PRandomBaseBasic
{
    mutating func UniformCalculations();
}

protocol PRandomBaseGaussian : PRandomBaseBasic
{
    mutating func GaussianCalculations();
}

protocol PRandomBasePerlinNoise : PRandomBaseBasic
{
    var PerlinNoiseCalculator : PerlinNoise { get set };
    
    mutating func PerlinNoiseCalculations();
}

protocol PRandomBaseComplete : PRandomBaseUniform, PRandomBaseGaussian, PRandomBasePerlinNoise
{
    
}

public class RandomBase : PRandomBaseBasic
{
    var RandomNumberModeValue : RandomNumberMode;
    var Width : CGFloat = 0.0;
    var Height : CGFloat = 0.0;
    
    init()
    {
        RandomNumberModeValue = RandomNumberMode.Uniform;
    }
    
    func SetRandomNumberMode( randomNumberMode : RandomNumberMode)
    {
        self.RandomNumberModeValue = randomNumberMode;
    }
    
    func SetConstrainsRange( width : CGFloat, height: CGFloat)
    {
        self.Width = width;
        self.Height = height;
    }
    
    func Constrain()
    {
        
    }
    
    func DoCalculations() {
        self.Constrain();
    }

    func Normal() {

    }
}

public class RandomBaseComplete : RandomBase, PRandomBaseComplete
{
    var PerlinNoiseCalculator : PerlinNoise = PerlinNoise(seed: 10);
    
    override func DoCalculations()
    {
        super.DoCalculations();
        switch(self.RandomNumberModeValue)
            {
        case .Uniform:
            self.UniformCalculations();
            
        case .Gaussian:
            self.GaussianCalculations();
        case .Perlin:
            self.PerlinNoiseCalculations();

        default:
            self.UniformCalculations();
        }
        
        self.Constrain();
    }
    
    override func Constrain()
    {
        super.Constrain();
    }
    
    override func Normal()
    {
        
    }
    
    func UniformCalculations()
    {
        
    }
    
    func GaussianCalculations()
    {
        
    }
    
    func PerlinNoiseCalculations()
    {
    }
}

public class RandomBasePerlinNoise : RandomBase, PRandomBasePerlinNoise
{
    var PerlinNoiseCalculator : PerlinNoise = PerlinNoise(seed: 10);
    
    override func DoCalculations()
    {
        super.DoCalculations();
        self.PerlinNoiseCalculations();
        
    }
    
    func PerlinNoiseCalculations()
    {
        
    }
}

public class RandomBaseGaussian : RandomBase, PRandomBaseGaussian
{
    override func DoCalculations()
    {
        super.DoCalculations();
        self.GaussianCalculations();
        
    }
    
    func GaussianCalculations()
    {
        
    }
}

public class RandomBaseUniform : RandomBase, PRandomBaseUniform
{
    override func DoCalculations()
    {
        super.DoCalculations();
        self.UniformCalculations();
        
    }
    
    func UniformCalculations()
    {
        
    }
}

