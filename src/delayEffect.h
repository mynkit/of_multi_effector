/**
* @file delayEffect.h
* @brief dev delayEffect
* @author mynkit
* @date 2019/10
*/

#pragma once

#include "holdIn.h"
#include "ofApp.h"

#include <iostream>
using namespace std;

/**
 * @brief 入力されたサンプルを変換して返す
 */
class delayOut{
    
public:
    
    float* ref;
    int size;
    int readPoint;
    int currentDelayTime;
    float currentDecayRate;
    int sampleRate;
    
    ~delayOut();
    /**
     * @brief 変数の値の保持
     * @param (inRef) holdInクラスをオブジェクト化したもの
     */
    delayOut(holdIn* inRef){
        //! 現在のdelaytime(ms) 最初は適当に初期値いれておく
        currentDelayTime = 400;
        //! 現在のdecayrate 最初は適当に初期値いれておく
        currentDecayRate = 0.5;
        //! バッファ
        ref = inRef->buffer;
        //! 保持されている音のサンプルサイズ
        size = inRef->size;
        //! サンプルレート
        sampleRate = inRef->sampleRate;
        //! 保持されているサンプルの中からディレイで使うサンプル
        readPoint = size - (currentDelayTime*0.001*sampleRate)-1;
        
    }
    /**
     * @fn
     * 現在のサンプルをcurrentDelayTime分遅らせて返す
     * @return 現在のサンプル
     */
    float getDelaySample(){
        float temp = ref[readPoint];
        readPoint++;
        if(readPoint >= size){readPoint = 0;}
        return temp * currentDecayRate;
    }

    /**
     * @fn
     * delaytimeを変更する
     * @param (delaytime) 新たなdelaytime
     */
    void changeDelayTime(float newDelayTime){
        readPoint -= (newDelayTime - currentDelayTime) * 0.001 * sampleRate;
        if(readPoint >= size){readPoint = 0;}
        currentDelayTime = newDelayTime;
    }

    /**
     * @fn
     * decayrateを変更する
     * @param (newDecayRate) 新たなdecayrate
     */
    void changeDecayRate(float newDecayRate){
        currentDecayRate = newDecayRate;
    }

    /**
     * @fn
     * effect部分の実装
     * @param (inref) holdInオブジェクト
     * @param (sample) 現在のsample
     */
    float effect(holdIn* inref, float sample){
        sample += getDelaySample();
        inref->feed(sample);
        return sample;
    }
    
    
};
