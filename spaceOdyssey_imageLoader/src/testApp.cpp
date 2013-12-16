#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofBackground(0);
    counter = 0;
    frameNum = 0;
//    for( int i =0; i < 50; i++){
//        
//        string frameNum = ofToString(i);
//        metroid[i].loadImage(frameNum + ".png");
//    }
    
    frameNum2 = 0;
    counter2 = 1;
    
    for( int i = 1; i < 200; i++){
        
        string frameNum2 = ofToString(i);
        galaxy[i].loadImage(frameNum2 + ".png");
    }
}

//--------------------------------------------------------------
void testApp::update(){
    
    //This is all thanks to Jennifer Presto. A very quite clever piece of code that allows us to go back and forth through a number
//    frameNum = abs( abs(49 - counter) - 49);
//    counter++;
//    
//    if( counter == 100){
//        
//        counter = 0;
//    }
    
    frameNum2 = abs ( abs(98 - counter2) - 98);
    counter2++;
    
    if( counter2 == 200){
        
        counter2 = 0;
    }
    
    cout << counter2 << endl;


}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    
//    metroid[frameNum].draw(pos.x, pos.y);
    galaxy[frameNum2].draw(0 , 0);
    ofDrawBitmapString(ofToString(frameNum2), 10, 10);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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
