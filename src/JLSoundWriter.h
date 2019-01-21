//
//  JLSoundWriter.hpp
//  SoundVis2
//
//  Created by jlsy on 18/11/2018.
//

#ifndef JLSoundWriter_hpp
#define JLSoundWriter_hpp

#include <stdio.h>
#include "JLSoundAnalyzer.h"

// private property area ////////////////////////////////////////////////////////////////

// public property area ////////////////////////////////////////////////////////////////

// private method area ////////////////////////////////////////////////////////////////

// public method area ////////////////////////////////////////////////////////////////


// event method area ////////////////////////////////////////////////////////////////


class JLSoundWriter : public JLSoundAnalyzer
{
    
    // private property area ////////////////////////////////////////////////////////////////
    
private:
    
    ofImage terrain;
    ofFile file;
    int dataSize;
    int zOrder;
    int curRow;
    int totalRowCount;
    float frameRate;
    
    // public property area ////////////////////////////////////////////////////////////////
    
    // private method area ////////////////////////////////////////////////////////////////
    
private:
    
    void initDefaultData();
    
    // public method area ////////////////////////////////////////////////////////////////
    
public:
    
    JLSoundWriter();
    ~JLSoundWriter();

    void setDefaultData(int setDataSize);
    void stop();
    void update();
    void draw();
    
};


#endif /* JLSoundWriter_hpp */