//
//  Walker.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 24/09/14.
//  Copyright (c) 2014 Test. All rights reserved.
//

import Foundation

public enum ColorOption : Int
{
    case Blue = 0
    case Green = 1
    case Yellow = 2
    case Red = 3
}

// Walker base class that gives functionality to some object. Use it to move it randomly somewhere
public class Walker
{
    /// Current X position
    var positionX : CGFloat = 0;
    
    /// Current Y position
    var positionY : CGFloat = 0;
    
    /// Area width where the walker can walk
    var width : CGFloat;
    
    /// Area height where the walker can walk
    var height : CGFloat;
    
    var probalitityFactor : Float = 0.5;
    
    
    init(width : CGFloat, height : CGFloat)
    {
        self.positionX = width / 2;
        self.positionY = height / 2;
        self.width = width;
        self.height = height;
    }
    
    init(positionX : CGFloat, positionY : CGFloat, width : CGFloat, height : CGFloat)
    {
        self.positionX = positionX;
        self.positionY = positionY;
        self.width = width;
        self.height = height;
    }
    
    func setProbalitiyFactor(factor : Float)
    {
        self.probalitityFactor = factor;
    }
    
    /// Makes the walker object to take a step in a direction
    public func step() -> CGPoint
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
        
        
        self.constrain();
        
        return(CGPointMake(self.positionX, self.positionY));
    }
    
    public func step(target : CGPoint) -> CGPoint
    {
        var choice : Float = RandomNumberGenerator.GetRandomFloat(1);
        
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
        
        
        self.constrain();
        
        return(CGPointMake(self.positionX, self.positionY));
    }
    
    /// Return current position of the walker
    public func GetCurentPosition() -> CGPoint
    {
        return(CGPointMake(self.positionX, self.positionY));
    }
    
    /// Constrain the walker position to the defined area
    func constrain()
    {
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