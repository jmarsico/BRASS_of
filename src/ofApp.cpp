#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    osc.setup(5000);
    
    
    
    // this sets the camera's distance from the object
//    cam.setDistance(100);
    
    light.setDirectional();
    ofEnableLighting();
    
    //set up our voice tubes
    int numVoices = 2;
    for(int i = 0; i < numVoices; i++){
        VoiceTube vt;
        vt.init(i);
        tubes.push_back(vt);
    }

    gui.setup();
//    gui.add(maxNumSegments.set("max segs", 10, 10, 2000));
//    gui.add(smoothness.set("smoothness", 0, 0, 20));
//    gui.add(volumeThresh.set("volume thresh", 0.0, 0.0, 0.2));
//    gui.add(speed.set("speed", 1, 0.01, 100.0));
    gui.add(camZ.set("cam Z", 100, -1000, 1000));
    gui.add(camY.set("cam Y", ofGetHeight()/2, -100, ofGetHeight() +100));
    gui.add(camX.set("cam X", 0, -500, 500));
    gui.add(diffuse.set("diffuse", 1.0, 0.0, 1.0));
    gui.add(ambient.set("ambient", 0.0, 0.0, 1.0));
    gui.add(atten.set("atten", 0.0, 0.0, 1.0));
    
    gui.loadFromFile("settings.xml");
    
    
    tubeParams.setup("tube", "tubeSettings.xml");
    for(auto& vt : tubes){
        tubeParams.add(vt.params);
    }
    tubeParams.loadFromFile("tubeSettings.xml");
    tubeParams.setPosition(gui.getWidth() + 20, 10);
    
    syphon.setName("brass");
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //receive osc and update params of each voicetube
    receiveOsc();
    
    
    //we need an average x location;
    //update all of the voice tubes
    int avgX = 0;
    for(auto& vt : tubes){
        vt.update();
        avgX += vt.currentPos.x;
    }
    
    //get average x loc
    avgX = avgX/tubes.size();
    
   
    light.setPosition(ofVec3f(avgX, -10, 0));
    light.lookAt(ofVec3f(avgX, ofGetHeight()/2, 0));
    light.setDiffuseColor(ofFloatColor(diffuse));
    light.setAmbientColor(ofFloatColor(ambient));
    light.setAttenuation(atten);
    //update camera position
    cam.setPosition(ofVec3f(avgX + camX, camY, camZ));
    cam.lookAt(ofVec3f(avgX, ofGetHeight()/2 + 200, 0));

    
}



//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofEnableDepthTest();
    ofEnableLighting();
    
    ofSetColor(255);
    
    cam.begin();
    ofScale(1, -1, 1);
    ofTranslate(0, -1500,0);
   
    light.enable();
    
    for(auto& vt : tubes){
        vt.draw();
    }
    
    cam.end();
    
    syphon.publishScreen();

    ofDisableDepthTest();
    ofDisableLighting();
    gui.draw();
    tubeParams.draw();
}

//--------------------------------------------------------------
void ofApp::receiveOsc(){
    
    while(osc.hasWaitingMessages()){
        ofxOscMessage m;
        
        if(osc.getNextMessage(m)){
            
            //  /voice ID freq vol
            if(m.getAddress() == "/voice"){
                int ID = m.getArgAsInt(0);
                freq = m.getArgAsFloat(1);
                vol = m.getArgAsFloat(2);
                
                //if the ID is within range
                if(ID < tubes.size()){
                    tubes[ID].freq = freq;
                    tubes[ID].vol = vol;
                }
                

            }
        }
    }
 
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
