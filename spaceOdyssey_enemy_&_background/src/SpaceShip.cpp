//
//  SpaceShip.cpp
//  Space_Odyssey_2
//
//  Created by Mauricio Sanchez Duque on 11/22/13.
//
//

#include "SpaceShip.h"


void SpaceShip::setup(ofVec2f _pos, ofColor _colorPlayer/*, ofImage _spaceImage*/){
    
    { // Mauricio
        pos = _pos;
        //vel = _vel;
        colorPlayer = _colorPlayer;
        /*spaceImage = _spaceImage;*/
        //spaceShipSize = 50;
        rotAngle = 0;
        //size = 150;
        inc = 20;
        rotAngleInc = 1 * 0.15;
    }
    
    { // Matt
        vel.set( 0 );
        acc.set( 0 );
        rotateCCWise = rotateCWise = notAngled = addToSpeed = fire = bReadyToFire = bFiring = false;
        allowAction = true;
        fireTimer = firePacer = 0;
        timerMax = 30;
        pacerMax = 15;
        boost = 0.3;
        size = 150/2;
        engineSize = size / 3;
    }
}


void SpaceShip::update(){
    
    { // Mauricio
        //We check the propeller drawn at a point on the ellipse's circumference based on the angle, so to rotate we change the angle
        if( rotateCCWise == true){
            
            rotAngle += rotAngleInc;
        }
        
        if ( rotateCWise == true){
            
            rotAngle -= rotAngleInc;
        }
        
        //If the angle has reached its limit we reset it
        if( rotAngle > 2 * PI){
            
            rotAngle = 0;
        }
        
        if( rotAngle < 0 ){
            
            rotAngle = 2 * PI;
        }
        
        /* // Note from Matt: this is the code from Processing, which did not provide full 360-degree movement. Now with vector math it's much easier, so I commented all this out and figured out the angles in the applyForce function.
         
         //This determines the 8 different angles at which
         if ((rotAngle < (PI/inc) || rotAngle > (PI*2)-(PI/inc)) ||
         (rotAngle < PI+(PI/inc) && rotAngle > PI-(PI/inc)) ||
         (rotAngle < (PI/2+PI/inc) && rotAngle > (PI/2-PI/inc)) ||
         (rotAngle < (3*PI/2+PI/inc) && rotAngle > (3*PI/2-PI/inc))){
         notAngled = false;
         
         }else{
         notAngled = false;
         }
         
         //If accelerating we change the velocity
         if( addToSpeed == true){
         
         if ( vel <= 4 * velModifier){
         
         velModifier += ( 0.25 * 1/60);
         }
         } else {
         
         velModifier = 0.75;
         }
         
         //Here we check the motion
         if( fire == true){
         
         //Move straight up
         if( rotAngle < (PI/inc) || rotAngle > ( PI * 2) - (PI / inc) ){
         
         pos.y -= vel;
         
         }
         
         //Move straight down
         if( rotAngle < PI + (PI/inc) && rotAngle > PI -( PI / inc) ) {
         
         pos.y += vel;
         
         }
         
         //Move straight left
         if( rotAngle < ( PI/2 + PI/inc) && rotAngle > (PI/2 -PI/inc)){
         
         pos.x -= vel;
         }
         
         //Move straight right
         if( rotAngle < ( 3 * PI/ 2 + PI/inc) && rotAngle > (3 * PI /2 - PI/ inc)){
         
         pos.x += vel;
         }
         
         
         if ( notAngled == false){
         
         if( rotAngle < PI / 2){
         
         pos.y -= vel;
         pos.x -= vel;
         
         }else if( rotAngle >= PI /2 && rotAngle < PI){
         
         pos.y += vel;
         pos.x -= vel;
         
         }else if( rotAngle >= PI && rotAngle < 3 * PI / 2){
         
         pos.y += vel;
         pos.x += vel;
         
         }else if( rotAngle >= 3 * PI / 2 && rotAngle < 2 * PI){
         
         pos.y -= vel;
         pos.x += vel;
         
         }
         }else {
         
         addToSpeed = false;
         }
         
         } */
    } // End Mauricio
    
    { // Matt
        
        // Player has to tap the fire button twice within a specified timeframe to fire a bullet.
        if ( fireTimer > 0 ) {
            bReadyToFire = true;
            fireTimer--;
        } else {
            bReadyToFire = false;
        }
        // Control fire rate.
        if ( firePacer > 0 ) {
            firePacer--;
        }
        
        // Reset the bool.
        //shootBullet = false;
        
        if ( fire ) {
            // Accelerate.
            applyForce( boost, rotAngle );
            
            if ( allowAction ) {
                // Prep for firing.
                if ( fireTimer == 0 ) {
                    fireTimer = timerMax;
                    //bFiring = true;
                    //allowAction = false;
                } else {
                    bFiring = true;
                    fireTimer = 0;
                    //cout<<"yes!"<<endl;
                }
                allowAction = false;
            }
        } else {
            bFiring = false;
            firePacer = 0;
            allowAction = true;
        }
        
        vel += acc;
        pos += vel;
        
        float damping = 0.97;
        vel *= damping;
        acc.set( 0 );
    }
}


void SpaceShip::draw(){
    
    //if ( fireTimer > 0 ) cout<<fireTimer<<endl;
    
    { // Mauricio
        ofSetColor( colorPlayer);
        ofPushMatrix();{
            
            //        ofTranslate( pos.x, pos.y);
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofEllipse( pos.x, pos.y, size, size);
            ofPushMatrix();{
                
                ofTranslate( pos.x, pos.y);
                
                ofSetColor( 255);
                ofRect( sin(rotAngle) * engineSize, cos( rotAngle) * engineSize, engineSize, engineSize);
                
                
            }ofPopMatrix();
            
            
        }ofPopMatrix();
    }
}

void SpaceShip::applyForce( float _force, float _ang ) {
    
    { // Matt
        // Apply the force in the angle opposite the direction of the engine.
        float ang = _ang - PI;
        ofVec2f force;
        force.x = sin( ang ) * _force;
        force.y = cos( ang ) * _force;
        acc += force;
    }
}