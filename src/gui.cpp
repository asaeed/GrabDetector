//
//  gui.cpp
//  GrabDetector
//
//  Created by Ahmad Saeed on 1/29/16.
//
//

#include "gui.h"

void Gui::setup(){
    ofSetVerticalSync(true);
    
    // we add this listener before setting up so the initial circle resolution is correct
    circleResolution.addListener(this, &Gui::circleResolutionChanged);
    ringButton.addListener(this, &Gui::ringButtonPressed);
    
    gui.setup(); // most of the time you don't need a name
    gui.add(filled.setup("fill", false));
    gui.add(radius.setup("radius", 140, 10, 300));
    gui.add(center.setup("center", ofVec2f(ofGetWidth()*.5, ofGetHeight()*.5), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
    gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(circleResolution.setup("circle res", 5, 3, 90));
    gui.add(twoCircles.setup("two circles"));
    gui.add(ringButton.setup("ring"));
    gui.add(screenSize.setup("screen size", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));
    
    bHide = false;
    
    ring.load("ring.wav");
}

//--------------------------------------------------------------
void Gui::exit(){
    ringButton.removeListener(this, &Gui::ringButtonPressed);
}

//--------------------------------------------------------------
void Gui::circleResolutionChanged(int &circleResolution){
    ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void Gui::ringButtonPressed(){
    ring.play();
}

//--------------------------------------------------------------
void Gui::update(){
    ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void Gui::draw(){
    
    if(filled){
        ofFill();
    }else{
        ofNoFill();
    }
    
    ofSetColor(color);
    if(twoCircles){
        ofDrawCircle(center->x-radius*.5, center->y, radius );
        ofDrawCircle(center->x+radius*.5, center->y, radius );
    }else{
        ofDrawCircle((ofVec2f)center, radius );
    }
    
    // auto draw?
    // should the gui control hiding?
    if(!bHide){
        gui.draw();
    }
}

//--------------------------------------------------------------
void Gui::keyPressed(int key){
    if(key == 'h'){
        bHide = !bHide;
    }
    else if(key == 's'){
        gui.saveToFile("settings.xml");
    }
    else if(key == 'l'){
        gui.loadFromFile("settings.xml");
    }
    else if(key == ' '){
        color = ofColor(255);
    }
}

//--------------------------------------------------------------
void Gui::windowResized(int w, int h){
    screenSize = ofToString(w) + "x" + ofToString(h);
}
