#pragma once

#include "ofMain.h"
#include "ofxPS3EyeGrabber.h"
#include "ofxSyphon.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "camParameterGroup.h"
#include "ofxTextInputField.h"


class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    void onGainChange(const void * guiSender,int & value);
    void onShutterChange(const void * guiSender,int & value);
    void onBrightnessChange(const void * guiSender,int & value);
    void onContrastChange(const void * guiSender,int & value);
    void onHueChange(const void * guiSender,int & value);
    void onLedChange(const void * guiSender,bool & value);
    void onFlickerChange(const void * guiSender,int & value);
    void onWhiteBalanceChange(const void * guiSender,int & value);
    void onSharpnessChanged(const void * guiSender,int & value);
    void onRedBalanceChanged(const void * guiSender,int & value);
    void onBlueBalanceChanged(const void * guiSender,int & value);
    void onGreenBalanceChanged(const void * guiSender,int & value);
    
    void onCamDrawChanged(const void * guiSender,bool & value);
    void onAutoBalanceChanged(const void * guiSender,bool & value);
    void onFlipVertChanged(const void * guiSender,bool & value);
    void onFlipHorizChanged(const void * guiSender,bool & value);
    void onAutoGainAndShutterChange(const void * guiSender,bool & value);
    
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
    
    ofxTextInputField portInputOutgoing;
    ofxTextInputField portInputIncoming;
    
    ofColor drawColour;
    bool setIncomingPort, setOutGoingPort;

    
    
    
    
};
