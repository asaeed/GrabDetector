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

#ifndef vision_hpp
#define vision_hpp

class Vision {
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
#ifdef _USE_LIVE_VIDEO
    ofVideoGrabber 		vidGrabber;
#else
    ofVideoPlayer 		vidPlayer;
#endif
    
    ofxCvColorImage	colorImage;
    ofxCvColorImage colorPrev;
    
    ofxCvGrayscaleImage redImage;
    ofxCvGrayscaleImage redPrev;
    ofxCvGrayscaleImage redDiff;
    
    ofxCvGrayscaleImage greenImage;
    ofxCvGrayscaleImage greenPrev;
    ofxCvGrayscaleImage greenDiff;
    
    ofxCvGrayscaleImage blueImage;
    ofxCvGrayscaleImage bluePrev;
    ofxCvGrayscaleImage blueDiff;
    
    ofPixels colorImagePixels;
    ofPixels colorPrevPixels;
    
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayPrev;
    ofxCvGrayscaleImage grayDiff;
    
    ofxCvContourFinder contourFinder;
    
    int vidWidth;
    int vidHeight;
    int vidRenderWidth;
    int vidRenderHeight;
    
    int threshold;
    bool bLearnBakground;
};


#endif
