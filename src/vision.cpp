//
//  vision.cpp
//  GrabDetector
//
//  Created by Ahmad Saeed on 1/30/16.
//
//

#include "vision.h"
#include "zones.h"

//--------------------------------------------------------------
// TODO: a better strategy might be to set the framerate very low
// (either on video stream or manually with a timer)
// around 1 fps, and check for differences just in the zones by
// comparing prev and current frame zone by zone.
//--------------------------------------------------------------


void Vision::setup(){
    vidWidth = 160;
    vidHeight = 120;
    vidRenderWidth = 640;
    vidRenderHeight = 480;
    
#ifdef _USE_LIVE_VIDEO
    video.setVerbose(true);
    video.setup(vidWidth, vidHeight);
#else
    video.load("fingers.mov");
    video.play();
    video.setLoopState(OF_LOOP_NORMAL);
#endif
    
    colorImage.allocate(vidWidth, vidHeight);
    colorPrev.allocate(vidWidth, vidHeight);
    colorDiff.allocate(vidWidth, vidHeight);
    
    // needed to allocate memory for these somehow
    colorPrevPixels = colorDiff.getPixels();
    colorDiffPixels = colorDiff.getPixels();
    
    grayImage.allocate(vidWidth, vidHeight);
    grayBg.allocate(vidWidth, vidHeight);
    grayPrev.allocate(vidWidth, vidHeight);
    grayDiff.allocate(vidWidth, vidHeight);
    
    grayDiffFromColor.allocate(vidWidth, vidHeight);
    
    grayDiffFromColorPixels = grayDiffFromColor.getPixels();
    
    bLearnBakground = true;
    threshold = 40;
}

void Vision::glue(Zones * z) {
    zonesPtr = z;
}

//--------------------------------------------------------------
void Vision::update(){
    
    video.update();
    
    if (video.isFrameNew()){

        colorImagePixels = video.getPixels();
        
        colorPrevPixels = colorPrev.getPixels();
        colorImage.setFromPixels(colorImagePixels, vidWidth, vidHeight);
        
        float dist;
        int amp = 1;
        for (int i = 0; i < vidWidth * vidHeight; i++) {
            colorDiffPixels[i*3] = abs(colorPrevPixels[i*3] - colorImagePixels[i*3]) * amp;
            colorDiffPixels[i*3+1] = abs(colorPrevPixels[i*3+1] - colorImagePixels[i*3+1]) * amp;
            colorDiffPixels[i*3+2] = abs(colorPrevPixels[i*3+2] - colorImagePixels[i*3+2]) * amp;
            
            dist = colorDiffPixels[i*3] * colorDiffPixels[i*3]
                + colorDiffPixels[i*3+1] * colorDiffPixels[i*3+1]
                + colorDiffPixels[i*3+2] * colorDiffPixels[i*3+2];
            dist = sqrt(dist);
        }
        
        colorDiff.setFromPixels(colorDiffPixels, vidWidth, vidHeight);
        grayDiffFromColor.setFromPixels(grayDiffFromColorPixels, vidWidth, vidHeight);
        grayDiffFromColor.threshold(threshold);
        
        
        // set grayscale image
        grayImage = colorImage;
        
        // learn background on user action
        if (bLearnBakground == true){
            grayBg = grayImage;
            bLearnBakground = false;
        }
        
        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.absDiff(grayPrev, grayImage);
        grayDiff.threshold(threshold);
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayDiffFromColor, 20, (vidWidth * vidHeight)/3, 10, true);	// find holes
        
        grayPrev = grayImage;
        colorPrev = colorImage;
        colorPrevPixels = colorImage.getPixels();
    }
    
}

//--------------------------------------------------------------
void Vision::draw(){
    
    // draw the incoming, the grayscale, the bg and the thresholded difference
    ofSetHexColor(0xffffff);
    
    colorImage.draw(ofGetWidth()/2 - vidRenderWidth/2, 0, vidRenderWidth, vidRenderHeight);
    //colorImg.draw(0, 0, vidRenderWidth, vidRenderHeight);
    
    grayImage.draw(ofGetWidth() - vidWidth, 0);
    grayDiff.draw(ofGetWidth() - vidWidth, vidHeight);
    colorDiff.draw(ofGetWidth() - vidWidth, vidHeight * 2);
    grayDiffFromColor.draw(ofGetWidth() - vidWidth, vidHeight * 3);
    
    // then draw the contours:
    int contourFinderX = ofGetWidth() - vidWidth;
    int contourFinderY = vidHeight * 4;
    
    ofFill();
    ofSetHexColor(0x333333);
    ofDrawRectangle(contourFinderX, contourFinderY, vidWidth, vidHeight);
    ofSetHexColor(0xffffff);
    
    // we could draw the whole contour finder
    //contourFinder.draw(360,540);
    
    // or, instead we can draw each blob individually from the blobs vector,
    // this is how to get access to them:
    for (int i = 0; i < contourFinder.nBlobs; i++){
        //cout << contourFinder.blobs[i].area << endl;
        
        contourFinder.blobs[i].draw(contourFinderX, contourFinderY);
        
        // draw over the centroid if the blob is a hole
        ofSetColor(255);
        if(contourFinder.blobs[i].hole){
            ofDrawBitmapString("hole", contourFinder.blobs[i].boundingRect.getCenter().x + contourFinderX, contourFinder.blobs[i].boundingRect.getCenter().y + contourFinderY);
        }
    }
    
    // finally, a report:
    ofSetHexColor(0xffffff);
    stringstream reportStr;
    reportStr << "bg subtraction and blob detection" << endl
    << "press ' ' to capture bg" << endl
    << "threshold " << threshold << " (press: +/-)" << endl
    << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
    ofDrawBitmapString(reportStr.str(), 20, 600);
    
}

//--------------------------------------------------------------
void Vision::keyPressed(int key){
    
    switch (key){
        case ' ':
            bLearnBakground = true;
            break;
        case '+':
            threshold ++;
            if (threshold > 255) threshold = 255;
            break;
        case '-':
            threshold --;
            if (threshold < 0) threshold = 0;
            break;
    }
}

void Vision::showZones() {
    cout << zonesPtr->allZones.size() << endl;
}

