//
//  Walker.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 24/09/14.
//  Copyright (c) 2014 Adrian Simionescu. All rights reserved.
//

import Foundation


/**
A protocol to conform to the class that implements the Walker class.
*/
protocol pWalker : pObjectBaseBasic
{
    /**
        The implementor of the Walker class must have an Walker object
    */
    var walker : Walker { get set }
    
    /**
    Implement this method to render the walker at a certain position
    */
    func renderWalkerByPosition( position: CGPoint);
    
    
    /**
    Use this method to set a target for the Walker to aim at, to move towards to
    */
    func setWalkerTarget(target : CGPoint);
    
    /**
    Use this method to implement logic related to make the Walker to give you the next position where the implementor should be at
    */
    mutating func stepWalker();
    
    /**
    Use this method to implement logic related to make the Walker to give you the next position where the implementor should be at and aimed at the target, moving towardst he target.
    */
    mutating func stepWalkerByTarget(target : CGPoint);
}

// Walker base class that gives functionality to some object. Use it to move it randomly somewhere
public class Walker : RandomBaseComplete
{
    /// Current X position
    var positionX : CGFloat = 0;
    
    /// Current Y position
    var positionY : CGFloat = 0;
    
    var target : CGPoint = CGPointZero;
    
    var perlinNoiseTime_PositionX : CGFloat = 0;
    var perlinNoiseTime_PositionY : CGFloat = 10000;

    
    /// Probality factor walking towards a target
    var probalitityFactor : Float = 0.5;
    
    
    init(width : CGFloat, height : CGFloat)
    {
        super.init();
        self.positionX = width / 2;
        self.positionY = height / 2;
        self.width = width;
        self.height = height;
        self.randomNumberMode = RandomNumberMode.Uniform;
    }
    
    init(positionX : CGFloat, positionY : CGFloat, width : CGFloat, height : CGFloat)
    {
        super.init();
        self.positionX = positionX;
        self.positionY = positionY;
        self.width = width;
        self.height = height;
        self.randomNumberMode = RandomNumberMode.Uniform;
    }
    
    /// Set a probability factor when to start to walk towards the target
    func setProbalitiyFactor(factor : Float)
    {
        self.probalitityFactor = factor;
    }
    
    override func UniformCalculations()
    {
        super.UniformCalculations();
        if( self.target == CGPointZero)
        {
            var choice = RandomNumberGenerator.GetRandomUInt32(4);
        
            switch(choice)
                {
            case 0:
                self.positionX += RandomNumberGenerator.GetRandomCGFloat(2);
            case 1:
                self.positionX -= RandomNumberGenerator.GetRandomCGFloat(2);
            case 2:
                self.positionY += RandomNumberGenerator.GetRandomCGFloat(2);
            case 3:
                self.positionY -= RandomNumberGenerator.GetRandomCGFloat(2);
            default:
                self.positionX++;
            }
        } else
        {
            var choice : Float = RandomNumberGenerator.GetRandomPositiveFloat(1);
            
            if(choice < self.probalitityFactor)
            {
                var xdir = (target.x - self.positionX);
                var ydir = (target.y - self.positionY);
                
                if(xdir != 0)
                {
                    xdir /= abs(xdir);
                }
                
                if(ydir != 0)
                {
                    ydir /= abs(ydir);
                }
                
                self.positionX += xdir;
                self.positionY += ydir;
            } else
            {
                self.positionX += RandomNumberGenerator.GetRandomCGFloat(2);
                self.positionY += RandomNumberGenerator.GetRandomCGFloat(2);
            }
        }
    }
    
    override func GaussianCalculations()
    {
        super.GaussianCalculations();
    }
    
    override func PerlinNoiseCalculations()
    {
        super.PerlinNoiseCalculations();
        
        var x = CGFloat(self.perlinNoise.perlin1DValueForPoint(Float(self.perlinNoiseTime_PositionX)));
        self.positionX = PerlinNoiseTool.MapCGFloat(CGFloat(self.perlinNoise.perlin1DValueForPoint(Float(self.perlinNoiseTime_PositionX))), perlinNoiseMinValue: 0, perlinNoiseMaxValue: 1, targetMinValue: 0, targetMaxValue: self.width);
        
        self.positionY = PerlinNoiseTool.MapCGFloat(CGFloat(self.perlinNoise.perlin1DValueForPoint(Float(self.perlinNoiseTime_PositionY))), perlinNoiseMinValue: 0, perlinNoiseMaxValue: 1, targetMinValue: 0, targetMaxValue: self.height);
        
        self.perlinNoiseTime_PositionX += 0.01;
        self.perlinNoiseTime_PositionY += 0.01;
    }
    
    /// Makes the walker object to take a step in a direction
    /*public func step() -> CGPoint
    {
        self.target = CGPointZero;
        self.UniformCalculations();
        
        
        self.constrain();
        
        return(CGPointMake(self.positionX, self.positionY));
    }*/
    
    public func setTarget(target : CGPoint)
    {
        self.target = target;
    }
    
    /// Makes the walker object to take a step towards the target
    /*public func step(target : CGPoint) -> CGPoint
    {
        self.target = target;
        self.UniformCalculations();
        
        self.constrain();
        
        return(CGPointMake(self.positionX, self.positionY));
    }*/
    
    /// Return current position of the walker
    public func GetCurentPosition() -> CGPoint
    {
        return(CGPointMake(self.positionX, self.positionY));
    }
    
    /// Constrain the walker position to the defined area
    override func constrain()
    {
        super.constrain();
        if(self.positionX < 0)
        {
            self.positionX = 0;
        }
        if(self.positionX > self.width)
        {
            self.positionX = self.width;
        }
        if(self.positionY < 0)
        {
            self.positionY = 0;
        }
        
        if(self.positionY > self.height)
        {
            self.positionY = self.height;
        }
        
    }
}