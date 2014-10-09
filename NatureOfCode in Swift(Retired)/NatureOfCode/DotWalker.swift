//
//  DotWalker.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 24/09/14.
//  Copyright (c) 2014 Adrian Simionescu. All rights reserved.
//

import Foundation

// Walker base class that gives functionality to some object. Use it to move it randomly somewhere
public class DotWalker : CCDrawNode, PWalker
{
    var ViewSize : CGSize;
    var MainColor : CCColor;
    var ColorCount : Int = 0;
    var ColorCountLimit : Int = 25;
    var WalkerObject : Walker;
    var TargetForWalker : CGPoint;
    var RandomNumberModeValue : RandomNumberMode;
    
    
    override init()
    {
        self.ViewSize = CCDirector.sharedDirector().viewSize();
        self.MainColor = CCColor.blueColor();
        self.WalkerObject = Walker(width: self.ViewSize.width, height: self.ViewSize.height);
        self.TargetForWalker = CGPointZero;
        self.RandomNumberModeValue = RandomNumberMode.Uniform;
        super.init();
        self.Render();
        
    }
    
    init(position : CGPoint)
    {
        self.ViewSize = CCDirector.sharedDirector().viewSize();
        self.MainColor = CCColor.blueColor();
        self.WalkerObject = Walker(positionX: position.x, positionY: position.y, width: self.ViewSize.width, height: self.ViewSize.height);
        self.TargetForWalker = CGPointZero;
        self.RandomNumberModeValue = RandomNumberMode.Uniform;
        super.init();
        self.Render();
    }
    
    func SetRandomNumberMode(randomNumberMode : RandomNumberMode)
    {
        self.RandomNumberModeValue = randomNumberMode;
        self.WalkerObject.SetRandomNumberMode(randomNumberMode);
    }
    
    public func SetWalkerTarget(target: CGPoint) {
        self.TargetForWalker = target;
    }
    
    
    internal func RenderWalkerByPosition( position: CGPoint)
    {
        self.WalkerObject.SetRandomNumberMode(self.RandomNumberModeValue);
        self.drawDot(position, radius: 2, color: self.MainColor);
    }
    
    internal func Render()
    {
        
        let selectorWalkerStepping: Selector = "StepWalker";
        var makeTheWalkerToStep : CCActionCallFunc = CCActionCallFunc.actionWithTarget(self, selector: selectorWalkerStepping ) as CCActionCallFunc;
        
        var delay : CCActionDelay = CCActionDelay.actionWithDuration(0.0001) as CCActionDelay;
        
        var actions = Array<CCAction>();
        actions.append(makeTheWalkerToStep);
        actions.append(delay);
        var walk : CCActionSequence = CCActionSequence.actionWithArray(actions) as CCActionSequence;
        var walkForever : CCActionRepeatForever = CCActionRepeatForever.actionWithAction(walk) as CCActionRepeatForever;
        
        self.runAction(walkForever);
    }
    
    /// Makes the walker object to take a step in a direction
    internal func StepWalker()
    {
        if(self.TargetForWalker != CGPointZero)
        {
            self.StepWalkerByTarget(self.TargetForWalker);
        } else
        {
            self.ColorCount++;
            if(self.ColorCount > self.ColorCountLimit)
            {
                var choice = RandomNumberGenerator.GetRandomUInt32(4);
            
                switch(choice)
                {
                    case 0:
                        self.MainColor = CCColor.blueColor();
                    case 1:
                        self.MainColor = CCColor.redColor();
                    case 2:
                        self.MainColor = CCColor.yellowColor();
                    case 3:
                        self.MainColor = CCColor.greenColor();
                    default:
                        self.MainColor = CCColor.blueColor();
                }
                self.ColorCount = 0;
            }
            
            self.WalkerObject.DoCalculations();
        
            self.RenderWalkerByPosition(self.WalkerObject.GetCurentPosition());
        }
    }
    
    internal func StepWalkerByTarget(target : CGPoint)
    {
        
        
        self.ColorCount++;
        if(self.ColorCount > self.ColorCountLimit)
        {
            var choice = RandomNumberGenerator.GetRandomUInt32(4);
            
            switch(choice)
                {
            case 0:
                self.MainColor = CCColor.blueColor();
            case 1:
                self.MainColor = CCColor.redColor();
            case 2:
                self.MainColor = CCColor.yellowColor();
            case 3:
                self.MainColor = CCColor.greenColor();
            default:
                self.MainColor = CCColor.blueColor();
            }
            self.ColorCount = 0;
        }
        self.WalkerObject.SetTarget(target);
        self.WalkerObject.DoCalculations();
        
        self.RenderWalkerByPosition(self.WalkerObject.GetCurentPosition());
    }
    
}