//
//  Michael.h
//  Space_Odyssey_2
//
//  Created by Mauricio Sanchez Duque on 12/16/13.
//
//

#pragma once
#include "ofMain.h"

class Michael{
    
    
public:
    
    Michael();
    
    void update();
    void draw();
    void setup( ofVec2f _pos);
    void setParams(ofVec2f _pos, float vx, float vy);
    void addForce(ofVec2f force);
    void addDampingForce();
    void resetForces();
    
    ofVec2f pos, vel, frc, damping;
    
    ofImage image;
    float sinOfTimeMapped;
    float rotation;
    
};
