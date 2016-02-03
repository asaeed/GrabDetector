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
    
    windowBorder = ofRectangle(10, 10, ofGetWidth()-20, ofGetHeight()-20);
}

void Zones::update() {
    if (isDragging) {
        // move the zone as the mouse moves
        allZones[dragRectIndex].position = dragRectPosition + ofPoint(ofGetMouseX() - mouseStart.x, ofGetMouseY() - mouseStart.y);
    }
}

void Zones::draw() {
    
    // draw the zones as rects
    ofFill();
    int i = 0;
    for (ofRectangle r : allZones) {
        ofSetColor(255, 0, 255, 80);
        ofDrawRectangle(r);
        
        // label the zone with id
        ofSetColor(255, 255, 255);
        stringstream reportStr;
        reportStr << i << endl;
        ofDrawBitmapString(reportStr.str(), r.position.x + 4, r.position.y + 14);
        
        i++;
    }
    
    // draw the rect being drawn
    if (isDrawing) {
        ofNoFill();
        ofSetHexColor(0xff00ff);
        ofDrawRectangle(mouseStart, ofGetMouseX() - mouseStart.x, ofGetMouseY() - mouseStart.y);
    }
    
    // if it's out of bounds of window, show it will be deleted
    if (isDragging) {
        if (!windowBorder.intersects(allZones[dragRectIndex])) {
            ofNoFill();
            ofSetLineWidth(10);
            ofSetColor(255, 0, 0);
            ofDrawRectangle(windowBorder);
            ofSetLineWidth(1);
        }
    }
    
}

void Zones::mousePressed(int x, int y, int button) {
    // first check if you hit an existing rect
    dragRectIndex = -1;;
    for (int i = allZones.size() - 1; i >= 0; i--) {
        if (allZones[i].inside(x, y)) {
            
            // TODO: if on bottom right corner, do resizing
            
            // else do dragging
            isDragging = true;
            dragRectIndex = i;
            dragRectPosition = allZones[i].position;
            
            break;
        }
    }
    
    //cout << dragRectIndex << endl;
    
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
    
    // delete zone if dragged out of bounds
    if (isDragging) {
        if (!windowBorder.intersects(allZones[dragRectIndex])) {
            allZones.erase(allZones.begin() + dragRectIndex);
        }

    }
    
    // reset
    isDrawing = false;
    isDragging = false;
    
    // TODO: here could use events to send new zone data to Vision class
    
}