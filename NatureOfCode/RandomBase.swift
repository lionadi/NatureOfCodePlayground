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
    func doCalculations();
    func constrain();
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
    var perlinNoise : PerlinNoise { get set };
    
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
    
    func constrain()
    {
        
    }
    
    func doCalculations() {
        self.constrain();
    }
}

public class RandomBaseComplete : RandomBase, pRandomBaseComplete
{
    var perlinNoise : PerlinNoise = PerlinNoise(seed: 1);
    
    override func doCalculations()
    {
        super.doCalculations();
        switch(self.randomNumberMode)
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
        
        self.constrain();
    }
    
    override func constrain()
    {
        super.constrain();
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

public class RandomBasePerlinNoise : RandomBase, pRandomBasePerlinNoise
{
    var perlinNoise : PerlinNoise = PerlinNoise(seed: 1);
    
    override func doCalculations()
    {
        super.doCalculations();
        self.PerlinNoiseCalculations();
        
    }
    
    func PerlinNoiseCalculations()
    {
        
    }
}

public class RandomBaseGaussian : RandomBase, pRandomBaseGaussian
{
    override func doCalculations()
    {
        super.doCalculations();
        self.GaussianCalculations();
        
    }
    
    func GaussianCalculations()
    {
        
    }
}

public class RandomBaseUniform : RandomBase, pRandomBaseUniform
{
    override func doCalculations()
    {
        super.doCalculations();
        self.UniformCalculations();
        
    }
    
    func UniformCalculations()
    {
        
    }
}

