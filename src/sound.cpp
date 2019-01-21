//
//  sound.m
//  soundvis
//
//  Created by jlsy012 on 2017. 12. 13..
//

#include "sound.h"


//--------- private member method area ----------------//



//--------- public member method area -----------------//

void JLSound::setup(int maxBand)
{
    bands = maxBand;
    
    scale = 100;
    
    smoothingFactor = 0.1;
    
    fftSmooth     = new float[8192];
    prevFftSmooth = new float[8192];
    
    for (int i=0;i<8192;i++)
    {
        fftSmooth[i] = 0;
        
        prevFftSmooth[i] = 0;
    }
    
    length = 320;// this should be automated
    
    mySound.load("2.mp3");
    
    mySound.setLoop(false);
    
    mySound.play();
    mySound.setPosition(1.0f);
    int ms = mySound.getPositionMS();
    mySound.setPosition(0);
    mySound.stop();
    ofLog()<< "sound length = " << ms;
}

void JLSound::play()
{
    mySound.play();
}

void JLSound::stop()
{
    mySound.stop();
}

void JLSound::update()
{
    float *value;
    
    ofSoundUpdate();
    
    value = ofSoundGetSpectrum((int)(bands*2));
    
    for (int i=0;i<bands;i++)
    {
        //fftSmooth[i] = (value[i] * smoothScale);
        
        fftSmooth[i] += ((value[i]*(scale+(i*10))) - fftSmooth[i]) * smoothingFactor;
                
        //ofLog() << fftSmooth[i];
    }
}

int JLSound::getLength()
{
    return length;
}

float * JLSound::getFFT()
{
//    for (int i=0;i<bands;i++)
//    {
//        fftSmooth[i] = (fftSmooth[i]*100 - prevFftSmooth[i]);
//
//        prevFftSmooth[i] = fftSmooth[i];
//    }
    
    return fftSmooth;
}

void JLSound::draw()
{
    ;
}
