#pragma once

#include "ofMain.h"
#include "sound.h"
#include "JLSoundSlice.h"
#include "JLSoundWriter.h"

#define MODE_SLICE 0
#define MODE_WRITING 1

// private property area ////////////////////////////////////////////////////////////////

// public property area ////////////////////////////////////////////////////////////////

// private method area ////////////////////////////////////////////////////////////////

// public method area ////////////////////////////////////////////////////////////////


// event method area ////////////////////////////////////////////////////////////////






// Member method area ///////////////////////////////////////////////////////////


class ofApp : public ofBaseApp
{
    
    // private property area ////////////////////////////////////////////////////////////////
    
private:
    
    JLSoundSlice testSlice[3][157];
    JLSoundSlice *displaySlice;
    JLSoundWriter *soundWriter;
    JLSound mySound;
    ofPolyline soundCurve;
    ofTrueTypeFont indexFont;
    
    int scrWidth, scrHeight;
    int maxBand;
    int expWidth;
    int expHeight;
    int sliceWidth;
    int shapeWidth;
    int expRow;
    int index;
    int curPage;
    int totalPageCount;
    int totalSliceCount;
    int curSliceIndex;
    int curMode; //
    float *soundFFT;
    bool capture;
    bool refresh;
    
    ofImage testImage;
    
    
    // public property area ////////////////////////////////////////////////////////////////
    
    
    
    // private method area ////////////////////////////////////////////////////////////////
    
    void initDefaultData();
    void initSoundSlice();
    void initSoundWriter();
    void saveIt();
    void updateSlice();
    void updateWriting();
    void drawSlice();
    void drawWriting();
    
    
    // public method area ////////////////////////////////////////////////////////////////


	public:
    
		void setup();
		void update();
		void draw();

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
		
};
