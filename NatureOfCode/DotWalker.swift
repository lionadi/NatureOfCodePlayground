//
//  DotWalker.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 24/09/14.
//  Copyright (c) 2014. All rights reserved.
//

import Foundation

// Walker base class that gives functionality to some object. Use it to move it randomly somewhere
public class DotWalker : CCDrawNode, WalkerProtocol
{
    var viewSize : CGSize;
    var mainColor : CCColor;
    var colorCount : Int = 0;
    var colorID : ColorOption;
    var colorCountLimit : Int = 25;
    var walker : Walker;
    var targetForWalker : CGPoint;
    
    
    override init()
    {
        self.colorID = ColorOption.Blue;
        self.viewSize = CCDirector.sharedDirector().viewSize();
        self.mainColor = CCColor.blueColor();
        self.walker = Walker(width: self.viewSize.width, height: self.viewSize.height);
        self.targetForWalker = CGPointZero;
        super.init();
        self.renderWalker();
        
    }
    
    init(position : CGPoint)
    {
        self.viewSize = CCDirector.sharedDirector().viewSize();
        self.colorID = ColorOption.Blue;
        self.mainColor = CCColor.blueColor();
        self.walker = Walker(positionX: position.x, positionY: position.y, width: self.viewSize.width, height: self.viewSize.height);
        self.targetForWalker = CGPointZero;
        super.init();
        self.renderWalker();
    }
    
    public func setWalkerTarget(target: CGPoint) {
        self.targetForWalker = target;
    }
    
    
    internal func renderWalkerByPosition( position: CGPoint)
    {
        self.drawDot(position, radius: 2, color: self.mainColor);
    }
    
    internal func renderWalker()
    {
        
        let selectorWalkerStepping: Selector = "stepWalker";
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
    internal func stepWalker()
    {
        if(self.targetForWalker != CGPointZero)
        {
            self.stepWalkerByTarget(self.targetForWalker);
        } else
        {
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
        
            self.renderWalkerByPosition(self.walker.step());
        }
    }
    
    internal func stepWalkerByTarget(target : CGPoint)
    {
        
        
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
        
        self.renderWalkerByPosition(self.walker.step(target));
    }
    
}