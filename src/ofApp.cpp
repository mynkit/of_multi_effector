#include "ofApp.h"

const int BUFFERSIZE = 512; //バッファサイズ
const int SAMPLERATE = 44100; //サンプルレート(Hz)

const int MAXDELAYTIME = 1000; //delayの間隔の最大値(これよりDELAYTIMEが上回るとエラー)．
const int DELAYTIME = 400; //delayの間隔(ms)
const float DECAYRATE = 0.5; //delay音の減衰率

//--------------------------------------------------------------
void ofApp::setup(){
    
    bufferSize = BUFFERSIZE;
    sampleRate = SAMPLERATE;
    inputBuffer.resize(bufferSize);
    
    myTapIn = new tapIn(MAXDELAYTIME, sampleRate);
    
    myTapOut = new tapOut(myTapIn, DELAYTIME);
    
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
        float tapOutSample = myTapOut->getSample();
        
        myTapIn->feed(currentSample + (tapOutSample*DECAYRATE));
        //myTapIn->feed(currentSample);
        
        
        buffer[i*nChannels+0] = currentSample + (tapOutSample*DECAYRATE);
        buffer[i*nChannels+1] = currentSample + (tapOutSample*DECAYRATE);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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

