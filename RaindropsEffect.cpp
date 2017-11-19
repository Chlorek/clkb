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
    std::uniform_int_distribution<unsigned char> RaindropsEffect::randX(0, 19), RaindropsEffect::randY(0, 5);
    std::uniform_int_distribution<unsigned short> RaindropsEffect::randDelay(0, 1200);
    
    RaindropsEffect::RaindropsEffect(unsigned char maxDrops, std::chrono::milliseconds duration, RGB color) 
        : maxDrops(maxDrops), duration(duration), color(color) {
    }

    RaindropsEffect::RaindropsEffect(const RaindropsEffect& o)
        : maxDrops(o.maxDrops), duration(o.duration), color(color) {
    }

    RaindropsEffect::~RaindropsEffect() {
    }
    
    void RaindropsEffect::tick(DeviceController* dvct) {
        // draw raindrops
        for(decltype(drops)::iterator i = drops.begin(); i != drops.end(); ++i) {
            auto diff = std::chrono::system_clock::now() - (*i).begin;
            if(diff > duration)
                diff = duration;
            
            float progress = (float)std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() / duration.count() * 2;
            if(progress > 1)
                progress = (2.f - progress);
            if(progress < 0)
                progress = 0;
            else if(progress > 1)
                progress = 1;
            //std::cout << progress << std::endl;
            
            std::vector<KEY> keys = KEY::fromKeymap((*i).x, (*i).y);
            if(keys.size() > 0) {
                RGB bg = dvct->getColor(keys[0], layer-1);
                
                RGB colInTime = {progress*color.r, progress*color.g, progress*color.b};
                dvct->setColor(KEY::fromKeymap((*i).x, (*i).y), Effect::lerp(bg, colInTime, progress), layer);
                progress *= 0.9;
                colInTime = {progress*color.r, progress*color.g, progress*color.b};

                RGB around = Effect::lerp(bg, colInTime, progress);
                dvct->setColor(KEY::fromKeymap((*i).x-1, (*i).y), around, layer);
                dvct->setColor(KEY::fromKeymap((*i).x+1, (*i).y), around, layer);
                dvct->setColor(KEY::fromKeymap((*i).x, (*i).y-1), around, layer);
                dvct->setColor(KEY::fromKeymap((*i).x, (*i).y+1), around, layer);
                dvct->setColor(KEY::fromKeymap((*i).x-1, (*i).y-1), around, layer);
                dvct->setColor(KEY::fromKeymap((*i).x+1, (*i).y-1), around, layer);
                dvct->setColor(KEY::fromKeymap((*i).x-1, (*i).y+1), around, layer);
                dvct->setColor(KEY::fromKeymap((*i).x+1, (*i).y+1), around, layer);
            }
            // remove drop
            if(diff == duration)
                i = drops.erase(i);
        }
        
        // add raindrops
        while(drops.size() < maxDrops)
            drops.push_back({std::chrono::system_clock::now() + std::chrono::milliseconds(randDelay(rng)), randX(rng), randY(rng)});
    }
}