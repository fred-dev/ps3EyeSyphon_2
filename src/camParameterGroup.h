//
//  camParameterGroup.h
//  CaseyPs3Eye2
//
//  Created by Fred Rodrigues on 03/07/15.
//
//
#ifndef CAMPARAMETERGROUP_H_
#define CAMPARAMETERGROUP_H_


#include "ofParameterGroup.h"
#include "ofParameter.h"
#include "ofMain.h"



class camParameterGroup {
public:
    camParameterGroup();
    
    void setup(int camId);
    ofParameterGroup parameters;
    ofParameter<bool>  drawcam;
    ofParameter<bool>  camAutoGain;
    ofParameter<bool>  camAutoBalance;
    ofParameter<bool>  camflipHoriz;
    ofParameter<bool>  camflipVert;
    
    ofParameter<int> camExposure;
    ofParameter<int>  camGain;
    ofParameter<int>  camSharpness;
    ofParameter<int>  camBrightness;
    ofParameter<int>  camContrast;
    ofParameter<int>  camRedBalance;
    ofParameter<int>  camBlueBalance;
    ofParameter<int>  camGreenBalance;
    ofParameter<int>  camHue;
    

    
};

#endif