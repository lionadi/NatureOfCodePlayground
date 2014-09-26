//
//  CCMacros.swift
//
//  Created by Adrian Simionescu on 26/06/14.
//

/* Common place for workaround for all the Cocos2d C MACROs */

import Foundation

extension CCPositionType {

    /**
    * #define CCPositionTypeNormalized CCPositionTypeMake(CCPositionUnitNormalized, CCPositionUnitNormalized, CCPositionReferenceCornerBottomLeft)
    */
    static var Normalized:CCPositionType { get {
        return CCPositionTypeMake(CCPositionUnit.Normalized, CCPositionUnit.Normalized, CCPositionReferenceCorner.BottomLeft)
    }}

}

public struct MathGlobals
{
    static var RADIANS_TO_DEGREES : Float = 57.29577951;
}


extension CGPoint
{
    static func Sub(v1 : CGPoint, v2 : CGPoint) -> CGPoint
    {
        return(CGPointMake(v1.x - v2.x, v1.y - v2.y));
    }
    
    static func Dot(let v1 : CGPoint, let v2 : CGPoint) ->  CGFloat
    {
        return v1.x * v2.x + v1.y * v2.y;
    }
    
    static func LengthSQ(let v: CGPoint) ->  CGFloat
    {
        return CGPoint.Dot(v, v2: v);
    }
    
    static func Normalize(let v: CGPoint) -> CGPoint
    {
        return CGPoint.Mult(v, s: 1.0 / CGPoint.Length(v));
    }
    
    static func Mult(let v: CGPoint , let s:  CGFloat) -> CGPoint
    {
        return CGPointMake(v.x * s, v.y * s);
    }
    
    static func Length(let v: CGPoint) ->  CGFloat
    {
        return CGFloat(sqrtf(Float(CGPoint.LengthSQ(v))));
    }
    
    static func AngleSigned(a: CGPoint, b: CGPoint) -> Float
    {
        var a2 : CGPoint = CGPoint.Normalize(a);
        var b2 : CGPoint = CGPoint.Normalize(b);
        var angle : Float = atan2f(Float(a2.x * b2.y - a2.y * b2.x), Float(CGPoint.Dot(a2, v2: b2)));
        if( fabs(angle) < FLT_EPSILON ) { return 0; }
        return angle;
    }
    
    static func RotateByAngle(v : CGPoint, pivot: CGPoint, angle : Float) -> CGPoint
    {
        var r : CGPoint = CGPoint.Sub(v, v2: pivot);
        var cosa : Float = cosf(angle), sina = sinf(angle);
        var t : Float = Float(r.x);
        r.x = CGFloat(t*cosa - Float(r.y)*sina + Float(pivot.x));
        r.y = CGFloat(t*sina + Float(r.y)*cosa + Float(pivot.y));
        return r;
    }
    
    static func Distance(v1 : CGPoint, v2 : CGPoint) -> CGFloat
    {
        return CGPoint.Length(CGPoint.Sub(v1, v2: v2));
    }
}