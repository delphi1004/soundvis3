//
//  JLSoundWriter.cpp
//  SoundVis2
//
//  Created by jlsy on 18/11/2018.
//

#include "JLSoundWriter.h"



// private method area ////////////////////////////////////////////////////////////////


void JLSoundWriter::initDefaultData()
{
    int i = 0;
    
    zOrder = 0;
    
    curRow = 0;
    
    //1.76
    
    totalRowCount = 550;
    
    terrain.allocate(128+80, totalRowCount+20, OF_IMAGE_GRAYSCALE);
    
    frameRate = (terrain.getHeight());
    
    for (int y = 0;y<terrain.getHeight();y++)
    {
        for (int x = 0;x<terrain.getWidth();x++)
        {
            terrain.setColor(x,y,0);
        }
    }
    
    terrain.update();
}

void JLSoundWriter::setDefaultData(int setDataSize)
{
    dataSize = setDataSize;
}


// public method area ////////////////////////////////////////////////////////////////


JLSoundWriter::JLSoundWriter()
{
    initDefaultData();
}

JLSoundWriter::~JLSoundWriter()
{
    ;
}

void JLSoundWriter::stop()
{
    terrain.save("terrain-"+ofGetTimestampString()+".png");
    
    ofExit();
}

void JLSoundWriter::update()
{
    float height;
    string temp;
    
    temp = "";
    
    if ((ofGetFrameNum() % 20) == 0) // you can change the interval
    {
        for (int i=0;i<dataSize;i++)
        {
            height = (getSoundFFT()[i]/2);
            
            terrain.setColor((dataSize-i)+40,curRow+10,height);
        }
        
        curRow++;
        
        if (curRow > totalRowCount)
        {
            stop();
        }
    }
}

void JLSoundWriter::draw()
{
    ofSetColor(255,255,255);
   
    terrain.update();
    
    terrain.draw(0,0);
    
    ofSetColor(0);
    
    ofDrawBitmapString(curRow, 400, 300);
}


// event method area ////////////////////////////////////////////////////////////////
