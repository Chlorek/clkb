/* 
 * File:   RandomEffect.cpp
 * Author: chlorek
 * 
 * Created on November 16, 2017, 1:16 AM
 */

#include "RandomEffect.hpp"
#include "DeviceController.hpp"
#include "ColorProvider.hpp"

namespace clkb {
    RandomEffect::RandomEffect(std::vector<KEY> keys, std::chrono::milliseconds duration, ColorProvider* provider)
        : LinearEffect(duration), provider(provider), from(provider->next()), to(provider->next()) {
        for(auto k : keys) 
            this->keys.push_back(k.i);
    }
    
    RandomEffect::RandomEffect(std::vector<KEY::INDEX_TYPE> keys, std::chrono::milliseconds duration, ColorProvider* provider)
        : LinearEffect(duration), keys(keys), provider(provider), from(provider->next()), to(provider->next()) {
    }
    
    RandomEffect::RandomEffect(std::chrono::milliseconds duration, ColorProvider* provider)
        : LinearEffect(duration), provider(provider), from(provider->next()), to(provider->next()) {
    }

    RandomEffect::RandomEffect(const RandomEffect& o)
        : LinearEffect(o), keys(o.keys), provider(provider), from(o.from), to(o.to) {
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
            to = provider->next();
        }
    }
}