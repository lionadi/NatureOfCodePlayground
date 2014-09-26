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

public class Walker : CCDrawNode
{
    var positionX : CGFloat = 0;
    var positionY : CGFloat = 0;
    var viewSize : CGSize;
    var mainColor : CCColor;
    var colorCount : Int = 0;
    var colorID : ColorOption;
    var colorCountLimit : Int = 25;
    
    
    override init()
    {
        self.colorID = ColorOption.Blue;
        self.viewSize = CCDirector.sharedDirector().viewSize();
        self.mainColor = CCColor.blueColor();
        super.init();
        self.positionX = self.viewSize.width / 2;
        self.positionY = self.viewSize.height / 2;
        
    }
    init(position : CGPoint)
    {
        self.viewSize = CCDirector.sharedDirector().viewSize();
        self.colorID = ColorOption.Blue;
        self.mainColor = CCColor.blueColor();
        super.init();
        self.render(position);
    }
    
    func walk()
    {
        
        
        var finalPositionX : Float = RandomNumberGenerator.GetRandomFloat(2);
        var finalPositionY : Float = RandomNumberGenerator.GetRandomFloat(2);
        
    }
    
    private func render( position: CGPoint)
    {
        self.drawDot(position, radius: 2, color: self.mainColor);
    }
    
    public func render()
    {
        
        let selectorWalkerStepping: Selector = "step";
        var makeTheWalkerToStep : CCActionCallFunc = CCActionCallFunc.actionWithTarget(self, selector: selectorWalkerStepping) as CCActionCallFunc;
        
        var delay : CCActionDelay = CCActionDelay.actionWithDuration(0.0001) as CCActionDelay;
        
        var actions = Array<CCAction>();
        actions.append(makeTheWalkerToStep);
        actions.append(delay);
        var walk : CCActionSequence = CCActionSequence.actionWithArray(actions) as CCActionSequence;
        var walkForever : CCActionRepeatForever = CCActionRepeatForever.actionWithAction(walk) as CCActionRepeatForever;
        
        self.runAction(walkForever);
    }
    
    /// Makes the walker object to take a step in a direction
    public func step()
    {
        var choice = RandomNumberGenerator.GetRandomUInt32(4);
        
        switch(choice)
            {
        case 0:
            self.positionX++;
            self.positionX++;
            
        case 1:
            self.positionX--;
            self.positionX--;
        case 2:
            self.positionY++;
            self.positionY++;
        case 3:
            self.positionY--;
            self.positionY--;
        default:
                self.positionX++;
        }
        
        self.colorCount++;
        if(self.colorCount > colorCountLimit)
        {
            var choice = RandomNumberGenerator.GetRandomUInt32(4);
            
            switch(choice)
                {
            case 0:
                self.mainColor = CCColor.blueColor();
            case 1:
                self.mainColor = CCColor.redColor();
            case 2:
                self.mainColor = CCColor.yellowColor();
            case 3:
                self.mainColor = CCColor.greenColor();
            default:
                self.mainColor = CCColor.blueColor();
            }
            self.colorCount = 0;
        }
        self.constrain();
        self.render(CGPointMake(self.positionX, self.positionY));
    }
    
    func constrain()
    {
        if(self.positionX < 0)
        {
            self.positionX = 0;
        }
        if(self.positionX > self.viewSize.width)
        {
            self.positionX = self.viewSize.width;
        }
        if(self.positionY < 0)
        {
            self.positionY = 0;
        }
        
        if(self.positionY > self.viewSize.height)
        {
            self.positionY = self.viewSize.height;
        }
        
    }
}