//
//  zones.cpp
//  GrabDetector
//
//  Created by Ahmad Saeed on 2/2/16.
//
//

#include "zones.h"

void Zones::setup() {
    isDrawing = false;
    isDragging = false;
    mouseStart = ofPoint(0, 0);
    mouseEnd = ofPoint(0, 0);
}

void Zones::update() {
    if (isDragging) {
        allZones[dragRectIndex].position = dragRectPosition + ofPoint(ofGetMouseX() - mouseStart.x, ofGetMouseY() - mouseStart.y);
    }
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
    if (isDrawing) {
        ofDrawRectangle(mouseStart, ofGetMouseX() - mouseStart.x, ofGetMouseY() - mouseStart.y);
    }
    
}

void Zones::mousePressed(int x, int y, int button) {
    // first check if you hit an existing rect
    dragRectIndex = -1;;
    for (int i = allZones.size() - 1; i >= 0; i--) {
        if (allZones[i].inside(x, y)) {
            isDragging = true;
            dragRectIndex = i;
            dragRectPosition = allZones[i].position;
            break;
        }
    }
    
    cout << dragRectIndex << endl;
    
    // if not, then you're drawing
    if (dragRectIndex == -1) {
        isDrawing = true;
    }
    
    // either way store mouse start
    mouseStart = ofPoint(x, y);
}

void Zones::mouseReleased(int x, int y, int button) {
    // save new rect if drawing
    if (isDrawing) {
        mouseEnd = ofPoint(x, y);
        allZones.push_back(ofRectangle(mouseStart, mouseEnd));
    }
    
    // reset
    isDrawing = false;
    isDragging = false;
}