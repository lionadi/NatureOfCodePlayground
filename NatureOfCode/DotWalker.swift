//
//  DotWalker.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 24/09/14.
//  Copyright (c) 2014. All rights reserved.
//

import Foundation

// Walker base class that gives functionality to some object. Use it to move it randomly somewhere
public class DotWalker : CCDrawNode
{
    var viewSize : CGSize;
    var mainColor : CCColor;
    var colorCount : Int = 0;
    var colorID : ColorOption;
    var colorCountLimit : Int = 25;
    var walker : Walker;
    
    
    override init()
    {
        self.colorID = ColorOption.Blue;
        self.viewSize = CCDirector.sharedDirector().viewSize();
        self.mainColor = CCColor.blueColor();
        self.walker = Walker(width: self.viewSize.width, height: self.viewSize.height);
        super.init();
        self.render();
        
    }
    
    init(position : CGPoint)
    {
        self.viewSize = CCDirector.sharedDirector().viewSize();
        self.colorID = ColorOption.Blue;
        self.mainColor = CCColor.blueColor();
        self.walker = Walker(positionX: position.x, positionY: position.y, width: self.viewSize.width, height: self.viewSize.height);
        super.init();
        self.render(position);
    }
    
    
    private func render( position: CGPoint)
    {
        self.drawDot(position, radius: 2, color: self.mainColor);
    }
    
    private func render()
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
        
        self.render(self.walker.step());
    }
    
}