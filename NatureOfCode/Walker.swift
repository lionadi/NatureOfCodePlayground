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
protocol PWalker : PObjectBaseBasic
{
    
    /**
    The implementor of the Walker class must have an Walker object
    */
    var WalkerObject : Walker { get set }
    
    /**
    Implement this method to render the walker at a certain position
    */
    func RenderWalkerByPosition( position: CGPoint);
    
    
    /**
    Use this method to set a target for the Walker to aim at, to move towards to
    */
    func SetWalkerTarget(target : CGPoint);
    
    /**
    Use this method to implement logic related to make the Walker to give you the next position where the implementor should be at
    */
    mutating func StepWalker();
    
    /**
    Use this method to implement logic related to make the Walker to give you the next position where the implementor should be at and aimed at the target, moving towardst he target.
    */
    mutating func StepWalkerByTarget(target : CGPoint);
}

// Walker base class that gives functionality to some object. Use it to move it randomly somewhere
public class Walker : RandomBaseComplete
{
    /// Current X position
    var PositionX : CGFloat = 0;
    
    /// Current Y position
    var PositionY : CGFloat = 0;
    
    var Target : CGPoint = CGPointZero;
    
    var PerlinNoiseTime_PositionX : CGFloat = 0;
    var PerlinNoiseTime_PositionY : CGFloat = 10000;

    
    /// Probality factor walking towards a target
    var ProbalitityFactor : Float = 0.9;
    
    
    init(width : CGFloat, height : CGFloat)
    {
        super.init();
        self.PositionX = width / 2;
        self.PositionY = height / 2;
        self.Width = width;
        self.Height = height;
        self.RandomNumberModeValue = RandomNumberMode.Uniform;
    }
    
    init(positionX : CGFloat, positionY : CGFloat, width : CGFloat, height : CGFloat)
    {
        super.init();
        self.PositionX = positionX;
        self.PositionY = positionY;
        self.Width = width;
        self.Height = height;
        self.RandomNumberModeValue = RandomNumberMode.Uniform;
    }
    
    /// Set a probability factor when to start to walk towards the target
    func SetProbalitiyFactor(factor : Float)
    {
        self.ProbalitityFactor = factor;
    }
    
    override func UniformCalculations()
    {
        super.UniformCalculations();
        if( self.Target == CGPointZero)
        {
            var choice = RandomNumberGenerator.GetRandomUInt32(4);
        
            switch(choice)
                {
            case 0:
                self.PositionX += RandomNumberGenerator.GetRandomCGFloat(2);
            case 1:
                self.PositionX -= RandomNumberGenerator.GetRandomCGFloat(2);
            case 2:
                self.PositionY += RandomNumberGenerator.GetRandomCGFloat(2);
            case 3:
                self.PositionY -= RandomNumberGenerator.GetRandomCGFloat(2);
            default:
                self.PositionX++;
            }
        } else
        {
            MoveWalkerTowardsTarget();
        }
    }
    
    func MoveWalkerTowardsTarget()
    {
        var choice : Float = RandomNumberGenerator.GetRandomPositiveFloat(1);
        
        if(choice < self.ProbalitityFactor)
        {
            var xdir = (self.Target.x - self.PositionX);
            var ydir = (self.Target.y - self.PositionY);
            
            if(xdir != 0)
            {
                xdir /= abs(xdir);
            }
            
            if(ydir != 0)
            {
                ydir /= abs(ydir);
            }
            
            self.PositionX += xdir;
            self.PositionY += ydir;
        } else
        {
            self.PositionX += RandomNumberGenerator.GetRandomCGFloat(2);
            self.PositionY += RandomNumberGenerator.GetRandomCGFloat(2);
        }
    }
    
    override func GaussianCalculations()
    {
        super.GaussianCalculations();
    }
    
    override func PerlinNoiseCalculations()
    {
        super.PerlinNoiseCalculations();
        
        
        var tempX = CGFloat(self.PerlinNoiseCalculator.perlin1DValueForPoint(Float(self.PerlinNoiseTime_PositionX)));
        var tempY = CGFloat(self.PerlinNoiseCalculator.perlin1DValueForPoint(Float(self.PerlinNoiseTime_PositionY)));
        
        if(tempX < 0)
        {
            tempX *= -1;
        }
        
        if(tempY < 0)
        {
            tempY *= -1;
        }
        self.PositionX = PerlinNoiseTool.MapCGFloat(tempX, perlinNoiseMinValue: 0, perlinNoiseMaxValue: 1, targetMinValue: 0, targetMaxValue: self.Width);
        
        self.PositionY = PerlinNoiseTool.MapCGFloat(tempY, perlinNoiseMinValue: 0, perlinNoiseMaxValue: 1, targetMinValue: 0, targetMaxValue: self.Height);
        
        self.PerlinNoiseTime_PositionX += 0.1;
        self.PerlinNoiseTime_PositionY += 0.1;
        
        if( self.Target != CGPointZero)
        {
            self.MoveWalkerTowardsTarget();
        }
    }
    
    /// Makes the walker object to take a step in a direction
    /*public func step() -> CGPoint
    {
        self.target = CGPointZero;
        self.UniformCalculations();
        
        
        self.constrain();
        
        return(CGPointMake(self.positionX, self.positionY));
    }*/
    
    public func SetTarget(target : CGPoint)
    {
        self.Target = target;
    }
    
    /// Makes the walker object to take a step towards the target
    /*public func step(target : CGPoint) -> CGPoint
    {
        self.Target = target;
        self.UniformCalculations();
        
        self.constrain();
        
        return(CGPointMake(self.positionX, self.positionY));
    }*/
    
    /// Return current position of the walker
    public func GetCurentPosition() -> CGPoint
    {
        return(CGPointMake(self.PositionX, self.PositionY));
    }
    
    /// Constrain the walker position to the defined area
    override func Constrain()
    {
        super.Constrain();
        if(self.PositionX < 0)
        {
            self.PositionX = 0;
        }
        if(self.PositionX > self.Width)
        {
            self.PositionX = self.Width;
        }
        if(self.PositionY < 0)
        {
            self.PositionY = 0;
        }
        
        if(self.PositionY > self.Height)
        {
            self.PositionY = self.Height;
        }
        
    }
}