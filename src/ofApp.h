#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#include "gui.h"
#include "vision.h"
#include "zones.h"

class ofApp : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    
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
    
    // TODO: classes representing app components are declared here
    // they need to be either set up as singletons so they can instantiate each other in setup
    // or only instantiate here and use the event system to communicate among them

    Vision vision;
    Gui gui;
    Zones zones;
    
    
};

