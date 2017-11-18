/* 
 * File:   Effect.cpp
 * Author: chlorek
 * 
 * Created on November 15, 2017, 9:27 PM
 */

#include "Effect.hpp"
#include "DeviceController.hpp"

namespace clkb {
    Effect::Effect() {
    }

    Effect::Effect(const Effect& o) {
    }

    Effect::~Effect() {
    }
    
    RGB Effect::lerp(RGB a, RGB b, float weight) {
        return {
                   a.r*(1-weight) + b.r*weight,
                   a.g*(1-weight) + b.g*weight,
                   a.b*(1-weight) + b.b*weight
               };
    }
}