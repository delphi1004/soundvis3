//
//  JLSoundSlice.cpp
//  SoundVis
//
//  Created by jlsy012 on 2018. 10. 26..
//

#include "JLSoundSlice.h"



// private method area ////////////////////////////////////////////////////////////////

void JLSoundSlice::initDefaultData()
{
    int tempWidth;
    
    tempWidth = (width - (margin*2));
    
    dataInterval = (tempWidth / (float)dataSize);
    
    if (dataInterval < 1)
    {
        ofLog() << "the width is too small because data size is " << dataSize << " and drawing width is " << tempWidth;
        
        assert(dataInterval < 1);
    }
}


// public method area ////////////////////////////////////////////////////////////////



JLSoundSlice::JLSoundSlice()
{
    
    dataSize = 0;
    
}

JLSoundSlice::~JLSoundSlice()
{
    
    ;
    
}

void JLSoundSlice::setDefaultData(int setWidth, int setMargin, int setDataSize,int setIndex,ofTrueTypeFont *setIndexFont)
{
    width    = setWidth;
    margin   = setMargin;
    dataSize = setDataSize;
    index    = setIndex;
    indexFont = setIndexFont;
    
    initDefaultData();
}

void JLSoundSlice::setPosition(int x , int y)
{
    position.set(x,y);
}

void JLSoundSlice::update()
{
    int index;
    float height;
    
    index = 0;
    
    soundCurve.clear();
    
    soundCurve.begin();

    soundCurve.lineTo(position.x , position.y);
    soundCurve.lineTo(position.x , position.y);
    
    soundCurve.lineTo(position.x+margin, position.y);

    for (int i=0;i<dataSize;i++)
    {
        height = (getSoundFFT()[i]/2);
        
        if (height > 60)
        {
            height *= 0.5;
        }
        
        soundCurve.lineTo(position.x+(i*dataInterval+margin) , position.y - height);
        
        //soundCurve.lineTo(position.x+(i*dataInterval+margin) , position.y - (soundFFT[i]));
    }

    soundCurve.lineTo(position.x+((dataSize-1)*dataInterval+margin), position.y);
    soundCurve.lineTo(position.x+((dataSize-1)*dataInterval+(margin*2)), position.y);
    soundCurve.lineTo(position.x+((dataSize-1)*dataInterval+(margin*2)), position.y);
    
    soundCurve.lineTo(position.x+((dataSize-1)*dataInterval+(margin*2)), position.y);
    soundCurve.lineTo((position.x+(dataSize-1)*dataInterval+(margin*2)) , position.y+margin*2);
    soundCurve.lineTo(position.x , position.y+margin*2);
    soundCurve.lineTo(position.x , position.y);
    

    //soundCurve.curveTo((position.x+(dataSize-1)*dataInterval+(margin*2)) , position.y+margin*2);
    //soundCurve.curveTo(position.x , position.y+margin*2);
    //soundCurve.curveTo(position.x , position.y+margin*2);
    //soundCurve.lineTo(position.x , position.y);
    //soundCurve.lineTo(position.x+margin, position.y);
    //soundCurve.lineTo(position.x , position.y);
    
    soundCurve.close();
}

//void JLSoundSlice::update()
//{
//    soundCurve.clear();
//
//    soundCurve.lineTo(position.x+margin, position.y);
//    soundCurve.lineTo(position.x , position.y);
//    soundCurve.lineTo(position.x , position.y+margin*2);
//    soundCurve.lineTo((position.x+(dataSize-1)*dataInterval+(margin*2)) , position.y+margin*2);
//    soundCurve.lineTo(position.x+((dataSize-1)*dataInterval+(margin*2)), position.y);
//    soundCurve.lineTo(position.x+((dataSize-1)*dataInterval+margin), position.y);
//
//    for (int i=0;i<dataSize;i++)
//    {
//        soundCurve.lineTo(position.x+(i*dataInterval+margin) , position.y - (soundFFT[i]/2));
//    }
//
//}

void JLSoundSlice::draw()
{
    ofSetColor(255,0,0);
    
    soundCurve.draw();
    
    ofSetColor(0,0,0);
    
    indexFont->drawString(ofToString(index),position.x+40, position.y+15);
}



// event method area ////////////////////////////////////////////////////////////////



