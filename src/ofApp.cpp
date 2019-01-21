#include "ofApp.h"



// private method area ////////////////////////////////////////////////////////////////

void ofApp::initDefaultData()
{
    int expRow;
    int index;
    
    ofSetBackgroundColor(255);
    
    ofSetLineWidth(0.1);
    ofSetColor(255);
    
    ofSetBackgroundAuto(true);
    
    scrWidth = ofGetScreenWidth()+150;
    scrHeight = ofGetScreenHeight();
    
    ofLog() << scrWidth << scrHeight;
    
    maxBand = 128;
    
    sliceWidth = 171;
    
    mySound.setup(maxBand);
    
    mySound.play();
    
    soundFFT = mySound.getFFT();
    
    displaySlice = new JLSoundSlice();
    
    displaySlice->setSoundFFT(mySound.getFFT());
    displaySlice->setDefaultData(sliceWidth*3, 20, maxBand,0,&indexFont);
    displaySlice->setPosition(400,400);
}

void ofApp::initSoundSlice()
{
    curMode = MODE_SLICE;
    
    totalSliceCount = 0;
    curSliceIndex = 0;
    curPage = 0;
    totalPageCount = 3;
    index = 0;
    
    expRow =  round((mySound.getLength()/2.0)/13.0);
    
    expWidth = (sliceWidth*13)+(10 *13);
    expHeight = (expRow * 120)+120;
    
    for (int i=0;i<totalPageCount;i++)
    {
        index = 0;
        
        for (int y = 120;y<expHeight;y+= 120)
        {
            for (int x=20;x<expWidth;x+=(sliceWidth+10))
            {
                testSlice[i][index].setSoundFFT(mySound.getFFT());
                testSlice[i][index].setDefaultData(sliceWidth, 10, maxBand,totalSliceCount,&indexFont);
                
                testSlice[i][index].setPosition(x,y);
                
                index++;
                
                totalSliceCount++;
            }
        }
    }
    
    totalSliceCount /= totalPageCount;
    
    ofLog() << "Total slice count = " << totalSliceCount;
}

void ofApp::initSoundWriter()
{
    curMode = MODE_WRITING;
    
    soundWriter = new JLSoundWriter();
    
    soundWriter->setDefaultData(maxBand);
    
    soundWriter->setSoundFFT(mySound.getFFT());
    
    totalSliceCount = 10;
}

void ofApp::saveIt()
{
    ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+"_"+ofToString(curPage)+".pdf", false);
    
    for (int i = 0;i<totalSliceCount;i++)
    {
        testSlice[curPage][i].draw();
    }
    
    ofEndSaveScreenAsPDF();
    
    ofLog() << "Data saved!  page = " << curPage;
    
    curPage++;
    
    curSliceIndex = 0;
    
    if (curPage >= totalPageCount)
    {
        curPage = 0;
        
        ofExit();
    }
    
    ofSetBackgroundColor(255);
}

void ofApp::updateSlice()
{
    if ((ofGetFrameNum() % 50) == 0)
    {
        refresh = true;
        
        testSlice[curPage][curSliceIndex].update();
        
        curSliceIndex++;
        
        if (curSliceIndex >= totalSliceCount)
        {
            saveIt();
        }
    }
}

void ofApp::updateWriting()
{
    soundWriter->update();
}

void ofApp::drawSlice()
{
    for (int i = 0;i<totalSliceCount;i++)
    {
        testSlice[curPage][i].draw();
    }
    
    ofDrawLine(expWidth,0,expWidth,10);
    ofDrawLine(expWidth, expHeight, expWidth+10, expHeight);
}

void ofApp::drawWriting()
{
    soundWriter->draw();
}


// public method area ////////////////////////////////////////////////////////////////


void ofApp::setup()
{
    ofSetWindowShape(ofGetScreenWidth()+200,ofGetScreenHeight());
    
    //ofSetWindowShape(4000,2000);
    
    //ofSetupOpenGL(5000, 768, OF_WINDOW);
    
    indexFont.load("ITCAvantGardePro-XLt.otf", 10 , false,true,true,1.0);
    
    indexFont.setLetterSpacing(1.5);
    
    ofSetFrameRate(1000);
    
    initDefaultData();
    
    //initSoundSlice();
    
    initSoundWriter();
    
    testImage.allocate(128, 128*2.5, OF_IMAGE_COLOR);
    
    
}

//--------------------------------------------------------------
void ofApp::update()
{
    int posX;
    int interval;
    
    ofSetColor(255);
    
    mySound.update();
    
    displaySlice->update();
    
    switch(curMode)
    {
        case MODE_SLICE : updateSlice();break;
        case MODE_WRITING : updateWriting();break;
    }
    
}

//--------------------------------------------------------------

void ofApp::draw()
{
    ofBackground(255);
    
    if( ofGetFrameNum() == 1 )
    {
        ofSetWindowPosition( ofGetWindowPositionX(), ofGetWindowPositionY()+1 );
        ofSetWindowPosition( ofGetWindowPositionX(), ofGetWindowPositionY()-1 );
    }
    
    displaySlice->draw();
    
    switch(curMode)
    {
        case MODE_SLICE : drawSlice();break;
        case MODE_WRITING : drawWriting();break;
    }
    
}


// event method area ////////////////////////////////////////////////////////////////

void ofApp::keyPressed(int key)
{
    //soundWriter->stop();
    
    //ofExit();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}
