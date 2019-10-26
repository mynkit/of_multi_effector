/**
* @file holdIn.h
* @brief input音を保持するためのクラスを実装
* @author mynkit
* @date 2019/10
*/

#pragma once

#include "delayEffect.h"

#include <iostream>
using namespace std;

/**
 * @brief 入力されたサンプルを指定の秒数だけ保持する機能を持ったクラス
 */
class holdIn{
    
public:
    float* buffer;
    int writeIndex;
    int size;
    int sampleRate;
    
    ~holdIn();
    holdIn(float time_ms, int _sampleRate){
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