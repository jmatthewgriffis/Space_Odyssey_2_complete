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
    pos = ofVec2f( ofGetWindowWidth() / 2, 5);
    vel.set( ofRandom(-1, 1), ofRandom(-1, 1));
    attack = true;
    
}

void Enemy::update(vector <SpaceShip> _tmp){
    
    // Matt
    pos += vel;
    
    //Mauricio
        
        d[0] = pos.distance(_tmp[0].pos);
        d[1] = pos.distance(_tmp[1].pos);
        d[2] = pos.distance(_tmp[2].pos);
        d[3] = pos.distance(_tmp[3].pos);
    
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

void Enemy::draw(){
    
    // Matt
    drawWings();
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
    ofSetLineWidth(3);
    ofPushMatrix();{
        ofSetColor( 255, 0, 0 );
        ofTranslate( pos );
        ofRotate( -115+ofNoise(ofGetElapsedTimef()));
        branch( 250, -10, 50, -1 );
    }ofPopMatrix();
    ofPushMatrix();{
        ofSetColor( 255, 0, 0 );
        ofTranslate( pos );
        ofRotate( 115+ofNoise(ofGetElapsedTimef()) );
        branch( 250, -10, 50 );
    }ofPopMatrix();
}