//
//  SpaceShip.h
//  Space_Odyssey_2
//
//  Created by Mauricio Sanchez Duque on 11/22/13.
//
//

//Mauricio: I'm going to start migrating the base code from processing make sure that it works in our spaceships and include some new physics.

// Note from Matt: I wrote the original code for the ship in the Processing game. Mauricio ported it to this oF project, and now I'm improving it.

#pragma once
#include "ofMain.h"
//#include "Bullet.h"

class SpaceShip {
    
    public:
    
    // Mauricio
    
//    SpaceShip(ofVec2f _pos, ofVec2f _vel, ofColor _colorPlayer/*, ofImage _spaceImage*/);
    void setup(ofVec2f _pos, ofColor _colorPlayer/*, ofImage _spaceImage*/);
    void draw();
    void update();
    
    
    //These are unique to the players
    ofVec2f pos;
    //float vel;
    ofColor colorPlayer;
    ofImage spaceImage;
    
    //Universal Variables
    float spaceShipSize;
    float rotAngle, rotAngleInc;
    float size;
    float velModifier;
    float speed;
    
    bool rotateCCWise, rotateCWise, notAngled, addToSpeed, fire, bReadyToFire, bFiring, allowAction;
    
    int inc;
    
    //---------------------------
    
    // Matt
    
    void applyForce( float _force, float _ang );
    float boost, engineSize;
    ofVec2f vel, acc;
    int fireTimer, firePacer, timerMax, pacerMax;
};
