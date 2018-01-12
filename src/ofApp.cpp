#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    osc.setup(5000);
    
    // make ellipse to draw along the length of the ptf
    mesh.setMode(OF_PRIMITIVE_POINTS);
    unsigned numVerts = 40;
    float w = 20;
    float h = 40;
    for (unsigned i = 0; i < numVerts; ++i)
    {
        mesh.addVertex(ofVec3f(0.0f, w * cos(TWO_PI * i / (float)numVerts), h * sin(TWO_PI * i / (float)numVerts)));
    }
    
    
    // this sets the camera's distance from the object
    cam.setDistance(100);
//    cam.setPosition(ofVec3f(0,0,100));
//    cam.lookAt(ofVec3f(0,0,0));
//    cam.setFov(fov);


    gui.setup();
    gui.add(maxNumSegments.set("max segs", 10, 10, 2000));
    gui.add(smoothness.set("smoothness", 0, 0, 20));
    gui.add(volumeThresh.set("volume thresh", 0.0, 0.0, 0.2));
    gui.add(fov.set("fov", 10, 10, 100));
    gui.add(speed.set("speed", 1, 0.01, 100.0));
    gui.add(camZ.set("cam Z", 100, -1000, 1000));
    gui.loadFromFile("settings.xml");
    
    currentPos.set(0,0,0);
    
    tube.init();
}

//--------------------------------------------------------------
void ofApp::update(){
    receiveOsc();
//    cam.setFov(fov);
////    cam.lookAt(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0));
//    
//    cam.setPosition(currentPos.x, 200, 2000);
//    cam.lookAt(ofVec3f(currentPos.x, 200, 0));


    
    if(vol > volumeThresh) {
        currentPos.y = ofMap(freq, 0, 1000, ofGetHeight(), 0);
        currentPos.x += vol*speed;
        currentPos.z = ofNoise(ofGetElapsedTimeMillis() * 0.01) * 1.0;
    } else {
        currentPos.y = ofGetHeight();
    }
    
    
    pl.addVertex(currentPos);
    ptf.addPoint(currentPos);
    
        cam.setPosition(currentPos.x, 200, camZ);
        cam.lookAt(ofVec3f(currentPos.x, ofGetHeight()/2, 0));
    
    cull();
    
    ofPolyline p = pl.getSmoothed(smoothness);
    tube.setup(p, 20);
    tube.update();
    
}

//--------------------------------------------------------------
void ofApp::addPoint(ofVec3f _vec){
    pl.addVertex(_vec);
    ptf.addPoint(_vec);
    
    cull();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofEnableDepthTest();
    
    ofSetColor(255);
    
    cam.begin();
    ofScale(1, -1, 1);
    
//    ofPushMatrix();
    ofTranslate(0, -1000,0);
    ofSetColor(200, 10, 30);
    pl.getSmoothed(smoothness).draw();
    
    ofSetColor(255, 100);
//    tube.draw();
//    tube.drawNormals(15);
    tube.drawTubeRings();
    
//    ofSetColor(255);
//    for (int i = 0; i < ptf.framesSize(); ++i)
//    {
//        ofPushMatrix();
//        
//        // multiply current matrix (rotated around x axis)
//        // by transform for next frame
//        ofMultMatrix(ptf.frameAt(i));
//        
//        // draw ellipse
//        mesh.draw();
//        ofPopMatrix();
//    }
    
//    ofPopMatrix();
    
    cam.end();

    ofDisableDepthTest();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::receiveOsc(){
    
    while(osc.hasWaitingMessages()){
        ofxOscMessage m;
        
        if(osc.getNextMessage(m)){
            if(m.getAddress() == "/voice"){
                int ID = m.getArgAsInt(0);
                
                
                freq = m.getArgAsFloat(1);
                vol = m.getArgAsFloat(2);
                
//                currentPos.y = ofMap(freq, 0.0, 2,000, ofGetHeight(), 100.0);
                ofLog() << "ID: " << ID << " freq: " << freq;

//                currentPos.y = ofMap(volume, 0.0, 0.8, ofGetHeight(),100.0);
                
                
//                if(volume > volumeThresh){
//                    ptf.addPoint(ofVec3f(freq, y, z));
//                    pl.addVertex(ofVec3f(freq, y, z));
//                    cull();
//                }
            }
        }
    }
 
}

//---------------------------------------------------------
void ofApp::cull(){
    if(ptf.getFrames().size() > maxNumSegments){
        
        
        int diff = ptf.getFrames().size() - maxNumSegments;
        
        ofLog() << "ptf size: " << ptf.getFrames().size() << " culling " << diff << " frames.";
        
        pl.getVertices().erase(pl.getVertices().begin(), pl.getVertices().begin() + diff);
        
        
        for(int i = 0; i < diff; i++){
            ptf.getFrames().pop_front();
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
