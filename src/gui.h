//
//  gui.h
//  GrabDetector
//
//  Created by Ahmad Saeed on 1/29/16.
//
//

#ifndef gui_h
#define gui_h

#include "ofMain.h"
#include "ofxGui.h"

class Gui {
    
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
    
    void circleResolutionChanged(int & circleResolution);
    void ringButtonPressed();
    
    bool bHide;
    
    ofxFloatSlider radius;
    ofxColorSlider color;
    ofxVec2Slider center;
    ofxIntSlider circleResolution;
    ofxToggle filled;
    ofxButton twoCircles;
    ofxButton ringButton;
    ofxLabel screenSize;
    
    ofxPanel gui;
    
    ofSoundPlayer ring;
};


#endif /* gui_h */
