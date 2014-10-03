//
//  TesterBot.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 03/10/14.
//  Copyright (c) 2014 Adrian Simionescu. All rights reserved.
//

import Foundation

public class TestBot : CCDrawNode, pRandomBaseBasic, pObjectBaseBasic
{
    var width : CGFloat = 0;
    var height : CGFloat = 0;
    var viewSize : CGSize;
    var randomNumberMode : RandomNumberMode;
    var velocity : Vector!;
    
    override init()
    {
        self.viewSize = CCDirector.sharedDirector().viewSize();
        self.randomNumberMode = RandomNumberMode.Uniform;
        super.init();
        
        self.position = CGPointMake(self.viewSize.width / 2, self.viewSize.height / 2);
        self.velocity = Vector(x: 2.5, y: 5);
        self.render();
    }
    
    func render() {
        let selectorCalculations: Selector = "doCalculations";
        var makeTheWalkerToStep : CCActionCallFunc = CCActionCallFunc.actionWithTarget(self, selector: selectorCalculations ) as CCActionCallFunc;
        
        var delay : CCActionDelay = CCActionDelay.actionWithDuration(0.0001) as CCActionDelay;
        
        var actions = Array<CCAction>();
        actions.append(makeTheWalkerToStep);
        actions.append(delay);
        var walk : CCActionSequence = CCActionSequence.actionWithArray(actions) as CCActionSequence;
        var walkForever : CCActionRepeatForever = CCActionRepeatForever.actionWithAction(walk) as CCActionRepeatForever;
        
        self.runAction(walkForever);
    }
    
    func setRandomNumberMode( randomNumberMode : RandomNumberMode)
    {
        
    }
    
    func setConstrainsRange( width : CGFloat, height: CGFloat)
    {
        
    }
    
    func doCalculations()
    {
        self.position += self.velocity;
        self.drawDot(position, radius: 2, color: CCColor.blueColor());
    }
    
    func constrain()
    {
        if ((self.position.x > width) || (self.position.x < 0)) {
            velocity.x = velocity.x * -1;
        }
        if ((self.position.y > height) || (self.position.y < 0)) {
            velocity.y = velocity.y * -1;
        }
    }
}