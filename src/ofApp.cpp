#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    minimised=false;
    ofSetVerticalSync(false);
    
    XML.loadFile("settings.xml");
    camWidth		= XML.getValue("CAMWIDTH", 1920);
    camHeight	= XML.getValue("CAMHEIGHT", 1080);
    frameRate	= XML.getValue("FRAMERATE", 60);
    recievePort	= XML.getValue("RECIEVEPORT", 1234);
    sendPort =XML.getValue("SENDPORT", 1235);
    sendIp = XML.getValue("SENDIP", "127.0.0.1");
    
    receiver.setup(recievePort);
    sender.setup(sendIp, sendPort);
    
    
//    QVGA - 15, 30, 60, 75, 100, 125, 200
//    VGA - 15, 30, 40, 50, 60, 75
    
    vector<ofVideoDevice> deviceList = ofxPS3EyeGrabber().listDevices();
    for (int i = 0; i < deviceList.size(); i++) {
        camParameterGroup params;
        params.setup(i);
        camParams.push_back(params);
        parameters.add(camParams[i].parameters);
    }
    
    parameters.setName("settings");
    
    for (int i = 0; i < deviceList.size(); i++) {
        
        ofxSyphonServer * server = new ofxSyphonServer();
        std::shared_ptr<ofxPS3EyeGrabber> camera = std::shared_ptr<ofxPS3EyeGrabber>(new ofxPS3EyeGrabber());
        ofTexture * texture = new ofTexture();
        
        camera->setDeviceID(i);
        camera->setDesiredFrameRate(frameRate);
        camera->setup(camWidth, camHeight);
        camera->setAutogain(true);
        camera->setAutoWhiteBalance(true);
        cameras.push_back(camera);
        
        server->setName("Camera " +ofToString(i+1)+" Output");
        servers.push_back(server);
        
        texture->allocate(camWidth, camHeight, GL_RGBA);
        if (texture->isAllocated()) {
            textures.push_back(texture);
        }
        
        
        cameras[i]->setBrightness(uint8_t(camParams[i].camBrightness));
        cameras[i]->setContrast(uint8_t(camParams[i].camContrast));
        if (!camParams[i].camAutoGain) {
            cameras[i]->setGain(uint8_t(camParams[i].camGain));
            cameras[i]->setSharpness(uint8_t(255-camParams[i].camSharpness));
            cameras[i]->setExposure(uint8_t(camParams[i].camExposure));
        }
        
        if (!camParams[i].camAutoBalance) {
            cameras[i]->setRedBalance(uint8_t(camParams[i].camRedBalance));
            cameras[i]->setBlueBalance(uint8_t(camParams[i].camBlueBalance));
            cameras[i]->setHue(uint8_t(camParams[i].camHue));
        }
        
        cameras[i]->setAutogain(camParams[i].camAutoGain);
        cameras[i]->setAutoWhiteBalance(camParams[i].camAutoBalance);
        cameras[i]->setFlip(camParams[i].camflipHoriz, camParams[i].camflipVert);
        
    }
    
    camCounter=deviceList.size();
    
    
}


void ofApp::update(){
    
    if (ofGetElapsedTimeMillis()>300000) {
        ofSystemAlertDialog("Evaluation time is up");
    }
    
    if (ofGetElapsedTimeMillis()>302000) {
        ofExit();
    }
    
    if (camCounter>0) {
        for (int i = 0; i < cameras.size(); i++) {
            cameras[i]->setBrightness(uint8_t(camParams[i].camBrightness));
            cameras[i]->setContrast(uint8_t(camParams[i].camContrast));
            cameras[i]->setSharpness(uint8_t(255-camParams[i].camSharpness));
            cameras[i]->setRedBalance(uint8_t(camParams[i].camRedBalance));
            cameras[i]->setBlueBalance(uint8_t(camParams[i].camBlueBalance));
            
            if (!camParams[i].camAutoGain) {
                cameras[i]->setGain(uint8_t(camParams[i].camGain));
                cameras[i]->setExposure(uint8_t(camParams[i].camExposure));
            }
            
            if (!camParams[i].camAutoBalance) {
                cameras[i]->setHue(uint8_t(camParams[i].camHue));
            }
            
            cameras[i]->setAutogain(camParams[i].camAutoGain);
            cameras[i]->setAutoWhiteBalance(camParams[i].camAutoBalance);
            cameras[i]->setFlip(camParams[i].camflipHoriz, camParams[i].camflipVert);
            cameras[i]->update();
            
            if (cameras[i]->isFrameNew()){
                textures[i]->loadData(cameras[i]->getPixels());
                servers[i]->publishTexture(textures[i]);
            }
        }
    
    }
    
    if (camCounter>0) {
        
        while(receiver.hasWaitingMessages()){
            ofxOscMessage m;
            receiver.getNextMessage(&m);
            
            for (int i = 0; i < camCounter; i++) {
                
                if ( m.getAddress() == "/minimise" ){
                    minimised=m.getArgAsInt32(0);
                }
                
                if ( m.getAddress() == "/saveSettings" ){
                    gui.saveToFile("settings.xml");
                }
                
                if ( m.getAddress() == "/recallSaved" ){
                    gui.loadFromFile("settings.xml");
                }
                
                if ( m.getAddress() == "/"+ofToString(i+1)+"/gain" ){
                    camParams[i].camGain =m.getArgAsInt32( 0 );
                }
                
                if ( m.getAddress() == "/"+ofToString(i+1)+"/gain" ){
                    camParams[i].camGain =m.getArgAsInt32( 0 );
                }
                
                if ( m.getAddress() == "/"+ofToString(i+1)+"/draw" ){
                    camParams[i].drawcam =m.getArgAsInt32( 0 );
                }
                
                if ( m.getAddress() == "/"+ofToString(i+1)+"/exposure" ){
                    camParams[i].camExposure = m.getArgAsInt32( 0 );
                }
                
                if ( m.getAddress() == "/"+ofToString(i)+"/sharpness" ){
                    camParams[i].camSharpness = m.getArgAsInt32( 0 );
                }
                
                if ( m.getAddress() == "/"+ofToString(i)+"/brightness" ){
                    camParams[i].camBrightness = m.getArgAsInt32( 0 );
                }
                
                if ( m.getAddress() == "/"+ofToString(i+1)+"/contrast" ){
                    camParams[i].camContrast = m.getArgAsInt32( 0 );
                }
                
                if ( m.getAddress() == "/"+ofToString(i+1)+"/hue" ){
                    camParams[i].camHue = m.getArgAsInt32( 0 );
                }
                
                if ( m.getAddress() == "/"+ofToString(i+1)+"/blueBalance" ){
                    camParams[i].camBlueBalance = m.getArgAsInt32( 0 );
                }
                
                if ( m.getAddress() == "/"+ofToString(i+1)+"/redBalance" ){
                    camParams[i].camRedBalance = m.getArgAsInt32( 0 );
                }
                
                if ( m.getAddress() == "/"+ofToString(i+1)+"/autoGain" ){
                    camParams[i].camAutoGain = m.getArgAsInt32( 0 );
                }
                
                if ( m.getAddress() == "/"+ofToString(i+1)+"/autoWhiteBalance" ){
                    camParams[i].camAutoBalance = m.getArgAsInt32( 0 );
                }
                
                if ( m.getAddress() == "/"+ofToString(i+1)+"/flip" ){
                    camParams[i].camflipVert = m.getArgAsInt32( 0 );
                    camParams[i].camflipHoriz = m.getArgAsInt32(1);
                }
            }
        }
    }
    
    if (camCounter>0) {
        for (int i =0; i<camCounter; i++) {
            
            ofxOscMessage drawMessage;
            drawMessage.setAddress("/"+ofToString(i+1)+"/gain" );
            drawMessage.addIntArg(camParams[i].drawcam);
            sender.sendMessage(drawMessage);
            
            ofxOscMessage gainMessage;
            gainMessage.setAddress("/"+ofToString(i+1)+"/gain" );
            gainMessage.addIntArg(cameras[i]->getGain());
            sender.sendMessage(gainMessage);
            
            ofxOscMessage exposureMessage;
            exposureMessage.setAddress("/"+ofToString(i+1)+"/exposure" );
            exposureMessage.addIntArg(cameras[i]->getExposure());
            sender.sendMessage(exposureMessage);
            
            ofxOscMessage sharpnessMessage;
            sharpnessMessage.setAddress("/"+ofToString(i+1)+"/sharpness" );
            sharpnessMessage.addIntArg(255-cameras[i]->getSharpness());
            sender.sendMessage(sharpnessMessage);
            
            ofxOscMessage brightnessMessage;
            brightnessMessage.setAddress("/"+ofToString(i+1)+"/brightness" );
            brightnessMessage.addIntArg(cameras[i]->getBrightness());
            sender.sendMessage(brightnessMessage);
            
            ofxOscMessage contrastMessage;
            contrastMessage.setAddress("/"+ofToString(i+1)+"/contrast" );
            contrastMessage.addIntArg(cameras[i]->getContrast());
            sender.sendMessage(contrastMessage);
            
            ofxOscMessage hueMessage;
            hueMessage.setAddress("/"+ofToString(i+1)+"/hue" );
            hueMessage.addIntArg(cameras[i]->getHue());
            sender.sendMessage(hueMessage);
            
            ofxOscMessage blueBalanceMessage;
            blueBalanceMessage.setAddress("/"+ofToString(i+1)+"/blueBalance" );
            blueBalanceMessage.addIntArg(cameras[i]->getBlueBalance());
            sender.sendMessage(blueBalanceMessage);
            
            ofxOscMessage redBalanceMessage;
            redBalanceMessage.setAddress("/"+ofToString(i+1)+"/redBalance" );
            redBalanceMessage.addIntArg(cameras[i]->getRedBalance());
            sender.sendMessage(redBalanceMessage);
            
            ofxOscMessage autoGainMessage;
            autoGainMessage.setAddress("/"+ofToString(i+1)+"/autoGain" );
            autoGainMessage.addIntArg(cameras[i]->getAutogain());
            sender.sendMessage(autoGainMessage);
            
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (minimised) {
        ofPushStyle();
        ofSetColor(255, 255, 255);
        if(cameras.size() == 0){
            ofDrawBitmapString("No PS3Eye found. :(", 10, 10);
        }
        if(cameras.size() != 0){
            ofDrawBitmapString(ofToString(cameras.size()) + " Cameras connected", 10, 10);
        }
        ofPopStyle();
    }
    if (!minimised) {
        ofBackground(0, 0, 0);
        ofPushStyle();
        ofSetColor(255, 255, 255);
        if(cameras.size() == 0){
            ofDrawBitmapString("No PS3Eye found. :(", 20, 50);
        }
        ofPopStyle();
        
        if (camCounter>0) {
            for (int i = 0; i < cameras.size(); i++) {
                if (camParams[i].drawcam==true) {
                    
                    textures[i]->draw(gui.getWidth()+80+i * cameras[i]->getWidth(),0);
                    ofDrawBitmapString("FPS="+ofToString(cameras[i]->getFPS()) + " Dimension=" + ofToString(cameras[i]->getWidth())  +" * "+ ofToString(cameras[i]->getHeight()), gui.getWidth()+80+ i * cameras[i]->getWidth() + 20, 20);
                }
            }
        }
        if( !bHide ){
            gui.draw();
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'g' ){
        bHide = !bHide;
    }
    
    if (key=='m') {
        minimised=!minimised;
        if (minimised) {
            ofSetWindowShape(300, 30);
        }
        if (!minimised) {
            if (cameras.size()*camHeight<gui.getShape().height+80) {
                ofSetWindowShape(gui.getWidth()+80+camWidth * cameras.size(), gui.getShape().height+80);
            }
            if (cameras.size()*camHeight>gui.getShape().height+80) {
                ofSetWindowShape(gui.getWidth()+80+camWidth * cameras.size(), cameras.size()*camHeight);
            }
        }
    }
    
    if (key=='s') {
        gui.saveToFile("settings.xml");
    }
    
    if (key=='r') {
        gui.loadFromFile("settings.xml");
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}