//
//  camParameterGroup.cpp
//  CaseyPs3Eye2
//
//  Created by Fred Rodrigues on 03/07/15.
//
//



#include "camParameterGroup.h"

camParameterGroup::camParameterGroup() {
    // TODO Auto-generated constructor stub
    
}


void camParameterGroup::setup(int camId){
    parameters.setName("cam " + ofToString(camId +1));
    parameters.add(drawcam.set("Draw Cam " + ofToString(camId+1), true));
    parameters.add(camAutoGain.set("Auto gain Cam " + ofToString(camId+1), true));
    parameters.add(camAutoBalance.set("Auto Balance Cam " + ofToString(camId+1), true));
    parameters.add(camflipHoriz.set("Flip Horizontal Cam " + ofToString(camId+1), false));
    parameters.add(camflipVert.set("Flip Vert Cam " + ofToString(camId+1), false));
    parameters.add(camExposure.set("Exposure Cam " + ofToString(camId+1), 120,0,255));
    parameters.add(camGain.set("Gain Cam " + ofToString(camId+1), 20,0,63));
    parameters.add(camBrightness.set("Brightness Cam " + ofToString(camId+1), 20,0,255));
    parameters.add(camSharpness.set("Sharpness Cam " + ofToString(camId+1), 255,0,255));
    parameters.add(camContrast.set("Contrast Cam " + ofToString(camId+1), 37,0,255));
    parameters.add(camRedBalance.set("Red Balance Cam " + ofToString(camId+1), 128,0,255));
    parameters.add(camBlueBalance.set("Blue Balance Cam " + ofToString(camId+1), 128,0,255));
    parameters.add(camHue.set("Hue Cam " + ofToString(camId+1), 143,0,255));
    
}

