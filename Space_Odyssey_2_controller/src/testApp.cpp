#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate( 60 );
    ofSetVerticalSync( true );
    CGDisplayHideCursor(NULL);
    
    // Edit the IP address to match the recipient.
    //mSender.setup( "169.254.136.111", 99999 );
    mSender.setup( "localhost", 99999 );
    
    ofBackground( 0 );
    
    key1 = key2 = key3 = key4 = key5 = key6 = 0;;
}

//--------------------------------------------------------------
void testApp::update(){
    
    ofxOscMessage m;
    
    // The slash is arbitrary but we'll use it to split messages when received.
    m.setAddress( "/keyPressed" ); // This is like the address on the envelope.
    m.addIntArg( key1 );
    m.addIntArg( key2 );
    m.addIntArg( key3 );
    m.addIntArg( key4 );
    m.addIntArg( key5 );
    m.addIntArg( key6 );
    
    mSender.sendMessage( m );
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofPushMatrix();{
        
        ofTranslate( -150, -100 );
        
        ofSetColor(255);
        ofDrawBitmapString("Look at the other screen!", ofGetWindowSize() / 2 );
        ofDrawBitmapString("Player 3: use QWE.  | Player 4: use IOP.", ofGetWindowWidth() / 2, ofGetWindowHeight() / 2 + 100 );
        ofDrawBitmapString("Press ESC to quit.", ofGetWindowWidth() / 2, ofGetWindowHeight() / 2 + 200 );
        
    }ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch( key ) {
            
            // Player controls
            
            // Player Three
        case 'q':
        case 'Q':
            key1 = 1;
            break;
            
        case 'w':
        case 'W':
            key2 = 1;
            break;
            
        case 'e':
        case 'E':
            key3 = 1;
            break;
            
            // Player Four
        case 'i':
        case 'I':
            key4 = 1;
            break;
            
        case 'o':
        case 'O':
            key5 = 1;
            break;
            
        case 'p':
        case 'P':
            key6 = 1;
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    switch( key ) {
            
            // Player controls
            
            // Player Three
        case 'q':
        case 'Q':
            key1 = 0;
            break;
            
        case 'w':
        case 'W':
            key2 = 0;
            break;
            
        case 'e':
        case 'E':
            key3 = 0;
            break;
            
            // Player Four
        case 'i':
        case 'I':
            key4 = 0;
            break;
            
        case 'o':
        case 'O':
            key5 = 0;
            break;
            
        case 'p':
        case 'P':
            key6 = 0;
            break;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
