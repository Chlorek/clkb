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
        : last(std::chrono::system_clock::now()), duration(duration), keys(keys), col(col) {
    }
    
    BreathingEffect::BreathingEffect(std::chrono::milliseconds duration, const RGB col)
        : last(std::chrono::system_clock::now()), duration(duration), col(col) {
    }

    BreathingEffect::BreathingEffect(const BreathingEffect& o) : keys(o.keys), last(o.last), duration(o.duration), col(o.col) {
    }

    BreathingEffect::~BreathingEffect() {
    }
    
    void BreathingEffect::tick(DeviceController* dvct) {
        auto diff = std::chrono::system_clock::now() - last;
        if(diff >= duration) {
            last = std::chrono::system_clock::now();
            diff = duration;
        }
        
        float progress = (float)std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() / duration.count() * 2;
        if(progress > 1)
            progress = (2.f - progress);
        
        RGB rgb {(RGB::TYPE)(col.r * progress), (RGB::TYPE)(col.g * progress), (RGB::TYPE)(col.b * progress)};
        if(keys.size() > 0)
            for(KEY k : keys)
                dvct->setColor(k, rgb);
        else
            dvct->setColor(rgb);
    }
}