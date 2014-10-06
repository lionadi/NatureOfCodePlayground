//
//  Mover.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 03/10/14.
//  Copyright (c) 2014 Test. All rights reserved.
//

import Foundation

protocol PMover : PObjectBaseBasic
{
    var MoverObject : Mover { get set }
    
    
}

public class Mover : RandomBaseComplete
{
    var Position : Vector;
    var Velocity : Vector;
    var Acceleration : Vector;
    
    override init()
    {
        self.Position = Vector.Zero();
        self.Velocity = Vector.Zero();
        self.Acceleration = Vector.Zero();
        super.init();
        
    }
    
    init(position : Vector, velocity : Vector)
    {
        self.Position = position;
        self.Velocity = velocity;
        self.Acceleration = Vector.Zero();
        super.init();
        
    }
    
    init(position : Vector, velocity : Vector, acceleration : Vector)
    {
        self.Position = position;
        self.Velocity = velocity;
        self.Acceleration = acceleration;
        super.init();
    }
    
    func Accelerate()
    {
        self.Velocity += self.Acceleration;
        self.Velocity.Limit(10);
        self.Position += self.Velocity;
    }
    
    func Decellerate()
    {
        self.Velocity -= self.Acceleration;
        self.Velocity.Limit(10);
        self.Position += self.Velocity;
    }
    
    
    override func UniformCalculations() {
        super.UniformCalculations();
        self.Accelerate();
    }
    
    override func Constrain() {
        if (self.Position.x > self.Width.ToFloat()) {
            self.Position.x = 0;
        } else if (self.Position.x < 0) {
            self.Position.x = self.Width.ToFloat();
        }
        
        if (self.Position.y > self.Height.ToFloat()) {
            self.Position.y = 0;
        } else if (self.Position.y < 0) {
            self.Position.y = self.Height.ToFloat();
        }
    }
    
}