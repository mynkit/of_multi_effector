/**
* @file ofApp.cpp
* @brief 処理のコア部分
* @author mynkit
* @date 2019/10
*/

#include "ofApp.h"
#include <iostream>
using namespace std;

const int BUFFERSIZE = 256; //! バッファサイズ
const int SAMPLERATE = 44100; //! サンプルレート(Hz)

const int MAXDELAYTIME = 1000; //! delayの間隔の最大値(これよりDELAYTIMEが上回るとエラー)．
const int DELAYTIME = 400; //! delayの間隔(ms)
const float DECAYRATE = 0.5; //! delay音の減衰率

//--------------------------------------------------------------
void ofApp::setup(){
    cout << "バッファによるレイテンシー: " << setprecision(2) << ((float) BUFFERSIZE) * 1000 / SAMPLERATE << "ms" << endl;
    
    bufferSize = BUFFERSIZE;
    sampleRate = SAMPLERATE;
    inputBuffer.resize(bufferSize);
    
    myDelayIn = new delayIn(MAXDELAYTIME, sampleRate);
    myDelayOut = new delayOut(myDelayIn, DELAYTIME, DECAYRATE);
    
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
        float delayOutSample = myDelayOut->getSample();
        
        myDelayIn->feed(currentSample + (delayOutSample));
        
        buffer[i*nChannels+0] = currentSample + (delayOutSample);
        buffer[i*nChannels+1] = currentSample + (delayOutSample);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'x'){
        int new_delay_time = 100;
        float new_decay_rate = 0.2;
        myDelayOut->changeDelayTime(new_delay_time);
        myDelayOut->changeDecayRate(new_decay_rate);
    } else if (key == 'z'){
        myDelayOut->changeDelayTime(DELAYTIME);
        myDelayOut->changeDecayRate(DECAYRATE);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
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

