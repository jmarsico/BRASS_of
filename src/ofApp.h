#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxSyphon.h"
#include "voiceTube.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
    void cull();
    void addPoint(ofVec3f _vec);
    
    void receiveOsc();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    

    
    ofxOscReceiver osc;
    
    vector<VoiceTube> tubes;
    
    ofxPanel gui;

    ofParameter<float> camZ;
    ofParameter<float> camY;
    
    
    ofxPanel tubeParams;
    
    float freq;
    float vol;
    
    
    ofEasyCam cam;
    
    
    ofxSyphonServer syphon;
    
    
		
};
