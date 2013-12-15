//
//  War Background.cpp
//  Space_Odyssey_2
//
//  Created by Mauricio Sanchez Duque on 12/9/13.
//
//

#include "WarBackground.h"

WarBackground::WarBackground(){
    
}

void WarBackground::setup(){
    
    
    for( int i = 0; i < NUM_OF_VEHICLES ; i++){
        
        addVehicle();
    }
}

void WarBackground::addVehicle(){
    
    ofVec2f _pos = ofVec2f(0 , 0)/*ofVec2f(ofRandom( ofGetWindowWidth(), ofGetWindowHeight() ) )*/;
    ofVec2f _vel = ofVec2f( ofRandom( - 1, 1 ) );
    ofVec2f _dest = ofVec2f(ofRandom( 0, ofGetWindowWidth()), ofRandom(0, ofGetWindowHeight() ) );
    Vehicle tmp( _pos, _vel, _dest ) ;
    vList.push_back( tmp);
    
    
}

void WarBackground::update(){
    
    deque< Vehicle >::iterator v1;
    for( v1 = vList.begin(); v1 != vList.end(); v1++){
        
        v1->seek(v1->dest);
        
        deque < Vehicle >::iterator v2 = v1 + 1;
        
        if( v1->pos.distance( v2->pos ) < 100){
            
            v1->addRepulsionforce(v2->pos);
            v2->addRepulsionforce(v1->pos);
        }
        
        if( v1->pos.distance(v1->dest) < 5){
            
            v1->dest = ofVec2f( ofRandom( 0, ofGetWindowWidth()), ofRandom( 0, ofGetWindowHeight()));
            
        }
        
        v1->update();
        
    }
    
}

void WarBackground::draw(){
    
    int i = 0;
    deque < Vehicle >::iterator v1;
    for( v1 = vList.begin(); v1 != vList.end(); v1++){
        
        ofSetColor(255);
        ofCircle(v1->dest, 1.5);
        v1->draw();
        ofDrawBitmapString(ofToString(v1->vel.x), 20, i * 10);
        i++;
    }
    
}