/**
* @file ofApp.h
* @brief クラスや変数定義
* @author mynkit
* @date 2019/10
*/

#pragma once

#include "ofMain.h"

/**
 * @brief 入力されたサンプルを指定の秒数だけ保持
 */
class tapIn{
    
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
    /**
     * @fn
     * currentSampleをbuffer (float*)に格納して保持しておく
     * @param (currentSample) 現在のサンプル
     * @return 戻り値の説明
     * @sa 参照すべき関数を書けばリンクが貼れる
     */
    void feed(float currentSample){
        buffer[writeIndex] = currentSample;
        writeIndex++;
        if(writeIndex>=size){ writeIndex = 0;}
    }
    
};

/**
 * @brief 入力されたサンプルを変換して返す
 */
class tapOut{
    
public:
    
    float* ref;
    int size;
    int readPoint;
    int sampleRate;
    
    ~tapOut();
    /**
     * @brief 変数の値の保持
     * @param (inRef) tapInクラスをオブジェクト化したもの
     * @param (time_ms) 何ms分Delayさせるか
     */
    tapOut(tapIn* inRef, float time_ms){
        //! バッファ
        ref = inRef->buffer;
        //! 保持されている音のサンプルサイズ
        size = inRef->size;
        //! サンプルレート
        sampleRate = inRef->sampleRate;
        //! 保持されているサンプルの中からディレイで使うサンプル
        readPoint = size - (time_ms*0.001*sampleRate)-1;
        
    }
    /**
     * @fn
     * 現在のサンプルを返す
     * @return 現在のサンプル
     */
    float getSample(){
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
