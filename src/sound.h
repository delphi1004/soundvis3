//
//  sound.h
//  soundvis
//
//  Created by jlsy012 on 2017. 12. 13..
//

#pragma once

#include "ofMain.h"

class JLSound
{
    
    //--------- private member property area---------------//
    
private:
    
    
    ofSoundPlayer mySound;
    
    float *fftSmooth;
    float *prevFftSmooth;
    float scale;
    float smoothingFactor;
    int bands;
    int length; // in secondd
    
    //--------- public member property area ---------------//
    
    
    
    //--------- private member method area ----------------//
    
    
    
    //--------- public member method area -----------------//
    
public:
    
    void setup(int maxBand);
    void play();
    void stop();
    void update();
    void draw();
    int getLength();
    
    float *getFFT();
    
};
