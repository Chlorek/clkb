/* 
 * File:   RandomEffect.cpp
 * Author: chlorek
 * 
 * Created on November 16, 2017, 1:16 AM
 */

#include "RandomEffect.hpp"
#include "DeviceController.hpp"

namespace clkb {
    RandomEffect::RandomEffect(std::vector<KEY> keys, std::chrono::milliseconds duration)
        : LinearEffect(duration), randomColor(0, 255), 
          from({randomColor(rng), randomColor(rng), randomColor(rng)}), to({randomColor(rng), randomColor(rng), randomColor(rng)}) {
        for(auto k : keys) 
            this->keys.push_back(k.i);
    }
    
    RandomEffect::RandomEffect(std::vector<KEY::INDEX_TYPE> keys, std::chrono::milliseconds duration)
        : LinearEffect(duration), keys(keys), randomColor(0, 255), 
          from({randomColor(rng), randomColor(rng), randomColor(rng)}), to({randomColor(rng), randomColor(rng), randomColor(rng)}) {
    }
    
    RandomEffect::RandomEffect(std::chrono::milliseconds duration)
        : LinearEffect(duration), randomColor(0, 255),
          from({randomColor(rng), randomColor(rng), randomColor(rng)}), to({randomColor(rng), randomColor(rng), randomColor(rng)}) {
    }

    RandomEffect::RandomEffect(const RandomEffect& o)
        : LinearEffect(o), keys(o.keys), randomColor(o.randomColor), from(o.from), to(o.to) {
    }
    
    RandomEffect::~RandomEffect() {
        //..
    }
    
    void RandomEffect::render(DeviceController* dvct, float progress) {
        if(keys.size() > 0)
            for(auto k : keys)
                dvct->setColor(k, Effect::lerp(from, to, progress));
        else
            dvct->setColor(Effect::lerp(from, to, progress));
        
        if(progress == 1) {
            from = to;
            to = {randomColor(rng), randomColor(rng), randomColor(rng)};
        }
    }
}