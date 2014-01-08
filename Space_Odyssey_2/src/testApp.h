#pragma once

/*
 
 A NOTE FROM MATT--
 
 M^2 Studios presents:
 
 SPACE ODYSSEY 2: MICHAEL KAHANE'S DEFECTION
 
 the follow-up to the award-winning* Space Odyssey ( which was created by M^3 Studios** in two weeks across Spring 2013 for Major Studio 2 and may be played here: http://www.openprocessing.org/sketch/93227 ).
 
 M^2 Studios is Mauricio Sanchez-Duque and Matt Griffis.
 
 * i.e. played obsessively by classmates)
 ** Mauricio Sanchez-Duque, Michael Kahane and Matt Griffis
 
 */

#include "ofMain.h"
#include "SpaceShip.h"
#include "Enemy.h"
#include "Bullet.h"
#include "WarBackground.h"
#include "ofxOsc.h"
#include "Michael.h"



// Question for Charlie: how to pass a function into a function.

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
    
    //----------NEW STUFF STARTS HERE----------
    
    // Matt
    bool killFrameRate;
    ofVec2f pos;
    //ofEasyCam cam;
    void drawGalaxy();
    // For branching:
    void branch( float length, float _ang1, float _ang2, float _mult = 1, bool _trans = false );
    float theta = 30;
    int generation;
    Enemy metroid;
    vector< SpaceShip > shipList;
    vector< Bullet > bulletList;
    void collideSpaceshipsAndBullets();
    void collideSpaceshipsAndSpaceships();
    void collideEnemyAndBullets();
    void collideSpaceshipsAndEnemy();
    
    // Mauricio
    //SpaceShip ship1;
    
    ofFbo enemyFbo;
    WarBackground secondBackground;
    
    //Values passed to the enemy
    int counter, frameNum;
//    ofVec2f pos;
    
    //Matt
    void checkOsc();
    ofxOscReceiver mReceiver;
    int gameState;
    ofImage startScreen, spaceShip;
    ofTrueTypeFont font, fontSmall;
    int startScreenFade, startScreenFadeVel;
    
    deque < Michael > kahane;
    
};
