/* 
 * File:   LinearEffect.cpp
 * Author: chlorek
 * 
 * Created on November 18, 2017, 11:24 PM
 */

#include "LinearEffect.hpp"

namespace clkb {
    LinearEffect::LinearEffect(std::chrono::milliseconds duration) 
        : begin(std::chrono::system_clock::now()), duration(duration) {
    }

    LinearEffect::LinearEffect(const LinearEffect& o)
        : begin(o.begin), duration(o.duration) {
    }

    LinearEffect::~LinearEffect() {
    }
    
    void LinearEffect::tick(DeviceController* dvct) {
        auto diff = std::chrono::system_clock::now() - begin;
        if(diff >= duration) {
            begin = std::chrono::system_clock::now();
            diff = duration;
        }
        
        float progress = (float)std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() / duration.count();
        if(progress > 1)
            render(dvct, 1);
        else
            render(dvct, progress);
    }
}