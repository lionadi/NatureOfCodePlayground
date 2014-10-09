//
//  TesterBot.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 03/10/14.
//  Copyright (c) 2014 Adrian Simionescu. All rights reserved.
//

import Foundation

public class TestBot : CCDrawNode, PMover
{
    var Width : CGFloat = 0;
    var Height : CGFloat = 0;
    var ViewSize : CGSize;
    var RandomNumberModeValue : RandomNumberMode;
    var MoverObject : Mover;
    
    override init()
    {
        self.ViewSize = CCDirector.sharedDirector().viewSize();
        self.RandomNumberModeValue = RandomNumberMode.Uniform;
        self.MoverObject = Mover(position: Vector.Zero(), velocity: Vector.Zero(), acceleration: Vector(x: -0.001, y: 0.01));
        self.MoverObject.SetConstrainsRange(self.ViewSize.width, height: self.ViewSize.height);
        super.init();
        self.Width = self.ViewSize.width;
        self.Height = self.ViewSize.height;
        self.position = CGPointMake(0, 0);
        self.drawDot(self.position, radius: 20, color: CCColor.blueColor());
        self.Render();
    }
    
    func Render() {
        let selectorCalculations: Selector = "DoCalculations";
        var makeTheWalkerToStep : CCActionCallFunc = CCActionCallFunc.actionWithTarget(self, selector: selectorCalculations ) as CCActionCallFunc;
        
        var delay : CCActionDelay = CCActionDelay.actionWithDuration(0.0001) as CCActionDelay;
        
        var actions = Array<CCAction>();
        actions.append(makeTheWalkerToStep);
        actions.append(delay);
        var walk : CCActionSequence = CCActionSequence.actionWithArray(actions) as CCActionSequence;
        var walkForever : CCActionRepeatForever = CCActionRepeatForever.actionWithAction(walk) as CCActionRepeatForever;
        
        self.runAction(walkForever);
    }
    
    func SetRandomNumberMode( randomNumberMode : RandomNumberMode)
    {
        
    }
    
    func SetConstrainsRange( width : CGFloat, height: CGFloat)
    {
        
    }
    
    func DoCalculations()
    {
        self.MoverObject.DoCalculations();
        self.position = self.MoverObject.Position.ToCGPoint();
        
    }
}