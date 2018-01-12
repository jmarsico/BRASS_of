//
//  voiceTube.hpp
//  BRASS_of
//
//  Created by Jakob Marsico on 1/12/18.
//
//

#ifndef voiceTube_hpp
#define voiceTube_hpp

#include <stdio.h>
#include "ofxTubePrimitive.h"
#include "ofMain.h"


class VoiceTube {
public:
    
    VoiceTube(){};
    void init(int _id);
    void update();
    void draw();
    
    
    
    void cull();
    
    
    
    

    
    ofParameterGroup params;
    ofParameter<int> maxNumSegments;
    ofParameter<int> smoothness;
    ofParameter<float> volumeThresh;
    ofParameter<float> speed;
    ofParameter<int> drawMode;
    
    
    ofVec3f currentPos;
    float freq;
    float vol;
    
    ofPolyline pl;
    ofVboMesh mesh;
    ofxTubePrimitive tube;
    int ID;



};

#endif /* voiceTube_hpp */
