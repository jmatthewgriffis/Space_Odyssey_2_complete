//
//  Enemy.h
//  Space_Odyssey_2
//
//  Created by J. Matthew Griffis on 12/1/13.
//
//

#pragma once
#include "ofMain.h"
#include "SpaceShip.h"


// Note from Matt: I created the class and implemented all the branching code to draw the Metroid/Balrog. Mauricio is handling the behavior.

//Note from Mauricio: In order to increase performance we have come up with a me thod to make a code GIF using code. We created a GIF loader in openFrameworks since ofImage although it supports GIF format it doesn't load the sequences of images. The code can be seen here //https://github.com/sheva29/oF_exercises/tree/master/imageLoader

class Enemy {
public:
    
    // Matt
    Enemy();
    void setup();
    void update(vector <SpaceShip> _tmp);
    void draw(int &_frameNum);
    void branch( float length, float _ang1, float _ang2, float _mult = 1, bool _trans = false );
    void drawWings();
    ofVec2f pos;
    ofVec2f vel;
    int generation;
    float theta = 30;
    float healthMax;
    bool bDestroyMe;
    
    //Mauricio
    float d[4], health, size, attackCounter;
    bool attack;
    
    ofImage metroid[50];
    
   
    
    
    
};