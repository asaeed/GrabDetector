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
    ofNoFill();
    
    // draw the rects in zones
    ofSetHexColor(0x990099);
    for (ofRectangle r : allZones) {
        ofDrawRectangle(r);
    }
    
    // draw the rect being drawn
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
    allZones.push_back(ofRectangle(rectStart.x, rectStart.y, rectEnd.x-rectStart.x, rectEnd.y-rectStart.y));
    
    // reset
    isPressed = false;
}