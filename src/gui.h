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
#include "ofxDatGui.h"

class Gui {
    
    
public:
    void setup();
    void update();
    void draw();
    bool mousePressed(int x, int y, int button);
    
    ofxDatGui * datgui;
    
    ofxDatGuiSlider * slider;
    ofxDatGuiSlider * sliderInt;
    ofxDatGuiSlider * sliderFloat;
    
    ofParameter<int> ofParamInt;
    ofParameter<float> ofParamFloat;
    
    void onParamIntChanged(int & pInt);
    void onParamFloatChanged(float & pFloat);
    void onSliderEvent(ofxDatGuiSliderEvent e);
};


#endif
