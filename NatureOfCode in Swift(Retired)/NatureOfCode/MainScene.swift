//
//  MainScene.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 23/09/14.
//  Copyright (c) 2014 Adrian Simionescu. All rights reserved.
//

import Foundation
import Darwin

class MainScene : CCScene
{
    var walker : DotWalker!;
    //var texture : RandomTexture!;
    var testBot : TestBot!;
    override init()
    {
        super.init();
        
        self.walker = DotWalker();
        self.walker.SetRandomNumberMode(RandomNumberMode.Perlin);
        self.addChild(self.walker);
        self.color = CCColor.grayColor();
        userInteractionEnabled = true
        
        var viewSize : CGSize = CCDirector.sharedDirector().viewSize();
        //self.texture = RandomTexture(width: Int32(viewSize.width), height: Int32(viewSize.height));
        //self.texture.textureSprite.removeFromParentAndCleanup(true);
        //self.texture.textureSprite.position = CGPointMake(viewSize.width / 2, viewSize.height / 2);
        //self.addChild(self.texture.textureSprite, z: -1);
        
        self.testBot = TestBot();
        self.testBot.position = CGPointMake(viewSize.width / 2, viewSize.height / 2);
        self.addChild(testBot);
    }
    
    override func touchEnded(touch: UITouch!, withEvent event: UIEvent!) {
        var touchLocation : CGPoint = touch.locationInNode(self);
        //self.walker.setWalkerTarget(CGPointZero);
    }
    
    override func touchMoved(touch: UITouch!, withEvent event: UIEvent!) {
        var touchLocation : CGPoint = touch.locationInNode(self);
        //self.walker.setWalkerTarget(touchLocation);
    }
    
    override func touchBegan(touch: UITouch!, withEvent event: UIEvent!)
    {
        var touchLocation : CGPoint = touch.locationInNode(self);
        //self.walker.setWalkerTarget(touchLocation);
    }
    
    override func touchCancelled(touch: UITouch!, withEvent event: UIEvent!) {
        var touchLocation : CGPoint = touch.locationInNode(self);
        //self.walker.setWalkerTarget(CGPointZero);
    }
    
    /*override func draw(renderer: CCRenderer!, transform: COpaquePointer) {
        //super.draw(renderer, transform: transform);
        var s = CCDirector.sharedDirector().viewSize();
        
        var drawLine : CCDrawNode = CCDrawNode();
        drawLine.drawDot(CGPointMake(s.width/2, s.height/2), radius: 5, color: CCColor.redColor());
        /*
        // draw a simple line
        // The default state is:
        // Line Width: 1
        // color: 255,255,255,255 (white, non-transparent)
        // Anti-Aliased
        glEnable(GL_LINE_SMOOTH);
        ccDrawLine( CGPointMake(0, 0), CGPointMake(s.width, s.height) );
        
        // line: color, width, aliased
        // glLineWidth > 1 and GL_LINE_SMOOTH are not compatible
        // GL_SMOOTH_LINE_WIDTH_RANGE = (1,1) on iPhone
        glDisable(GL_LINE_SMOOTH);
        glLineWidth( 5.0 );
        glColor4ub(255,0,0,255);
        ccDrawLine( CGPointMake(0, s.height), CGPointMake(s.width, 0) );
        
        // TIP:
        // If you are going to use always the same color or width, you don't
        // need to call it before every draw
        //
        // Remember: OpenGL is a state-machine.
        
        // draw big point in the center
        glPointSize(64);
        glColor4ub(0,0,255,128);
        ccDrawPoint( CGPointMake(s.width / 2, s.height / 2) );
        
        // draw 4 small points
        var  points : [CGPoint] = [ CGPointMake(60,60), CGPointMake(70,70), CGPointMake(60,70), CGPointMake(70,60) ];
        glPointSize(4);
        glColor4ub(0,255,255,255);
        ccDrawPoints( points, 4);
        
        // draw a green circle with 10 segments
        glLineWidth(16);
        glColor4ub(0, 255, 0, 255);
        ccDrawCircle( CGPointMake(s.width/2,  s.height/2), 100, 0, 10, NO);
        
        // draw a green circle with 50 segments with line to center
        glLineWidth(2);
        glColor4ub(0, 255, 255, 255);
        ccDrawCircle( CGPointMake(s.width/2, s.height/2), 50, CC_DEGREES_TO_RADIANS(90), 50, YES);
        
        // open yellow poly
        glColor4ub(255, 255, 0, 255);
        glLineWidth(10);
        var vertices : [CGPoint] = [ CGPointMake(0,0), CGPointMake(50,50), CGPointMake(100,50), CGPointMake(100,100), CGPointMake(50,100) ];
        ccDrawPoly( vertices, 5, NO);
        
        // closed purble poly
        glColor4ub(255, 0, 255, 255);
        glLineWidth(2);
        var vertices2 : [CGPoint] = [ CGPointMake(30,130), CGPointMake(30,230), CGPointMake(50,200) ];
        ccDrawPoly( vertices2, 3, YES);
        
        // draw quad bezier path
        ccDrawQuadBezier(CGPointMake(0,s.height), CGPointMake(s.width/2,s.height/2), CGPointMake(s.width,s.height), 50);
        
        // draw cubic bezier path
        ccDrawCubicBezier(CGPointMake(s.width/2, s.height/2), CGPointMake(s.width/2+30,s.height/2+50), CGPointMake(s.width/2+60,s.height/2-50),CGPointMake(s.width, s.height/2),100);
        
        
        // restore original values
        glLineWidth(1);
        glColor4ub(255,255,255,255);
        glPointSize(1);*/
    }*/
    
    deinit
    {
        // clean up code goes here
    }
}