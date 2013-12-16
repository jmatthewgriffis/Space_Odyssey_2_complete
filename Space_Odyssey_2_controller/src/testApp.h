#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxOscSender mSender;
    
    int key1, key2, key3, key4, key5, key6; // These function as booleans to indicate key status but they have to be ints so OSC can send them.
    
    vector< string > stringList; // Store the key input for IP address.
    void addToString( string _input );
    string ipAddress;
    
    int gameState;
    
    ofTrueTypeFont font, fontMedium, fontSmall, fontSmallest;
};
