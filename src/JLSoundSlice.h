//
//  JLSoundSlice.hpp
//  SoundVis
//
//  Created by jlsy012 on 2018. 10. 26..
//

#ifndef JLSoundSlice_hpp
#define JLSoundSlice_hpp

#include <stdio.h>
#include "ofMain.h"
#include "JLSoundAnalyzer.h"



class JLSoundSlice : public JLSoundAnalyzer
{
    
// private property area ////////////////////////////////////////////////////////////////
    
private:
    
    ofVec2f position;
    int width;
    int margin;
    int dataSize;
    float dataInterval;
    int index;
    ofPolyline soundCurve;
    ofTrueTypeFont *indexFont;

// public property area ////////////////////////////////////////////////////////////////

// private method area ////////////////////////////////////////////////////////////////
    
private:
    
    void initDefaultData();

// public method area ////////////////////////////////////////////////////////////////
    
public:
    
    JLSoundSlice();
    ~JLSoundSlice();
    
    void setDefaultData(int setWidth, int setMargin, int setDataSize, int setIndex,ofTrueTypeFont *setIndexFont);
    void setPosition(int x , int y);
    void update();
    void draw();
    
    
};





#endif /* JLSoundSlice_hpp */
