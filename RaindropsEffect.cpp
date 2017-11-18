/* 
 * File:   RaindropsEffect.cpp
 * Author: chlorek
 * 
 * Created on November 18, 2017, 5:26 PM
 */

#include "RaindropsEffect.hpp"
#include "DeviceController.hpp"
#include <iostream>

namespace clkb {
    RaindropsEffect::RaindropsEffect(unsigned char maxDrops, std::chrono::milliseconds duration, RGB color) 
        : maxDrops(maxDrops), randX(0, 19), randY(0, 5), duration(duration), color(color) {
        gen.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }

    RaindropsEffect::RaindropsEffect(const RaindropsEffect& o)
        : maxDrops(o.maxDrops), duration(o.duration), gen(o.gen), randX(0, 19), randY(0, 5), color(color) {
    }

    RaindropsEffect::~RaindropsEffect() {
    }
    
    void RaindropsEffect::tick(DeviceController* dvct) {
        // draw raindrops
        for(decltype(drops)::iterator i = drops.begin(); i != drops.end(); ++i) {
            auto diff = std::chrono::system_clock::now() - (*i).begin;
            if(diff >= duration)
                diff = duration;
            
            float progress = (float)std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() / duration.count() * 2;
            if(progress > 1)
                progress = (2.f - progress);
            
            std::vector<KEY> keys = KEY::fromKeymap((*i).x, (*i).y);
            RGB bg = keys.size() > 0 ? dvct->getColor(keys.at(0)) : RGB{0,0,0};
            RGB colInTime = Effect::lerp(color, bg, progress);
            
            dvct->setColor(KEY::fromKeymap((*i).x, (*i).y), colInTime);
            progress /= 8;
            /*dvct->setColor(KEY::fromKeymap((*i).x-1, (*i).y), {progress*255, 0, 0});
            dvct->setColor(KEY::fromKeymap((*i).x+1, (*i).y), {progress*255, 0, 0});
            dvct->setColor(KEY::fromKeymap((*i).x, (*i).y-1), {progress*255, 0, 0});
            dvct->setColor(KEY::fromKeymap((*i).x, (*i).y+1), {progress*255, 0, 0});
            dvct->setColor(KEY::fromKeymap((*i).x-1, (*i).y-1), {progress*255, 0, 0});
            dvct->setColor(KEY::fromKeymap((*i).x+1, (*i).y-1), {progress*255, 0, 0});
            dvct->setColor(KEY::fromKeymap((*i).x-1, (*i).y+1), {progress*255, 0, 0});
            dvct->setColor(KEY::fromKeymap((*i).x+1, (*i).y+1), {progress*255, 0, 0});*/
            
            // remove drop
            if(diff == duration)
                i = drops.erase(i);
        }
        
        // add raindrops
        if(drops.size() < maxDrops)
            drops.push_back({std::chrono::system_clock::now(), randX(gen), randY(gen)});
    }
}