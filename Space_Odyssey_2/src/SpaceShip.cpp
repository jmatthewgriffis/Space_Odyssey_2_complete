//
//  SpaceShip.cpp
//  Space_Odyssey_2
//
//  Created by Mauricio Sanchez Duque on 11/22/13.
//
//

#include "SpaceShip.h"


void SpaceShip::setup( int _index, ofVec2f _pos, ofImage _spaceImage){
    
    { // Mauricio
        pos = _pos;
        //vel = _vel;
        spaceImage = _spaceImage;
        //spaceShipSize = 50;
        //rotAngle = 0;
        //size = 150;
        inc = 20;
        //rotAngleInc = 1 * 0.15;
        propeller.loadImage("propeller.png");
    }
    
    { // Matt
        controlIndex = _index;
        
        // Angled toward the center.
        if ( controlIndex == 0 ) rotAngle = PI + PI / 4;
        else if ( controlIndex == 1 ) rotAngle = PI - PI / 4;
        else if ( controlIndex == 2 ) rotAngle = TWO_PI - PI / 4;
        else if ( controlIndex == 3 ) rotAngle = PI / 4;
        // Alternatively, facing each other vertically.
        /*if ( controlIndex == 0 || controlIndex == 1 ) {
         rotAngle = PI;
         } else {
         rotAngle = 0;
         }*/
        
        rotAngleInc = 0.75 * 0.15;
        vel.set( 0 );
        acc.set( 0 );
        rotateCCWise = rotateCWise = notAngled = addToSpeed = propel = fire = bReadyToFire = bFiring = bDestroyMe = false;
        allowAction = true;
        fireTimer = firePacer = 0;
        timerMax = 30;
        pacerMax = 10;
        boost = 0.3;
        size = 150/2;
        engineSize = size / 3;
        healthMax = 100;
        health = healthMax;
        maxSpeed = 7;
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
        
        if ( propel ) {
            // Accelerate.
            applyAngularForce( boost, rotAngle );
        }
        if ( fire ) {
            if ( allowAction ) {
                // Prep for firing.
                /*if ( fireTimer == 0 ) {
                    fireTimer = timerMax;
                    //bFiring = true;
                    //allowAction = false;
                } else { */
                    bFiring = true;
                    //fireTimer = 0;
                    //cout<<"yes!"<<endl;
                }
                allowAction = false;
            //}
        } else {
            bFiring = false;
            firePacer = 0;
            allowAction = true;
        }
        
        vel += acc;
        
        // Limit the velocity.
        if ( fabs( vel.x ) > maxSpeed ) {
            vel.x = ( vel.x / fabs( vel.x ) ) * maxSpeed;
        }
        if ( fabs( vel.y ) > maxSpeed ) {
            vel.y = ( vel.y / fabs( vel.y ) ) * maxSpeed;
        }
        
        pos += vel;
        
        // Pac-man across to the other side.
        float margin = 50;
        if ( pos.x < -margin ) {
            pos.x = ofGetWindowWidth() + margin;
        }
        if ( pos.x > ofGetWindowWidth() + margin ) {
            pos.x = -margin;
        }
        if ( pos.y < -margin ) {
            pos.y = ofGetWindowHeight() + margin;
        }
        if ( pos.y > ofGetWindowHeight() + margin ) {
            pos.y = -margin;
        }
        
        if ( health <= 0 ) {
            bDestroyMe = true;
        }
        
        float damping = 0.999;
        //vel *= damping;
        acc.set( 0 );
    }
}


void SpaceShip::draw(){
    
    { // Mauricio
//        ofSetColor( colorPlayer);
        ofPushMatrix();{
            
            //        ofTranslate( pos.x, pos.y);
            ofSetRectMode(OF_RECTMODE_CENTER);
            //ofEllipse( pos.x, pos.y, size, size);
            { // Matt
                ofNoFill();
                ofSetLineWidth(4);
                // Draw the hollow track for the engine.
//                ofEllipse( pos.x, pos.y, size, size);
                ofSetLineWidth(1);
                ofFill();
                ofPushMatrix();{
                    ofTranslate( pos.x, pos.y );
                    float rotAng = atan2( vel.y, vel.x ) + PI / 2;
                    // Rotate to face in the direction of velocity.
                    ofRotate(ofRadToDeg( rotAng ) );
                    float mult = size / 2.5;
                    float ang = PI / 5;
                    spaceImage.draw(0,0);
                    // Draw the triangular ship.
//                    ofTriangle(0, -mult, sin(-ang) * mult, cos(-ang) * mult, sin(ang) * mult, cos(ang) * mult);
                    ofSetLineWidth(2);
                    // Draw the cross-braces to attach the ship to the track.
//                    ofLine(-size /2, 0, size / 2, 0);
//                    ofLine(0, -size /2, 0, size / 2);
                    ofSetLineWidth(1);
                }ofPopMatrix();
            } // End Matt
            ofPushMatrix();{
                
                ofTranslate( pos.x, pos.y);
                
                { // Matt
                    // Draw the health bar
                    ofSetRectMode( OF_RECTMODE_CORNER );
                    float offset = 1;
                    float offsetBar = 10;
                    float barHeight = 10;
                    float barLength = size;
                    float currentHealth = ofMap( health, 0, healthMax, 0, barLength - offset * 2 );
                    // The border.
                    ofSetColor( 255 );
                    ofNoFill();
                    ofRect( -size / 2, size / 2 + offsetBar, barLength, barHeight );
                    ofFill();
                    // The current health.
                    ofSetColor( 0, 255, 0 );
                    ofRect( -size / 2 + offset, size / 2 + offsetBar + offset, currentHealth, barHeight - offset * 2 );
                } // End Matt
                
                // Draw the engine--Matt
                ofSetRectMode( OF_RECTMODE_CORNER );
                // Matt
                ofSetColor( 255); //This serves as clearing the color buffer
                //Mauricio this is the final art for the propeller
           
                ofPushMatrix();{
                    
                    ofSetRectMode(OF_RECTMODE_CENTER);
                    ofTranslate( sin( rotAngle + PI) * engineSize * 2, cos( rotAngle + PI) * engineSize * 2);
                    ofRotate( ofRadToDeg(-rotAngle) );
                    propeller.draw(0,0);
                    
                }ofPopMatrix();
                
                
            }ofPopMatrix();
            
            
            
        }ofPopMatrix();
    }
    
    /*{ // Debugging controls by showing them on-screen.
        ofSetColor(255);
        if (controlIndex == 0) {
            if (rotateCCWise) ofDrawBitmapString("q", 10, 10);
            if (propel) ofDrawBitmapString("w", 20, 10);
            if (fire) ofDrawBitmapString("e", 30, 10);
        } else if (controlIndex == 1) {
            if (rotateCCWise) ofDrawBitmapString("i", 40, 10);
            if (propel) ofDrawBitmapString("o", 50, 10);
            if (fire) ofDrawBitmapString("p", 60, 10);
        } else if (controlIndex == 2) {
            if (rotateCCWise) ofDrawBitmapString("Q", 70, 10);
            if (propel) ofDrawBitmapString("W", 80, 10);
            if (fire) ofDrawBitmapString("E", 90, 10);
        } else if (controlIndex == 3) {
            if (rotateCCWise) ofDrawBitmapString("I", 100, 10);
            if (propel) ofDrawBitmapString("O", 110, 10);
            if (fire) ofDrawBitmapString("P", 120, 10);
        }
    }*/
}

void SpaceShip::applyForce( ofVec2f _force ) {
    
    { // Matt
        // Apply the force using vector math (doesn't require an angle).
        acc += _force;
    }
}

void SpaceShip::applyAngularForce( float _force, float _ang ) {
    
    { // Matt
        // Apply the force in the angle opposite the direction of the engine.
        float ang = _ang - PI;
        ofVec2f force;
        force.x = sin( ang ) * _force;
        force.y = cos( ang ) * _force;
        acc += force;
    }
}