//
//  Galaxy.cpp
//  spaceOdyssey_enemy
//
//  Created by Mauricio Sanchez Duque on 12/11/13.
//
//

#include "Galaxy.h"


void Galaxy::branch(float length, float _ang1, float _ang2, float _mult){
    
    ofTranslate( 200, 0 );
    
    ofPushMatrix();
    ofLine( ofVec2f(0,0), ofVec2f(0, -length) );
    ofTranslate( 0, -length );
    float generation = 0;
    
    generation++;
    
    float noise = ofNoise( generation, ofGetElapsedTimef() * 0.025 );
    
    if( length > 2 ){
        ofPushMatrix();{
            ofRotate( ( _ang1 + theta + noise * 10-5 ) * _mult );
            branch( length * 0.666, _ang1, _ang2, _mult);
        }ofPopMatrix();
        
        ofPushMatrix();{
            ofRotate( ( _ang2 + theta - noise * 10-5 ) * _mult );
            branch( length * 0.666, _ang1, _ang2, _mult);
        }ofPopMatrix();
    }
    
    ofPopMatrix();
    
    generation--;


}


void Galaxy::drawGalaxy(){

    ofPushMatrix();{
        ofSetColor( 255 );
        ofSetLineWidth(1);
        ofTranslate( ofGetWindowWidth() + 1200 , ofGetWindowHeight() + 1200 );
        ofRotate(-90);
        branch( 400, -45, 45, 1);
    }ofPopMatrix();
    
    
}