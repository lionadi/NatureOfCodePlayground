//
//  ObjectBase.swift
//  NatureOfCode
//
//  Created by Adrian Simionescu on 01/10/14.
//  Copyright (c) 2014 Test. All rights reserved.
//

import Foundation

protocol pObjectBaseBasic : pRandomBase
{
    
    /**
    Implement this method to render the Object. Use this to initialize the render logic using the object data.
    */
    func render();
}