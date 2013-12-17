#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    { // Mauricio
        //ship1.setup(ofVec2f( ofGetWindowWidth() / 2 , ofGetWindowHeight() / 2), 2, ofColor( ofColor( 20, 20, 200)));
        //        enemyFbo.allocate( 0 , 0 );
        ofSeedRandom();
        secondBackground.setup();
    }
    
    
    { // Matt
        
        gameState = 0;
        ofSetRectMode( OF_RECTMODE_CORNER );
        startScreen.loadImage("spaceships_start_screen.png");
        
        // This one listens to the same port that we were sending to in the other app.
        mReceiver.setup( 99999 );
        
        killFrameRate = false; // Turn on the enemy and background, watch the framerate drop.
        // Maintenance
        ofSetVerticalSync( true );
        ofSetFrameRate( 60 );
        ofSetCircleResolution( 100 );
        ofEnableAlphaBlending();
        ofBackground( 0 );
        //ofHideCursor(); // Doesn't work.
        CGDisplayHideCursor(NULL); // But this does.
        generation = 0;
        //cam.setDistance(0);
        metroid.setup();
        
        { // Make the ships.
            float offset = 100;
            for ( int i = 0; i < 4; i++ ) {
                SpaceShip tmp;
                string picNum =  ofToString(i);
                // We pass in the value of i to set a permanent "control index," to which the specific controls are tied. That way if a ship gets destroyed and the vector indicies get changed, the controls stay the same. -Matt
                spaceShip.loadImage("spaceship" + picNum + ".png");
                tmp.setup( i, ofVec2f( offset, offset ), spaceShip);
                shipList.push_back( tmp );
            }
            // Individual pos
            shipList[ 1 ].pos.set( ofGetWindowWidth() - offset, offset );
            shipList[ 2 ].pos.set( offset, ofGetWindowHeight() - offset );
            shipList[ 3 ].pos.set( ofGetWindowWidth() - offset, ofGetWindowHeight() - offset );
            // Individual color
            shipList[ 1 ].colorPlayer = ofColor( 200, 20, 20 );
            shipList[ 2 ].colorPlayer = ofColor( 100, 80, 20 );
            shipList[ 3 ].colorPlayer = ofColor( 0, 255, 20 );
        }
    }
    
    
    //-----------------Michael Kane's-----------------//
    //Michael was an important part of the previous sequel so we decided to call the second michael's kahane defection, this part of the code is actually his
    for( int i = 0; i < 50; i++){
    
        Michael tmp;
        float vx = ofRandom(-4,4);
        float vy = ofRandom(-4,4);
        tmp.setParams(metroid.pos, vx, vy);
        kahane.push_back(tmp);
        
    }
    
        
        
    
}

//--------------------------------------------------------------
bool bShouldIErase( Bullet &a ){
    
    // Note from Matt: Zach Lieberman showed me this method to remove an element from a vector. We create a boolean function, feed it a class, and pass a reference label that we make up (in this case 'a') so we can refer to the applicable object. Then we check for a certain condition which if met returns a boolean value of 'true.' Otherwise it returns 'false.'
    
    if ( a.bDestroyMe ) return true;
    else return false;
}

bool bShouldIErase2( SpaceShip &a ){
    
    // See note in previous function. -Matt
    if ( a.bDestroyMe ) return true;
    else return false;
}

//--------------------------------------------------------------
void testApp::update(){
    
    if ( gameState == 0 ) return;
    
    checkOsc(); //Matt
    
    { // Mauricio
        //ship1.update();
        //secondBackground.update();
        
        //Mauricio
        //After trying to coming up with a counter that goes up and down, Jennifer Presto provided this. withour her contribution it woudn't have been possible to achive it.
        frameNum = abs ( abs( 49 - counter) - 49);
        counter++;
        
        if( counter == 100){
            
            counter = 0;
        }
    }
    
    collideSpaceshipsAndBullets();
    collideSpaceshipsAndSpaceships();
    collideEnemyAndBullets();
    collideSpaceshipsAndEnemy();
    
    { // Matt
        if ( !metroid.bDestroyMe ) metroid.update(shipList);
        
        for ( int i = 0; i < shipList.size(); i++ ) {
            shipList[ i ].update();
            // Handle firing.
            if ( shipList[ i ].bFiring ) {
                if ( shipList[ i ].firePacer == 0 ) {
                    float fireAng = shipList[ i ].rotAngle - PI;
                    Bullet tmp( shipList[ i ].pos, fireAng );
                    bulletList.push_back( tmp );
                    shipList[ i ].firePacer = shipList[ i ].pacerMax;
                    shipList[ i ].applyAngularForce( 0.5, fireAng );
                }
            }
        }
        
        for ( int i = 0; i < bulletList.size(); i++ ) {
            bulletList[ i ].update();
        }
        
        // AWESOME, come back to this later.
        //        if ( shipList[ 0 ].shootBullet && shipList[ 0 ].allowAction ) {
        //            float fireAng = shipList[ 0 ].rotAngle - PI;
        //            Bullet tmp( shipList[ 0 ].pos, fireAng );
        //            bulletList.push_back( tmp );
        //        }
    }
    
    
    
    // Note from Matt: Following up the boolean function we created above, this oF function sorts the vector according to the values of the booleans and then removes any with a 'true' value:
    ofRemove( bulletList, bShouldIErase );
    ofRemove( shipList, bShouldIErase2 );
    
    if (metroid.bDestroyMe){
        
        
        deque<Michael>::iterator it;
        for( it = kahane.begin(); it != kahane.end(); it++){
            
            it->resetForces();
            it->addDampingForce();
            it->update();
        }
    
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    if ( gameState == 0 ) {
        //ofSetRectMode(OF_RECTMODE_CENTER);
        startScreen.draw( 0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        return;
    }
    
    //secondBackground.draw();
    
    // Matt
    //cout<<bulletList.size()<<endl;
    
    {//Mauricio
        //    enemyFbo.begin();
        //        ofSetColor(255, 255, 255);
        //        ofClear(255, 255, 255, 0);
        { // Matt
            //cam.begin(); //
            //cam.setupPerspective();
            /*if ( killFrameRate ) */drawGalaxy();
            //Mauricio: For some reason the only way that our metroid animation works is by passing the frameNum from the testApp. I initally had everything inside the class but it didn't work. Passing the frameNum throught the draw it works.
            if ( !metroid.bDestroyMe ) metroid.draw(frameNum);
        }
        //    enemyFbo.end();
        //        enemyFbo.draw( ofGetWindowWidth() , ofGetWindowHeight());
    }
    
    { // Mauricio
        //ship1.draw();
        
    }
    
    { // Matt
        for ( int i = 0; i < shipList.size(); i++ ) {
            shipList[ i ].draw();
        }
        
        for ( int i = 0; i < bulletList.size(); i++ ) {
            bulletList[ i ].draw();
        }
        
        //cam.end();
    }
    
    if( metroid.bDestroyMe){
        
        deque<Michael>::iterator it;
        for( it = kahane.begin(); it != kahane.end(); it++){
            
            it->draw();
        }
            
        
        }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    /*
     // Matt says: didn't use a Switch in Processing.
     { // Mauricio
     if( key == 'q' || key == 'Q'){
     
     //ship1.rotateCCWise = true;
     shipList[ 0 ].rotateCCWise = true; // Matt
     }
     
     if( key == 'e' || key == 'E'){
     
     //ship1.rotateCWise = true;
     shipList[ 0 ].rotateCWise = true; // Matt
     }
     
     if ( key == 'w' || key == 'W'){
     
     //ship1.fire = true;
     shipList[ 0 ].fire = true; // Matt
     }
     }
     */
    
    { // Matt
        
        switch( key ) {
                
            case ' ':
                if ( gameState == 0 ) gameState = 1;
                break;
                
                // Player controls
                
                // Player One
            case 'q':
            case 'Q':
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 0 ) {
                        shipList[ i ].rotateCCWise = true;
                    }
                }
                break;
                
            case 'w':
            case 'W':
            {
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 0 ) {
                        shipList[ i ].propel = true;
                    }
                }
                break;
            }
                
            case 'e':
            case 'E':
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 0 ) {
                        //shipList[ i ].rotateCWise = true;
                        shipList[ i ].fire = true;
                    }
                }
                break;
                
                // Player Two
            case 'i':
            case 'I':
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 1 ) {
                        shipList[ i ].rotateCCWise = true;
                    }
                }
                break;
                
            case 'o':
            case 'O':
            {
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 1 ) {
                        shipList[ i ].propel = true;
                    }
                }
                break;
            }
                
            case 'P':
            case 'p':
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 1 ) {
                        //shipList[ i ].rotateCWise = true;
                        shipList[ i ].fire = true;
                    }
                }
                break;
                
                /*
                 // Player Three
                 case 'v':
                 case 'V':
                 for ( int i = 0; i < shipList.size(); i++ ) {
                 if ( shipList[ i ].controlIndex == 2 ) {
                 shipList[ i ].rotateCCWise = true;
                 }
                 }
                 break;
                 
                 case 'n':
                 case 'N':
                 for ( int i = 0; i < shipList.size(); i++ ) {
                 if ( shipList[ i ].controlIndex == 2 ) {
                 shipList[ i ].rotateCWise = true;
                 }
                 }
                 break;
                 
                 case 'b':
                 case 'B':
                 {
                 for ( int i = 0; i < shipList.size(); i++ ) {
                 if ( shipList[ i ].controlIndex == 2 ) {
                 shipList[ i ].fire = true;
                 }
                 }
                 break;
                 }
                 
                 // Player Four
                 case OF_KEY_LEFT:
                 for ( int i = 0; i < shipList.size(); i++ ) {
                 if ( shipList[ i ].controlIndex == 3 ) {
                 shipList[ i ].rotateCCWise = true;
                 }
                 }
                 break;
                 
                 case OF_KEY_RIGHT:
                 for ( int i = 0; i < shipList.size(); i++ ) {
                 if ( shipList[ i ].controlIndex == 3 ) {
                 shipList[ i ].rotateCWise = true;
                 }
                 }
                 break;
                 
                 case OF_KEY_DOWN:
                 {
                 for ( int i = 0; i < shipList.size(); i++ ) {
                 if ( shipList[ i ].controlIndex == 3 ) {
                 shipList[ i ].fire = true;
                 }
                 }
                 break;
                 }
                 */
                
            { // Debug
                
                // Turn the galaxy and enemy on and off.
            case '1':
                killFrameRate = !killFrameRate;
                break;
                
                // Reset
            case 'r':
            case 'R':
                shipList.clear();
                bulletList.clear();
                setup();
                break;
            } // End debug.
        }
    } // End Matt
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    /*
     { // Mauricio
     if( key == 'q' || key == 'Q'){
     
     //ship1.rotateCCWise = false;
     shipList[ 0 ].rotateCCWise = false; // Matt
     
     }
     
     if( key == 'e' || key == 'E'){
     
     //ship1.rotateCWise = false;
     shipList[ 0 ].rotateCWise = false; // Matt
     }
     
     if ( key == 'w' || key == 'W'){
     
     //ship1.fire = false;
     shipList[ 0 ].fire = false; // Matt
     }
     }
     */
    
    { // Matt
        
        switch( key ) {
                
                // Player controls
                
                // Player One
            case 'q':
            case 'Q':
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 0 ) {
                        shipList[ i ].rotateCCWise = false;
                    }
                }
                break;
                
            case 'w':
            case 'W':
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 0 ) {
                        shipList[ i ].propel = false;
                    }
                }
                break;
                
            case 'e':
            case 'E':
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 0 ) {
                        //shipList[ i ].rotateCWise = false;
                        shipList[ i ].fire = false;
                    }
                }
                break;
                
                // Player Two
            case 'i':
            case 'I':
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 1 ) {
                        shipList[ i ].rotateCCWise = false;
                    }
                }
                break;
                
            case 'o':
            case 'O':
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 1 ) {
                        shipList[ i ].propel = false;
                    }
                }
                break;
                
            case 'p':
            case 'P':
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 1 ) {
                        //shipList[ i ].rotateCWise = false;
                        shipList[ i ].fire = false;
                    }
                }
                break;
                
                /*
                 // Player Three
                 case 'v':
                 case 'V':
                 for ( int i = 0; i < shipList.size(); i++ ) {
                 if ( shipList[ i ].controlIndex == 2 ) {
                 shipList[ i ].rotateCCWise = false;
                 }
                 }
                 break;
                 
                 case 'n':
                 case 'N':
                 for ( int i = 0; i < shipList.size(); i++ ) {
                 if ( shipList[ i ].controlIndex == 2 ) {
                 shipList[ i ].rotateCWise = false;
                 }
                 }
                 break;
                 
                 case 'b':
                 case 'B':
                 for ( int i = 0; i < shipList.size(); i++ ) {
                 if ( shipList[ i ].controlIndex == 2 ) {
                 shipList[ i ].fire = false;
                 }
                 }
                 break;
                 
                 // Player Four
                 case OF_KEY_LEFT:
                 for ( int i = 0; i < shipList.size(); i++ ) {
                 if ( shipList[ i ].controlIndex == 3 ) {
                 shipList[ i ].rotateCCWise = false;
                 }
                 }
                 break;
                 
                 case OF_KEY_RIGHT:
                 for ( int i = 0; i < shipList.size(); i++ ) {
                 if ( shipList[ i ].controlIndex == 3 ) {
                 shipList[ i ].rotateCWise = false;
                 }
                 }
                 break;
                 
                 case OF_KEY_DOWN:
                 for ( int i = 0; i < shipList.size(); i++ ) {
                 if ( shipList[ i ].controlIndex == 3 ) {
                 shipList[ i ].fire = false;
                 }
                 }
                 break;
                 */
                
        } // End Matt
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

//--------------------------------------------------------------
void testApp::collideSpaceshipsAndBullets() {
    
    { // Matt
        for ( int i = 0; i < bulletList.size(); i++ ) {
            for ( int j = 0; j < shipList.size(); j++ ) {
                float dist = bulletList[ i ].pos.distance( shipList[ j ].pos );
                if ( dist < bulletList[ i ].size + shipList[ j ].size / 2 ) {
                    shipList[ j ].applyForce( bulletList[ i ].vel * 0.2 );
                    shipList[ j ].health -= bulletList[ i ].damage;
                    bulletList[ i ].bDestroyMe = true;
                }
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::collideSpaceshipsAndSpaceships() {
    
    { // Matt
        for ( int i = 0; i < shipList.size(); i++ ) {
            for ( int j = 0; j < shipList.size(); j++ ) {
                if ( i != j ) { // Prevent ship colliding with self.
                    float dist = shipList[ i ].pos.distance( shipList[ j ].pos );
                    if ( dist < shipList[ i ].size / 2 + shipList[ j ].size / 2 ) {
                        // if traveling in the same direction lose some velocity from impact.
                        /*float dampen = 0.9;
                         shipList[ i ].vel.x *= dampen;
                         shipList[ j ].vel.x *= dampen;
                         shipList[ i ].vel.y *= dampen;
                         shipList[ j ].vel.y *= dampen;*/
                        
                        // if traveling in different direction apply the opposing force in the opposite direction.
                        if ( ( shipList[ i ].vel.x <= 0 && shipList[ j ].vel.x >= 0 ) || ( shipList[ j ].vel.x <= 0 && shipList[ i ].vel.x >= 0 ) ) {
                            shipList[ i ].applyForce( ofVec2f( shipList[ j ].vel.x, 0 ) );
                            shipList[ j ].applyForce( ofVec2f( shipList[ i ].vel.x, 0 ) );
                        }
                        if ( ( shipList[ i ].vel.y <= 0 && shipList[ j ].vel.y >= 0 ) || ( shipList[ j ].vel.y <= 0 && shipList[ i ].vel.y >= 0 ) ) {
                            shipList[ i ].applyForce( ofVec2f( 0, shipList[ j ].vel.y ) );
                            shipList[ j ].applyForce( ofVec2f( 0, shipList[ i ].vel.y ) );
                        }
                        
                        /*float damage = 10;
                         shipList[ i ].health -= damage;
                         shipList[ j ].health -= damage;*/
                    }
                }
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::collideEnemyAndBullets() {
    
    { // Matt
        for ( int i = 0; i < bulletList.size(); i++ ) {
            float dist = bulletList[ i ].pos.distance( ofVec2f( metroid.pos.x + 400, metroid.pos.y + 250 ) );
            if ( dist < 350 ) {
                metroid.health -= bulletList[ i ].damage;
                bulletList[ i ].bDestroyMe = true;
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::collideSpaceshipsAndEnemy() {
    
    { // Matt
        for ( int i = 0; i < shipList.size(); i++ ) {
            float dist = shipList[ i ].pos.distance( ofVec2f( metroid.pos.x + 400, metroid.pos.y + 250 ) );
            if ( dist < 350 ) {
                shipList[ i ].health -= 1;
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::branch( float length, float _ang1, float _ang2, float _mult, bool _trans ) {
    
    // Matt--this is copied and modified from Charlie's in-class example.
    
    { // Matt
        ofTranslate( 100, 0 );
        
        ofPushMatrix();
        ofLine( ofVec2f(0,0), ofVec2f(0, -length) );
        ofTranslate( 0, -length );
        
        generation++;
        
        float noise = ofNoise( generation, ofGetElapsedTimef() * 0.1 );
        
        if( length > 2 ){
            ofPushMatrix();{
                ofRotate( ( _ang1 + theta + noise * 10-5 ) * _mult );
                branch( length * 0.666, _ang1, _ang2, _mult, _trans );
            }ofPopMatrix();
            
            ofPushMatrix();{
                ofRotate( ( _ang2 + theta - noise * 10-5 ) * _mult );
                branch( length * 0.666, _ang1, _ang2, _mult, _trans );
            }ofPopMatrix();
        }
        
        ofPopMatrix();
        
        generation--;
    }
}

//--------------------------------------------------------------
void testApp::drawGalaxy() {
    
    { // Matt
        // Draw the galaxy.
        ofPushMatrix();{
            ofSetColor( 255 );
            ofTranslate( ofGetWindowWidth()/2, ofGetWindowHeight() );
            branch( 200, -45, 45, 1, true );
        }ofPopMatrix();
    }
}

//--------------------------------------------------------------
void testApp::checkOsc() {
    
    while( mReceiver.hasWaitingMessages() ) {
        ofxOscMessage m;
        mReceiver.getNextMessage( &m );
        
        string addr = m.getAddress();
        
        if ( addr == "/keyPressed" ) {
            
            int key1, key2, key3, key4, key5, key6;
            key1 = m.getArgAsInt32( 0 );
            key2 = m.getArgAsInt32( 1 );
            key3 = m.getArgAsInt32( 2 );
            key4 = m.getArgAsInt32( 3 );
            key5 = m.getArgAsInt32( 4 );
            key6 = m.getArgAsInt32( 5 );
            
            if ( key1 == 1 ) {
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 2 ) {
                        shipList[ i ].rotateCCWise = true;
                    }
                }
            } else {
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 2 ) {
                        shipList[ i ].rotateCCWise = false;
                    }
                }
            }
            
            if ( key2 == 1 ) {
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 2 ) {
                        shipList[ i ].propel = true;
                    }
                }
            } else {
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 2 ) {
                        shipList[ i ].propel = false;
                    }
                }
            }
            
            if ( key3 == 1 ) {
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 2 ) {
                        shipList[ i ].fire = true;
                    }
                }
            } else {
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 2 ) {
                        shipList[ i ].fire = false;
                    }
                }
            }
            
            if ( key4 == 1 ) {
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 3 ) {
                        shipList[ i ].rotateCCWise = true;
                    }
                }
            } else {
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 3 ) {
                        shipList[ i ].rotateCCWise = false;
                    }
                }
            }
            
            if ( key5 == 1 ) {
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 3 ) {
                        shipList[ i ].propel = true;
                    }
                }
            } else {
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 3 ) {
                        shipList[ i ].propel = false;
                    }
                }
            }
            
            if ( key6 == 1 ) {
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 3 ) {
                        shipList[ i ].fire = true;
                    }
                }
            } else {
                for ( int i = 0; i < shipList.size(); i++ ) {
                    if ( shipList[ i ].controlIndex == 3 ) {
                        shipList[ i ].fire = false;
                    }
                }
            }
        }
    }
}