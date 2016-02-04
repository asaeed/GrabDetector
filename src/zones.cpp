//
//  zones.cpp
//  GrabDetector
//
//  Created by Ahmad Saeed on 2/2/16.
//
//

#include "zones.h"

void Zones::setup(Vision * v) {
    isDrawing = false;
    isDragging = false;
    isResizing = false;
    mouseStart = ofPoint(0, 0);
    mouseEnd = ofPoint(0, 0);
    minSize = 20.0f;
    
    windowBorder = ofRectangle(10, 10, ofGetWidth()-20, ofGetHeight()-20);
    
    this->visionPtr = v;
}

void Zones::update() {
    if (isDragging) {
        // move the zone as the mouse moves
        allZones[dragRectIndex].position = dragRectPosition + ofPoint(ofGetMouseX() - mouseStart.x, ofGetMouseY() - mouseStart.y);
    } else if (isResizing) {
        allZones[dragRectIndex].width = MAX(minSize, dragRectWidth + ofGetMouseX() - mouseStart.x);
        allZones[dragRectIndex].height = MAX(minSize, dragRectHeight + ofGetMouseY() - mouseStart.y);
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
        ofSetColor(0, 255, 255);
        stringstream reportStr;
        reportStr << i << endl;
        ofDrawBitmapString(reportStr.str(), r.position.x + 4, r.position.y + 14);
        
        // bottom right corner hit area
        ofDrawRectangle(r.position.x + r.width - 10, r.position.y + r.height - 10, 10, 10);
        
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
    
    // either way store mouse start
    mouseStart = ofPoint(x, y);
    
    // first check if you hit an existing rect
    dragRectIndex = -1;;
    for (int i = allZones.size() - 1; i >= 0; i--) {
        if (allZones[i].inside(x, y)) {
            
            // if on bottom right corner, do resizing
            if (x > allZones[i].position.x + allZones[i].width - 10 && y > allZones[i].position.y + allZones[i].height - 10) {
                isResizing = true;
            } else {
                // else do dragging
                isDragging = true;
            }
            
            dragRectIndex = i;
            dragRectPosition = allZones[i].position;
            dragRectWidth = allZones[i].width;
            dragRectHeight = allZones[i].height;
            
            break;
        }
    }
    
    //cout << dragRectIndex << endl;
    
    // if not, then you're drawing
    if (dragRectIndex == -1) {
        isDrawing = true;
    }
}

void Zones::mouseReleased(int x, int y, int button) {
    // save new rect if drawing
    if (isDrawing) {
        mouseEnd = ofPoint(x, y);
        newRect = ofRectangle(mouseStart, mouseEnd);
        
        // make sure it has min width and height;
        if (newRect.width < minSize) newRect.setWidth(minSize);
        if (newRect.height < minSize) newRect.setHeight(minSize);
        allZones.push_back(newRect);
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
    isResizing = false;
    
    // use events to send new zone data to Vision class
    visionPtr->setZones(allZones);
}