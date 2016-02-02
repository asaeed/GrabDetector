#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    vision.setup();
    gui.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(100,100,100);
    
    vision.update();
    gui.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    vision.draw();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    vision.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
