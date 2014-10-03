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
    
    static func ToCGPoint(vecotr : Vector) -> CGPoint
    {
        return(CGPoint(x: CGFloat(vecotr.x), y: CGFloat(vecotr.y)));
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

