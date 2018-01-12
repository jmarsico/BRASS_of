#pragma once

#include "ofMain.h"
#include "ofxPtf.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxTubePrimitive.h"

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
    
    
    ofxPtf ptf;
    ofPolyline pl;
    ofVboMesh mesh;
    
    ofxOscReceiver osc;
    
    
    ofxPanel gui;
    ofParameter<int> maxNumSegments;
    ofParameter<int> smoothness;
    ofParameter<float> volumeThresh;
    ofParameter<float> fov;
    ofParameter<float> speed;
    ofParameter<float> camZ;
    
    ofVec3f currentPos;
    float freq;
    float vol;
    
    
    ofEasyCam cam;
    
    ofxTubePrimitive tube;
    
    
    
		
};
