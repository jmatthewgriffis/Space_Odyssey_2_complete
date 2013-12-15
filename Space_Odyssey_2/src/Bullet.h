//
//  Bullet.h
//  Space_Odyssey_2
//
//  Created by J. Matthew Griffis on 12/3/13.
//
//

#pragma once
#include "ofMain.h"

// Note from Matt: this class is mine.

class Bullet {
public:
    Bullet( ofVec2f _pos, float _ang );
    void update();
    void draw();
    
    ofVec2f pos, vel;
    
    bool bDestroyMe;
    
    float size, damage;
};