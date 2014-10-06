//
//  Vector.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 03/10/14.
//  Copyright (c) 2014 Adrian Simionescu. All rights reserved.
//

import Foundation

public struct Vector
{
    var x : Float;
    var y : Float;
    
    init()
    {
        self.x = 0;
        self.y = 0;
    }
    
    init(x : Float, y : Float)
    {
        self.x = x;
        self.y = y;
    }
    
    static func ToCGPoint(vector : Vector) -> CGPoint
    {
        return(CGPoint(x: CGFloat(vector.x), y: CGFloat(vector.y)));
    }
    
    func ToCGPoint() -> CGPoint
    {
        return(CGPoint(x: CGFloat(x), y: CGFloat(y)));
    }
    
    static func Magnitude(vector : Vector) -> Float
    {
        return(Float(sqrt(vector.x * vector.x + vector.y * vector.y)));
    }
    
    func Magnitude() -> Float
    {
        return(Float(sqrt(x * x + y * y)));
    }
    
    mutating func Normalize() -> Vector
    {
        var magnitude : Float = Magnitude();
        if(magnitude != 0)
        {
            self.x = self.x / magnitude;
            self.y = self.y / magnitude;
            return(self.ReturnSelf());
        }
        
        return(Vector.Zero());
    }
    
    mutating func ReturnSelf() -> Vector
    {
        return(Vector(x: self.x, y: self.y));
    }
    
    static func Normalize(vector : Vector) -> Vector
    {
        var magnitude : Float = vector.Magnitude();
        if(magnitude != 0)
        {
            return(Vector(x: vector.x / magnitude, y: vector.y / magnitude));
        }
        
        return(Vector.Zero());
    }
    
    static func Zero() ->Vector
    {
        return(Vector(x: 0, y: 0));
    }
    
    mutating func Zero() ->Vector
    {
        self.x = 0;
        self.y = 0;
        
        return(Vector.Zero());
    }
    
    mutating func Limit( limit : Float) ->Vector
    {
        if ( self.x > limit ) {
            self.x = limit;
        }
        
        if ( self.y > limit ) {
            self.y = limit;
        }
        
        return(Vector.Zero());
    }
}
//-------------------------------------------------------
func + (left: Vector, right: Vector) -> Vector
{
    return Vector(x: left.x + right.x, y: left.y + right.y)
}

func + (left: Vector, right: CGPoint) -> Vector
{
    return Vector(x: left.x + Float(right.x), y: left.y + Float(right.y))
}

func + (left: CGPoint, right: Vector) -> CGPoint
{
    return CGPoint(x: left.x + CGFloat(right.x), y: left.y + CGFloat(right.y))
}

func + (left: Vector, right: Float) -> Vector
{
    return Vector(x: left.x + right, y: left.y + right)
}

func + (left: Vector, right: Int) -> Vector
{
    return Vector(x: left.x + Float(right), y: left.y + Float(right))
}

func + (left: Vector, right: Double) -> Vector
{
    return Vector(x: left.x + Float(right), y: left.y + Float(right))
}
//-------------------------------------------------------

func * (left: Vector, right: Float) -> Vector
{
    return Vector(x: left.x * right, y: left.y * right)
}

func * (left: Vector, right: Int) -> Vector
{
    return Vector(x: left.x * Float(right), y: left.y * Float(right))
}

func * (left: Vector, right: Double) -> Vector
{
    return Vector(x: left.x * Float(right), y: left.y * Float(right))
}

func / (left: Vector, right: Float) -> Vector
{
    return Vector(x: left.x / right, y: left.y / right)
}

func / (left: Vector, right: Int) -> Vector
{
    return Vector(x: left.x / Float(right), y: left.y / Float(right))
}

func / (left: Vector, right: Double) -> Vector
{
    return Vector(x: left.x / Float(right), y: left.y / Float(right))
}


//-------------------------------------------------------
func - (left: Vector, right: Vector) -> Vector
{
    return Vector(x: left.x - right.x, y: left.y - right.y)
}

func - (left: Vector, right: CGPoint) -> Vector
{
    return Vector(x: left.x - Float(right.x), y: left.y - Float(right.y))
}

func - (left: CGPoint, right: Vector) -> CGPoint
{
    return CGPoint(x: left.x - CGFloat(right.x), y: left.y - CGFloat(right.y))
}

func - (left: Vector, right: Float) -> Vector
{
    return Vector(x: left.x - right, y: left.y - right)
}

func - (left: Vector, right: Int) -> Vector
{
    return Vector(x: left.x - Float(right), y: left.y - Float(right))
}

func - (left: Vector, right: Double) -> Vector
{
    return Vector(x: left.x - Float(right), y: left.y - Float(right))
}
//-------------------------------------------------------

//-------------------------------------------------------
prefix func - (vector: Vector) -> Vector {
    return Vector(x: -vector.x, y: -vector.y)
}
//-------------------------------------------------------

//-------------------------------------------------------

func += (inout left: Vector, right: Vector) {
    left = left + right
}

func += (inout left: Vector, right: CGPoint) {
    left = left + right
}

func += (inout left: CGPoint, right: Vector) {
    left = left + right
}

func += (inout left: Vector, right: Int) {
    left = left + right
}

func += (inout left: Vector, right: Float) {
    left = left + right
}

func += (inout left: Vector, right: Double) {
    left = left + right
}
//-------------------------------------------------------

func *= (inout left: Vector, right: Int) {
    left = left * right
}

func *= (inout left: Vector, right: Float) {
    left = left * right
}

func *= (inout left: Vector, right: Double) {
    left = left * right
}

func /= (inout left: Vector, right: Int) {
    left = left / right
}

func /= (inout left: Vector, right: Float) {
    left = left / right
}

func /= (inout left: Vector, right: Double) {
    left = left / right
}
//-------------------------------------------------------
func -= (inout left: Vector, right: Vector) {
    left = left - right
}

func -= (inout left: Vector, right: CGPoint) {
    left = left - right
}

func -= (inout left: CGPoint, right: Vector) {
    left = left - right
}

func -= (inout left: Vector, right: Int) {
    left = left - right
}

func -= (inout left: Vector, right: Float) {
    left = left - right
}

func -= (inout left: Vector, right: Double) {
    left = left - right
}
//-------------------------------------------------------

//-------------------------------------------------------
prefix func ++ (inout vector: Vector) -> Vector {
    vector += Vector(x: 1.0, y: 1.0)
    return vector
}

prefix func -- (inout vector: Vector) -> Vector {
    vector -= Vector(x: 1.0, y: 1.0)
    return vector
}

postfix func ++ (inout vector: Vector) -> Vector {
    vector += Vector(x: 1.0, y: 1.0)
    return vector
}

postfix func -- (inout vector: Vector) -> Vector {
    vector -= Vector(x: 1.0, y: 1.0)
    return vector
}

func == (left: Vector, right: Vector) -> Bool {
    return (left.x == right.x) && (left.y == right.y)
}

func != (left: Vector, right: Vector) -> Bool {
    return !(left == right)
}
//-------------------------------------------------------

