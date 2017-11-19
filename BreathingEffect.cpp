/* 
 * File:   BreathingEffect.cpp
 * Author: chlorek
 * 
 * Created on November 15, 2017, 9:52 PM
 */

#include "BreathingEffect.hpp"
#include "DeviceController.hpp"

#include <iostream>

namespace clkb {
    BreathingEffect::BreathingEffect(std::vector<KEY> keys, std::chrono::milliseconds duration, const RGB col)
        : LinearEffect(duration), col(col) {
        for(KEY k : keys)
            this->keys.push_back(k.i);
    }
    
    BreathingEffect::BreathingEffect(std::vector<KEY::INDEX_TYPE> keys, std::chrono::milliseconds duration, const RGB col)
        : LinearEffect(duration), keys(keys), col(col) {
    }
    
    BreathingEffect::BreathingEffect(std::chrono::milliseconds duration, const RGB col)
        : LinearEffect(duration), col(col) {
        for(KEY::INDEX_TYPE i = 0; i < KEY::count; ++i)
            keys.push_back(i);
    }

    BreathingEffect::BreathingEffect(const BreathingEffect& o) : LinearEffect(o), keys(o.keys), col(o.col) {
    }

    BreathingEffect::~BreathingEffect() {
    }
    
    void BreathingEffect::render(DeviceController* dvct, float progress) {
        progress *= 2;
        if(progress > 1)
            progress = (2.f - progress);
        
        RGB rgb {(RGB::TYPE)(col.r * progress), (RGB::TYPE)(col.g * progress), (RGB::TYPE)(col.b * progress)};
        for(KEY::INDEX_TYPE k : keys) {
            if(progress == 0)
                dvct->resetColor(k, layer);
            else
                dvct->setColor(k, Effect::lerp(dvct->getColor(k, layer-1), rgb, progress), layer);
        }
    }
}