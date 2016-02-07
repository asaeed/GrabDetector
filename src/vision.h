//
//  vision.hpp
//  GrabDetector
//
//  Created by Ahmad Saeed on 1/30/16.
//
//

#include "ofMain.h"
#include "ofxOpenCv.h"

#define _USE_LIVE_VIDEO

#ifndef vision_h
#define vision_h

class Zones;

class Vision {
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void refreshZones();
    
    void glue(Zones * z);
    Zones * zonesPtr;
    ofRectangle curZone;
    map<int,int> zonesBreached;
    
#ifdef _USE_LIVE_VIDEO
    ofVideoGrabber 		video;
#else
    ofVideoPlayer 		video;
#endif
    
    ofxCvColorImage	colorImage;
    ofxCvColorImage colorPrev;
    
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayPrev;
    ofxCvGrayscaleImage grayDiff;
    
    unsigned char * colorPixels;
    unsigned char * grayPixels;
    
    ofxCvContourFinder contourFinder;
    
    int vidWidth;
    int vidHeight;
    int vidRenderWidth;
    int vidRenderHeight;
    
    int threshold;
    bool bLearnBakground;
    
    unsigned int curTime;
    unsigned int lastTime;
    unsigned int interval;
    
    ofSoundPlayer soundPlayer;

};


#endif
