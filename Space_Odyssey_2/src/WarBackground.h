//
//  War Background.h
//  Space_Odyssey_2
//
//  Created by Mauricio Sanchez Duque on 12/9/13.
//
//

#pragma once
#include "ofMain.h"
#define NUM_OF_VEHICLES 5

//These is going to be our vehicles that are moving in the second background
struct Vehicle{
    
    float maxSpeed, maxForce, slowDownRadius;
    ofVec2f pos, vel, accel, damping, dest;
    
    Vehicle( ofVec2f _pos, ofVec2f _vel, ofVec2f _dest){
        
        pos.set( _pos );
        vel.set( _vel );
        dest.set( _dest );
        damping = ofVec2f( 0.01f ) ;
        maxSpeed = 2.0;
        maxForce = 0.4;
        slowDownRadius = 100.0;
        
    }
    
    void applyForce( ofVec2f force ){
        
        accel += force;
        accel.limit(2.0);
        
    }
    
    void update(){
        
        vel += accel;
        pos += vel;
        
        vel *= 0.97;
        
        accel.set( 0 );
    }
    
    void addRepulsionforce( const ofVec2f &fromPos){
        
        ofVec2f diff = pos - fromPos;
        
        float strength = 1 - ( diff.length() / 300 ) ;
        
        applyForce( diff.normalize() * strength ) ;
        
    }
    
    void seek( ofVec2f _dest ){
        
        dest.set( _dest );
        
        ofVec2f desired = _dest - pos;
        
        if( desired.length() < slowDownRadius){
            
            float newMag = ofMap( desired.length(), 0, slowDownRadius, 0 , maxSpeed);
            
            desired.normalize();
            desired *= newMag;
            
        }else {
            
            desired.normalize();
            desired *= maxSpeed;
        }
        
        ofVec2f steer = desired - vel;
        
        steer.limit( maxForce );
        
        applyForce(steer);
        
    }
    
    void draw(){
        
        ofPushMatrix();{
            
            ofSetRectMode( OF_RECTMODE_CENTER );
            
            ofTranslate(pos);
            float rotAmt = atan2( vel.y, vel.x );
            ofRotate( ofRadToDeg(rotAmt) + 90 );
            ofFill();
            ofRect(0 , 0 , 20, 50 );
            
        }ofPopMatrix();
    }
};

class WarBackground{
    
public:
    
    WarBackground();
    void setup();
    void draw();
    void update();
    void addVehicle();
    
    deque < Vehicle > vList;
    
};
