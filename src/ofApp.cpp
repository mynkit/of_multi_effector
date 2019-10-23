/**
* @file ofApp.cpp
* @brief 処理のコア部分
* @author mynkit
* @date 2019/10
*/

#include "ofApp.h"
#include <iostream>
using namespace std;

const int BUFFERSIZE = 1024; //! バッファサイズ
const int SAMPLERATE = 44100; //! サンプルレート(Hz)

const int MAXDELAYTIME = 1000; //! delayの間隔の最大値(これよりDELAYTIMEが上回るとエラー)．

//--------------------------------------------------------------
void ofApp::setup(){
    cout << "バッファによるレイテンシー: " << setprecision(2) << ((float) BUFFERSIZE) * 1000 / SAMPLERATE << "ms" << endl;
    
    bufferSize = BUFFERSIZE;
    sampleRate = SAMPLERATE;
    inputBuffer.resize(bufferSize);

    myDelayIn = new delayIn(MAXDELAYTIME, sampleRate);
    myDelayOut = new delayOut(myDelayIn);
    delayOn = false;
    
    ofSoundStreamSetup(2, 1, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
}
//--------------------------------------------------------------
void ofApp::audioIn(float* buffer, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){
        inputBuffer[i] = buffer[i];
    }
}

//--------------------------------------------------------------
void ofApp::audioOut(float* buffer, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        
        float currentSample = inputBuffer[i];
        if (delayOn == true){
            float delayOutSample = myDelayOut->getSample();
            currentSample += delayOutSample;
            myDelayIn->feed(currentSample);
        }
        buffer[i*nChannels+0] = currentSample;
        buffer[i*nChannels+1] = currentSample;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'd'){
        delayOn = true;
    } else if (key == 'z'){
        delayOn = false;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    if (delayOn == true){
        int new_delay_time = x / 10 * 10;
        float new_decay_rate = y / 1000.0;
        if(new_delay_time >= MAXDELAYTIME){new_delay_time = MAXDELAYTIME - 1;}
        if(new_decay_rate >= 0.7){new_decay_rate = 0.7;}
        myDelayOut->changeDelayTime(new_delay_time);
        myDelayOut->changeDecayRate(new_decay_rate);
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamClose();
}

