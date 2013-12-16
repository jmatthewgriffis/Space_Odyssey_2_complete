//
//  Enemy.cpp
//  Space_Odyssey_2
//
//  Created by J. Matthew Griffis on 12/1/13.
//
//

#include "Enemy.h"

Enemy::Enemy() {
    
}

void Enemy::setup() {
    
    // Matt
    generation = 0;
    vel.set( ofRandom(-1, 1), ofRandom(-1, 1));
    attack = true;
    healthMax = 1000;
    health = healthMax;
    bDestroyMe = false;
    
    //Mauricio
//    counter = 0;
//    frameNum = 0;
    
    //We load our 50 images to create our animation
    for( int i = 0; i < 50; i++){
        
        string frameNum = ofToString(i);
        metroid[i].loadImage("metroid/" + frameNum + ".png");
    }
    
    pos = ofVec2f( ofGetWindowWidth() / 2.0 - metroid[ 0 ].getWidth() / 2.0, 0 ); //Matt
    
}

void Enemy::update(vector <SpaceShip> _tmp){
    
    if ( health <= 0 ) {
        bDestroyMe = true;
    }
       
    // Matt
    pos += vel;
        
//        d[0] = pos.distance(_tmp[0].pos);
//        d[1] = pos.distance(_tmp[1].pos);
//        d[2] = pos.distance(_tmp[2].pos);
//        d[3] = pos.distance(_tmp[3].pos);
    
    { // Matt (have to deal with changing vector size, here's a hack)
        float tooFar = ofGetWidth() * 2;
        if ( _tmp.size() > 3 ) d[3] = pos.distance(_tmp[3].pos);
        else d[3] = tooFar;
        if ( _tmp.size() > 2 ) d[2] = pos.distance(_tmp[2].pos);
        else d[2] = tooFar;
        if ( _tmp.size() > 1 ) d[1] = pos.distance(_tmp[1].pos);
        else d[1] = tooFar;
        if ( _tmp.size() > 0 ) d[0] = pos.distance(_tmp[0].pos);
        else d[0] = tooFar;
    } // End Matt
    
    //This will trigger the attack toward one of the enmies
        if( attack){
            
            if( d[0] < d[1] && d[0] < d[2] && d[0] < d[3]){
                
                pos.x = ofLerp(pos.x, _tmp[0].pos.x, 0.02);
                pos.y = ofLerp(pos.y, _tmp[0].pos.y, 0.02);
                
            }
            
            if( d[1] < d[0] && d[1] < d[2] && d[1] < d[3]){
                
                pos.x = ofLerp( pos.x, _tmp[1].pos.x, 0.02);
                pos.y = ofLerp( pos.y, _tmp[1].pos.y, 0.02);
            }
            
            if( d[2] < d[0] && d[2] < d[1] && d[2] < d[3]){
                
                pos.x = ofLerp( pos.x, _tmp[2].pos.x, 0.02);
                pos.y = ofLerp( pos.y, _tmp[2].pos.y, 0.02);
            }
            if( d[3] < d[0] && d[3] < d[1] && d[3] < d[2]){
                pos.x = ofLerp( pos.x, _tmp[3].pos.x, 0.02);
                pos.y = ofLerp( pos.y, _tmp[3].pos.y, 0.02);            
            }
        }
    
    if ( pos.x < 0 || pos.x > ofGetWindowWidth()){
        
        vel.x *= -1;
    }
    
    if( pos.y < 0 || pos.y > ofGetWindowHeight()){
        
        vel.y *= -1;
    }
    
    attackCounter++;
    
    if( attackCounter > 200 && attackCounter < 400){
        attack = true;
    } else {
        attack = false;
    }
    
    if( attackCounter > 500){
        
        attackCounter = 0;
        vel.set( ofRandom(-1, 1), ofRandom(-1, 1));
    }
    
}

void Enemy::draw(int &_frameNum){
    
    // Matt
//    drawWings();
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    ofPushMatrix();{
        
        ofTranslate(pos.x , pos.y);
        
        { // Matt
            // Draw the health bar
            ofSetRectMode( OF_RECTMODE_CORNER );
            float offset = 1;
            float hoffSet = ( metroid[ 0 ].getWidth() * 0.25 ) / 2;
            float voffSet = metroid[ 0 ].getHeight() - 50;
            float offsetBar = 10;
            float barHeight = 10;
            float barLength = metroid[ 0 ].getWidth() * 0.75;
            float currentHealth = ofMap( health, 0, healthMax, 0, barLength - offset * 2 );
            // The border.
            ofSetColor( 255 );
            ofNoFill();
            ofRect( hoffSet, voffSet, barLength, barHeight );
            ofFill();
            // The current health.
            ofSetColor( 0, 255, 0 );
            ofRect( hoffSet + offset, voffSet + offset, currentHealth, barHeight - offset * 2 );
        } // End Matt
        ofSetColor(255); //Matt
        metroid[_frameNum].draw(0,0);
        
    }ofPopMatrix();
}

void Enemy::branch( float length, float _ang1, float _ang2, float _mult, bool _trans ) {
    
    // Matt--this is copied and heavily modified from Charlie's in-class example.
    
    if ( _trans ) {
        ofTranslate( 100, 0 );
    }
    
    ofPushMatrix();
    ofLine( ofVec2f(0,0), ofVec2f(0, -length) );
    ofTranslate( 0, -length );
    
    //        generation++;
    
    float noise = ofNoise(ofGetElapsedTimef() * 0.1 );
    
    if( length > 2 ){
        ofPushMatrix();{
            ofRotate( ( _ang1 + theta + noise * 10-5 ) * _mult );
            branch( length * 0.666, _ang1, _ang2, _mult, _trans );
        }ofPopMatrix();
        
        ofPushMatrix();{
            ofRotate( ( _ang2 + theta - noise * 10-5 ) * _mult );
            branch( length * 0.666, _ang1, _ang2, _mult, _trans );
        }ofPopMatrix();
    }
    
    ofPopMatrix();
    
    //    generation--;
}

void Enemy::drawWings() {
    
    // Matt--this is copied and heavily modified from Charlie's in-class example.
    
    // Draw the wings.
    ofPushMatrix();{
        ofSetColor( 255, 0, 0 );
        ofTranslate( pos );
        ofRotate( -115+ofNoise(ofGetElapsedTimef()));
        branch( 100, -10, 50, -1 );
    }ofPopMatrix();
    ofPushMatrix();{
        ofSetColor( 255, 0, 0 );
        ofTranslate( pos );
        ofRotate( 115+ofNoise(ofGetElapsedTimef()) );
        branch( 100, -10, 50 );
    }ofPopMatrix();
}