//
//  JLSoundAnalyzer.hpp
//  SoundVis2
//
//  Created by jlsy on 18/11/2018.
//

#ifndef JLSoundAnalyzer_hpp
#define JLSoundAnalyzer_hpp

#include <stdio.h>
#include "ofMain.h"


// private property area ////////////////////////////////////////////////////////////////

// public property area ////////////////////////////////////////////////////////////////

// private method area ////////////////////////////////////////////////////////////////

// public method area ////////////////////////////////////////////////////////////////


// event method area ////////////////////////////////////////////////////////////////

class JLSoundAnalyzer
{
    // private property area ////////////////////////////////////////////////////////////////
    
private:
    
    float *soundFFT;
    ofVec2f position;
    
    // public property area ////////////////////////////////////////////////////////////////
    
    // private method area ////////////////////////////////////////////////////////////////
    
    // public method area ////////////////////////////////////////////////////////////////
    
public:
    
    JLSoundAnalyzer();
    ~JLSoundAnalyzer();
    
    float *getSoundFFT();
    void setSoundFFT(float *fft);
    
    virtual void setDefaultData();
    virtual void setPosition(int x , int y);
    virtual void update();
    virtual void draw();
    virtual void stop();

};

#endif /* JLSoundAnalyzer_hpp */
