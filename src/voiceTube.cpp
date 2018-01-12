//
//  voiceTube.cpp
//  BRASS_of
//
//  Created by Jakob Marsico on 1/12/18.
//
//

#include "voiceTube.h"

//---------------------------------------------------------
void VoiceTube::init(int _id){
    // make ellipse to draw along the length of the ptf
    mesh.setMode(OF_PRIMITIVE_POINTS);
    unsigned numVerts = 40;
    float w = 20;
    float h = 40;
    for (unsigned i = 0; i < numVerts; ++i)
    {
        mesh.addVertex(ofVec3f(0.0f, w * cos(TWO_PI * i / (float)numVerts), h * sin(TWO_PI * i / (float)numVerts)));
    }
    
    currentPos.set(0,0,0);
    tube.init();

    ID = _id;
    
    params.setName(ofToString(ID));
    params.add(maxNumSegments.set("max points", 100, 50, 3000));
    params.add(smoothness.set("smooth", 1, 0, 30));
    params.add(volumeThresh.set("volume thresh", 0.0, 0.0, 0.3));
    params.add(speed.set("speed", 30, 1.0, 100));
    params.add(drawMode.set("draw mode", 1, 1, 5));


}

//---------------------------------------------------------
void VoiceTube::update(){
    
    
    if(vol > volumeThresh) {
        currentPos.y = ofMap(freq, 0, 1000, ofGetHeight(), 0);
        currentPos.x += vol * speed;
        currentPos.z = ofNoise(ofGetElapsedTimeMillis() * 0.01) * 5.0;
    } else {
        currentPos.y = ofGetHeight();
    }
    
    
    pl.addVertex(currentPos);
    ofPolyline p = pl.getSmoothed(smoothness);
    tube.setup(p, 20);
    tube.update();

    
    cull();
    
}

//---------------------------------------------------------
void VoiceTube::draw(){
    ofSetColor(200, 10, 30);
    pl.getSmoothed(smoothness).draw();
    
    ofSetColor(255, 100);
    
    switch (drawMode){
        case 1: tube.draw();
        case 2: tube.drawNormals(15);
        case 3: tube.drawTubeRings();
        case 4: tube.drawTubeSkeleton();
        case 5: tube.drawTubeTangents();
    }

}


//---------------------------------------------------------
void VoiceTube::cull(){
    
    if(pl.getVertices().size() > maxNumSegments){
        int diff = pl.getVertices().size() - maxNumSegments;
        pl.getVertices().erase(pl.getVertices().begin(), pl.getVertices().begin() + diff);
    }
}
