#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate( 60 );
    ofSetVerticalSync( true );
    //CGDisplayHideCursor(NULL);
    ofBackground( 0 );
    
    gameState = 0;
    
    key1 = key2 = key3 = key4 = key5 = key6 = 0;
    
    ipAddress = "";
    
    font.loadFont( "blocked.ttf", 72 );
    fontMedium.loadFont( "blocked.ttf", 48 );
    fontSmall.loadFont( "blocked.ttf", 36 );
    fontSmallest.loadFont( "blocked.ttf", 18 );
}

//--------------------------------------------------------------
void testApp::addToString( string _input ) {
    
    stringList.push_back( _input );
}

//--------------------------------------------------------------
void testApp::update(){
    
    if ( gameState == 0 ) { // Setup the IP address on the first screen.
        
        ipAddress = ""; // Clear the string.
        
        for ( int i = 0; i < stringList.size(); i++ ) {
            ipAddress += stringList[ i ]; // Concatenate all the strings in the vector.
        }
        return;
    }
    
    // Now we're on the game screen (gameState = 1 ).
    
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
    
    if ( gameState == 0 ) { // Draw the first screen.
        
        ofPushMatrix();{
            
            ofTranslate( 0, -50 );
            
            ofSetColor(255);
            font.drawString( "Space Odyssey 2", ofGetWindowWidth() / 2 - 650, ofGetWindowHeight() / 2 - 150 );
            fontSmall.drawString( "Secondary controller setup", ofGetWindowWidth() / 2 - 300, ofGetWindowHeight() / 2 - 50 );
            fontSmallest.drawString( "   Players 3 and 4 can play using this computer's keyboard.\n\nYou will need the IP address of the computer running the game.", ofGetWindowWidth() / 2 - 550, ofGetWindowHeight() / 2 + 75 );
            float xPos = ofGetWindowWidth() / 2 - 450;
            float yPos = ofGetWindowHeight() / 2 + 275;
            ofSetColor( 0, 200, 0 );
            fontSmall.drawString( "Enter IP address: ", xPos, yPos );
            ofSetColor( 255 );
            fontSmall.drawString( ipAddress, xPos + 610, yPos );
            float xPos2 = ofGetWindowWidth() / 2 - 560;
            float yPos2 = ofGetWindowHeight() / 2 + 400;
            if ( stringList.size() != 0 ) {
                
                ofSetColor( 255 );
                fontMedium.drawString( "Press ", xPos2, yPos2 );
                ofSetColor( 200, 0, 0 );
                fontMedium.drawString( "[SPACE]", xPos2 + 275, yPos2 );
                ofSetColor( 255 );
                fontMedium.drawString( " to continue.", xPos2 + 555, yPos2 );
            }
        }ofPopMatrix();
        return;
    }
    
    // Now we're on the game screen (gameState = 1).
    
    ofPushMatrix();{
        
        ofTranslate( -150, -100 );
        
        ofSetColor(255);
        float xPos = ofGetWindowWidth() / 2 - 250;
        float yPos = ofGetWindowHeight() / 2 - 100;
        fontSmall.drawString( "Player 3:\n\nuse QWE.", xPos, yPos );
        fontSmall.drawString( "Player 4:\n\nuse IOP.", xPos + 500, yPos );
        fontSmallest.drawString("Press ESC to quit. Press B to run setup again.", ofGetWindowWidth() / 2 - 250, ofGetWindowHeight() / 2 + 150 );
        fontMedium.drawString("Look at the other screen!", ofGetWindowWidth() / 2 - 425, ofGetWindowHeight() / 2 + 300 );
        
    }ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch( key ) {
            
            // Restart
        case 'b':
        case 'B':
            if ( gameState == 1 ) {
                stringList.clear();
                setup();
            }
            break;
            
        { // Input IP address.
            
            // Add to the string.
        case '0':
            if ( gameState == 0 ) addToString( "0" );
            break;
        case '1':
            if ( gameState == 0 ) addToString( "1" );
            break;
        case '2':
            if ( gameState == 0 ) addToString( "2" );
            break;
        case '3':
            if ( gameState == 0 ) addToString( "3" );
            break;
        case '4':
            if ( gameState == 0 ) addToString( "4" );
            break;
        case '5':
            if ( gameState == 0 ) addToString( "5" );
            break;
        case '6':
            if ( gameState == 0 ) addToString( "6" );
            break;
        case '7':
            if ( gameState == 0 ) addToString( "7" );
            break;
        case '8':
            if ( gameState == 0 ) addToString( "8" );
            break;
        case '9':
            if ( gameState == 0 ) addToString( "9" );
            break;
        case '.':
            if ( gameState == 0 ) addToString( "." );
            break;
            // Subtract from the string.
        case OF_KEY_BACKSPACE:
            if ( gameState == 0 ) {
                if ( stringList.size() != 0 ) {
                    stringList.erase( stringList.end() );
                }
            }
            break;
            // Submit choice and setup the receiver.
        case ' ':
            if ( gameState == 0 && stringList.size() != 0 ) {
                mSender.setup( ipAddress, 99999 );
                //mSender.setup( "localhost", 99999 );
                gameState = 1;
            }
            break;
            
        } // End input IP address.
            
        { // Player controls.
            
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
            
        } // End player controls.
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    switch( key ) {
            
        { // Player controls.
            
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
            
        } // End player controls.
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
