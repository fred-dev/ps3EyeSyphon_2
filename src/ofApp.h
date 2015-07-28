#pragma once

#include "ofMain.h"
#include "ofxPS3EyeGrabber.h"
#include "ofxSyphon.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "camParameterGroup.h"


class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void onAutoGainAndShutterChange(bool & value);
    void onGainChange(float & value);
    void onShutterChange(float & value);
    void onGammaChange(float & value);
    void onBrightnessChange(float & value);
    void onContrastChange(float & value);
    void onHueChange(float & value);
    void onLedChange(bool & value);
    void onFlickerChange(int & value);
    void onWhiteBalanceChange(int & value);
    
    bool bHide;
    
    int camWidth;
    int camHeight;
    int frameRate;
    int camCounter;
    ofxXmlSettings XML;
    bool minimised;
    bool autoGain, autoBalance;
    
    std::vector<std::shared_ptr<ofxPS3EyeGrabber> > cameras;
    
    vector<ofxSyphonServer*> servers;
    vector<ofTexture*> textures;
    vector<camParameterGroup> camParams;
    
    ofParameterGroup parameters;
    ofxPanel gui;

    int recievePort;
    
    ofxOscReceiver receiver;
    ofxOscSender sender;
    string sendIp;
    int sendPort;
    
    
};
