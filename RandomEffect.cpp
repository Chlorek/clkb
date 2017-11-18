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
        : last(std::chrono::system_clock::now()), duration(duration), randomColor(0, 255),
        from({randomColor(gen), randomColor(gen), randomColor(gen)}), to({randomColor(gen), randomColor(gen), randomColor(gen)}) {
        for(auto k : keys) 
            this->keys.push_back(k.i);
        gen.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }
    
    RandomEffect::RandomEffect(std::vector<KEY::INDEX_TYPE> keys, std::chrono::milliseconds duration)
        : last(std::chrono::system_clock::now()), duration(duration), keys(keys), randomColor(0, 255),
        from({randomColor(gen), randomColor(gen), randomColor(gen)}), to({randomColor(gen), randomColor(gen), randomColor(gen)}) {
        gen.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }
    
    RandomEffect::RandomEffect(std::chrono::milliseconds duration)
        : last(std::chrono::system_clock::now()), duration(duration), randomColor(0, 255),
        from({randomColor(gen), randomColor(gen), randomColor(gen)}), to({randomColor(gen), randomColor(gen), randomColor(gen)}) {
        gen.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }

    RandomEffect::RandomEffect(const RandomEffect& o) : keys(o.keys), last(o.last), duration(o.duration), randomColor(o.randomColor),
        from(o.from), to(o.to), gen(o.gen) {
    }
    
    RandomEffect::~RandomEffect() {
        //..
    }
    
    void RandomEffect::tick(DeviceController* dvct) {
        auto diff = std::chrono::system_clock::now() - last;
        if(diff >= duration) {
            last = std::chrono::system_clock::now();
            diff = duration;
        }
        
        float progress = (float)std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() / duration.count();
        if(progress > 1)
            progress = 1;
        
        if(keys.size() > 0)
            for(auto k : keys)
                dvct->setColor(k, Effect::lerp(from, to, progress));
        else
            dvct->setColor(Effect::lerp(from, to, progress));
        
        if(diff == duration) {
            from = to;
            to = {randomColor(gen), randomColor(gen), randomColor(gen)};
        }
    }
}