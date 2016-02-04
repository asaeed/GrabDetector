//
//  zones.hpp
//  GrabDetector
//
//  Created by Ahmad Saeed on 2/2/16.
//
//

#ifndef zones_h
#define zones_h

#include "ofMain.h"
#include "ofxGui.h"

class Zones {
    
public:
    void setup();
    void update();
    void draw();
    
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    vector<ofRectangle> allZones;
    ofRectangle windowBorder;
    ofPoint mouseStart;
    ofPoint mouseEnd;
    float minSize;
    bool isDrawing;
    bool isDragging;
    bool isResizing;
    
    ofRectangle newRect;
    int dragRectIndex;
    ofPoint dragRectPosition;
    float dragRectWidth;
    float dragRectHeight;
    
};


#endif
