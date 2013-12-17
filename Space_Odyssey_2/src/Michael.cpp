//
//  Michael.cpp
//  Space_Odyssey_2
//
//  Created by Mauricio Sanchez Duque on 12/16/13.
//
//

#include "Michael.h"

Michael::Michael(){
    
    setParams(ofVec2f(0,0),0,0);
    damping.set(0,0);
    image.loadImage("image3.png"); //does this count as a non-circle? If not, image.png is definitely not a circle
}

void Michael::setup(ofVec2f _pos){
    
    pos.set(_pos);
}

void Michael::setParams(ofVec2f _pos, float vx, float vy){
    pos.set(_pos);
    vel.set(vx,vy);
    rotation = ofRandom(0,30);
}

void Michael::addForce(ofVec2f force){
    frc += force;
}

void Michael::resetForces(){
    frc.set(0,0);
}

void Michael::addDampingForce(){
    frc = frc - vel * damping;
}

void Michael::update(){
    vel+=frc;
    pos+=vel;
    
    //another thing I was playing with was uncommenting the below and then turning the auto background on.
    
    //    if(rotation<360){
    //    rotation+=rotation/100;
    //    }
    //    else{
    //        rotation=0;
    //        rotation+=rotation/1000;
    //    }
    
}

void Michael::draw(){
    float sinOfTime = sin( ofGetElapsedTimef() * 2 );
    sinOfTimeMapped = ofMap( sinOfTime, -1, 1, 1, 2);
    ofPushMatrix();
    ofSetRectMode(OF_RECTMODE_CORNER);
        ofRotate(rotation);
        image.draw(pos.x + 400,pos.y + 250,40*sinOfTimeMapped,45*sinOfTimeMapped);
    ofPopMatrix();
    
}