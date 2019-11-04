/**
* @file ofApp.cpp
* @brief 処理のコア部分
* @author mynkit
* @date 2019/10
*/

#include "ofApp.h"
#include <iostream>
using namespace std;

const int BUFFERSIZE = 216; //! バッファサイズ(256推奨．大きくすると処理に余裕はでるが遅延が長くなる)
const int SAMPLERATE = 44100; //! サンプルレート(Hz)

const int MAXDELAYTIME = 1000; //! delayの間隔の最大値(これよりDELAYTIMEが上回るとエラー)．

//--------------------------------------------------------------
void ofApp::setup(){
    cout << "バッファによるレイテンシー: " << setprecision(2) << ((float) BUFFERSIZE) * 1000 / SAMPLERATE << "ms" << endl;
    
    bufferSize = BUFFERSIZE;
    sampleRate = SAMPLERATE;
    frequency = 800;
    bw = 0.3;
    inputBuffer.resize(bufferSize);

    myHoldIn = new holdIn(MAXDELAYTIME, sampleRate);
    myDelayOut = new delayOut(myHoldIn);
    myOverdriveOut = new overdriveOut();

    // effectorは最初全部OFFにしておく
    overdriveOn = false;
    ringModulatorOn = false;
    delayOn = false;
    peakingfilterOn = false;

    // それぞれの変数は下記のとおりとする
    // samplerate … サンプリング周波数
    // freq … カットオフ周波数
    // bw   … 帯域幅

    omega = 2.0f * M_PI * frequency / sampleRate;
    alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));
    float gain = 10.0;
    A     = pow(10.0f, (gain / 40.0f) );
    // フィルタ計算用のバッファ変数。
	in1  = 0.0f;
	in2  = 0.0f;
	out1 = 0.0f;
	out2 = 0.0f;
    
    a0 =  1.0f + alpha / A;
    a1 = -2.0f * cos(omega);
    a2 =  1.0f - alpha / A;
    b0 =  1.0f + alpha * A;
    b1 =  -2.0f * cos(omega);
    b2 =  1.0f - alpha * A;
    
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

    float phaseDiff;

    phaseDiff = TWO_PI * frequency/sampleRate;
    
    for(int i = 0; i < bufferSize; i++){

		phase += phaseDiff;
		
		while (phase > TWO_PI) {
			phase -= TWO_PI;
		}
        
        float currentSample = inputBuffer[i];

        if (peakingfilterOn == true){
            currentSample = b0/a0 * currentSample + b1/a0 * in1  + b2/a0 * in2 - a1/a0 * out1 - a2/a0 * out2;
            in2  = in1;       // 2つ前の入力信号を更新
            in1  = inputBuffer[i];  // 1つ前の入力信号を更新
            out2 = out1;      // 2つ前の出力信号を更新
            out1 = currentSample; // 1つ前の出力信号を更新
        }

        if (overdriveOn == true){
            currentSample = myOverdriveOut->effect(currentSample, 2);
        }

        if (ringModulatorOn == true){
            currentSample = currentSample * sin(phase);
        }
        if (delayOn == true){
            currentSample = myDelayOut->effect(myHoldIn, currentSample);
        }
        buffer[i*nChannels+0] = currentSample;
        buffer[i*nChannels+1] = currentSample;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'o'){
        if (overdriveOn == false){
            overdriveOn = true;
        } else {
            overdriveOn = false;
        }
    } else if (key == 'p'){
        if (peakingfilterOn == false){
            peakingfilterOn = true;
        } else {
            peakingfilterOn = false;
        }
    } else if (key == 'd'){
        if (delayOn == false){
            delayOn = true;
        } else {
            delayOn = false;
        }
    } else if (key == 'r'){
        if (ringModulatorOn == false){
            ringModulatorOn = true;
        } else {
            ringModulatorOn = false;
        }
    } else if (key == 'z'){
        overdriveOn = false;
        ringModulatorOn = false;
        delayOn = false;
        peakingfilterOn = false;
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
    if (ringModulatorOn == true || peakingfilterOn == true){
        frequency = x / 10.0;
        if(frequency < 1){frequency = 1;}
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

