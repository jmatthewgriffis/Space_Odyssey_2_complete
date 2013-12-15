//
//  Bullet.cpp
//  Space_Odyssey_2
//
//  Created by J. Matthew Griffis on 12/3/13.
//
//

#include "Bullet.h"

Bullet::Bullet( ofVec2f _pos, float _ang ) {
    
    bDestroyMe = false;
    
    size = 5;
    damage = 10;
    
    float fVel = 20;
    vel.x = sin( _ang ) * fVel;
    vel.y = cos( _ang ) * fVel;
    
    pos = _pos + 30 * vel.normalized(); // The extra increment creates the bullet off the ship so it doesn't cause self-damage.
}

void Bullet::update() {
    
    pos += vel;
    
    // Mark the bullet for destruction when it goes offscreen.
    float offset = 50; // How far offscreen can the bullet get?
    if ( pos.x > ofGetWindowWidth() + offset
        || pos.x < -offset
        || pos.y > ofGetWindowHeight() + offset
        || pos.y < -offset ) {
        bDestroyMe = true;
    }
}

void Bullet::draw() {
    
    ofSetColor( 255 );
    ofCircle( pos, size );
}