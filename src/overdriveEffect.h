/**
* @file overdriveEffect.h
* @brief dev overdriveEffect
* @author mynkit
* @date 2019/10
*/

#pragma once

#include "holdIn.h"
#include "ofApp.h"

#include <iostream>
using namespace std;

class overdriveOut{
public:

    float current_th;
    float current_level;

    ~overdriveOut();
    overdriveOut(){
        //! overdriveの閾値
        current_th = 0.02;
        current_level = 5.0;
    }

    float hardClipping(float x){
        if (x > current_th){
            x = current_th;
        } else if (x < -current_th){
            x = -current_th;
        }
        return x;
    }

    float softClipping(float x){
        return current_th * atan(x / current_th) / (M_PI / 2.0);
    }

    float vacuumTubeClipping(float x){
        if (x >= current_th){
            x = current_th * 1.25;
        } else if (x < current_th && x >= current_th * 0.75){
            x = current_th * (-3.5 * (x / current_th - 1) * (x / current_th - 1) + 1.25);
        } else if (x < 0.75 * current_th && x >= -current_th){
            x = current_th * (0.5 * (x / current_th) * (x / current_th) + (x / current_th));
        } else {
            x = -0.5 * current_th;
        }
        return x;
    }

    /**
     * @fn
     * effect部分の実装
     * @param (sample) 現在のsample
     */
    float effect(float sample, int mode){
        if (mode == 0){
            sample = current_level * vacuumTubeClipping(sample);
        } else if (mode == 1){
            sample = current_level * softClipping(sample);
        } else if (mode == 2){
            sample = current_level * hardClipping(sample);
        }
        return sample;
    }
};