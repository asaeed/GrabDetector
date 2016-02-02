//
//  zones.cpp
//  GrabDetector
//
//  Created by Ahmad Saeed on 2/2/16.
//
//

#include "zones.h"

void Zones::setup() {
    isPressed = false;
    rectStart = ofPoint(0, 0);
    rectEnd = ofPoint(0, 0);
}

void Zones::update() {
    
}

void Zones::draw() {
    
    // draw the rects in zones
    ofFill();
    ofSetColor(255, 0, 255, 80);
    for (ofRectangle r : allZones) {
        ofDrawRectangle(r);
    }
    
    // draw the rect being drawn
    ofNoFill();
    ofSetHexColor(0xff00ff);
    if (isPressed) {
        ofDrawRectangle(rectStart, ofGetMouseX() - rectStart.x, ofGetMouseY() - rectStart.y);
    }
    
}

void Zones::mousePressed(int x, int y, int button) {
    isPressed = true;
    rectStart = ofPoint(x, y);
}

void Zones::mouseReleased(int x, int y, int button) {
    // set rect end point
    rectEnd = ofPoint(x, y);
    
    // save rect
    allZones.push_back(ofRectangle(rectStart, rectEnd));
    
    // reset
    isPressed = false;
}