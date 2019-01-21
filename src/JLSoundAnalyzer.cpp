//
//  JLSoundAnalyzer.cpp
//  SoundVis2
//
//  Created by jlsy on 18/11/2018.
//

#include "JLSoundAnalyzer.h"


// private property area ////////////////////////////////////////////////////////////////

// public property area ////////////////////////////////////////////////////////////////

// private method area ////////////////////////////////////////////////////////////////

// public method area ////////////////////////////////////////////////////////////////

JLSoundAnalyzer::JLSoundAnalyzer()
{
    ;
}

JLSoundAnalyzer::~JLSoundAnalyzer()
{
    
    ;
    
}

void JLSoundAnalyzer::setDefaultData()
{
    ;
}

void JLSoundAnalyzer::setSoundFFT(float *fft)
{
    soundFFT = fft;
}

float *JLSoundAnalyzer::getSoundFFT()
{
    return soundFFT;
}

void JLSoundAnalyzer::setPosition(int x , int y)
{
    position.set(x,y);
}

void JLSoundAnalyzer::stop()
{
    ;
}

void JLSoundAnalyzer::update()
{
    ;
}

void JLSoundAnalyzer::draw()
{
    ;
}


// event method area ////////////////////////////////////////////////////////////////
