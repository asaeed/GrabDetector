#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    vision.glue(&zones);
    zones.glue(&vision);
    gui.glue(&vision);
    
    vision.setup();
    gui.setup();
    zones.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vision.update();
    gui.update();
    zones.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(100,100,100);
    
    vision.draw();
    gui.draw();
    zones.draw();
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
    if (gui.mousePressed(x, y, button)) return;
    
    zones.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    zones.mouseReleased(x, y, button);
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
