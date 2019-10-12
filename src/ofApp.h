#pragma once

#include "ofMain.h"


class tapIn{
/* inputされた音を保持しておくクラス
Args:
    time_ms (float): 何msDalay用に音を保持しておくか(これよりDELAYTIMEが上回ることはできない)
    _sampleRate (int): サンプルレート
*/
    
public:
    float* buffer;
    int writeIndex;
    int size;
    int sampleRate;
    
    ~tapIn();
    tapIn(float time_ms, int _sampleRate){
        
        static const int _size = (time_ms*0.001*_sampleRate);
        buffer = new float[_size];
        writeIndex = 0;
        sampleRate = _sampleRate;
        size = _size;
    }
    
    void feed(float currentSample){
        /* currentSampleをbuffer (float*)に格納して保持しておく
        Args:
            currentSample (float): 現在のサンプル．
        */
        buffer[writeIndex] = currentSample;
        writeIndex++;
        if(writeIndex>=size){ writeIndex = 0;}
    }
    
};

class tapOut{
/*
Args:
    inRef (tapIn*): tapInをそのまま渡す
    time_ms (float): 何ms遅延(delay)させるか
*/
    
public:
    
    float* ref;
    int size;
    int readPoint;
    int sampleRate;
    
    ~tapOut();
    tapOut(tapIn* inRef, float time_ms){
        
        ref = inRef->buffer;
        size = inRef->size;
        sampleRate = inRef->sampleRate;
        readPoint = size - (time_ms*0.001*sampleRate)-1;
        
    }
    
    float getSample(){
        /* 現在のサンプルを返す
        Returns:
            float
        */
        float temp = ref[readPoint];
        readPoint++;
        if(readPoint >= size){readPoint = 0;}
        return temp;
    }
    
    
};


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    void audioIn(float* buffer, int bufferSize, int nChannels);
    void audioOut(float* buffer, int bufferSize, int nChannels);
    
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
    
    
    int bufferSize;
    int sampleRate;
    vector<float> inputBuffer;
    
    tapIn* myTapIn;
    tapOut* myTapOut;
    
};
