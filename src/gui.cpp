//
//  gui.cpp
//  GrabDetector
//
//  Created by Ahmad Saeed on 1/29/16.
//
//

#include "gui.h"

void Gui::setup()
{
    datgui = new ofxDatGui(100, 100);
    datgui->addHeader(":: Drag ::");
    datgui->addFooter();
    datgui->addSlider("slider", 0.0f, 100.0f, 50.0f);

    //sliderFloat->onSliderEvent(this, &Gui::onSliderEvent);
    //ofParamFloat.addListener(this, &Gui::onParamFloatChanged);
    
}

void Gui::onParamIntChanged(int & n)
{
    cout << "onParamIntChanged "<< n << endl;
}

void Gui::onParamFloatChanged(float & f)
{
    cout << "onParamFloatChanged "<< f << endl;
}

void Gui::onSliderEvent(ofxDatGuiSliderEvent e)
{
    if(e.target == slider){
        ofSetBackgroundColor(ofColor::white*e.scale);
        cout << "value = " << e.value << " : scale = " << e.scale << endl;
    }   else if (e.target == sliderInt){
        //  uncomment this to print the change event received from the int slider //
        //  cout << "value = " << e.value << " : scale = " << e.scale << endl;
    }   else if (e.target == sliderFloat){
        //  uncomment this to print the change event received from the float slider //
        //  cout << "value = " << e.value << " : scale = " << e.scale << endl;
    }
}

void Gui::update()
{
    datgui->update();
}

void Gui::draw()
{
    datgui->draw();
}

bool Gui::mousePressed(int x, int y, int button) {
    if (ofRectangle(datgui->getPosition(), datgui->getWidth(), datgui->getHeight()).inside(x, y)) {
        return true;
    } else {
        return false;
    }
}