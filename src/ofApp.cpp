#include "ofApp.h"

const int DELAYTIME = 400; //delayの感覚
const float DECAYRATE = 0.7; //delay音の減衰率

//--------------------------------------------------------------
void ofApp::setup(){
    
    bufferSize = 512;
    sampleRate = 44100;
    inputBuffer.resize(bufferSize);
    
    myTapIn = new tapIn(10000, sampleRate);
    
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
        
        
        buffer[i*nChannels+0] = currentSample + tapOutSample;
        buffer[i*nChannels+1] = currentSample + tapOutSample;
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

