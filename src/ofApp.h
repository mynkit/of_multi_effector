/**
* @file ofApp.h
* @brief クラスや変数定義
* @author mynkit
* @date 2019/10
*/

#pragma once

#include "ofMain.h"
#include "delayEffect.h"
#include "holdIn.h"
#include "overdriveEffect.h"

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

    // inputされた音の保持オブジェクト
    holdIn* myHoldIn;

    // overdrive
    overdriveOut* myOverdriveOut;
    bool overdriveOn;

    // sin波
    float phase;
    int frequency;
    float bw;
    bool peakingfilterOn;

    float omega;
    float alpha;
    float A;
    // フィルタ計算用のバッファ変数。
	float in1;
	float in2;
	float out1;
	float out2;
    
    float a0;
    float a1;
    float a2;
    float b0;
    float b1;
    float b2;

    // delay
    delayOut* myDelayOut;
    bool delayOn;

    // ring modulator
    bool ringModulatorOn;
    
};
