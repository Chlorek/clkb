/* 
 * File:   AnimationEffect.cpp
 * Author: chlorek
 * 
 * Created on November 17, 2017, 3:52 PM
 */

#include "AnimationEffect.hpp"
#include "DeviceController.hpp"

namespace clkb {
    AnimationEffect::AnimationEffect(std::vector<const char*> path, std::chrono::milliseconds duration)
        : last(std::chrono::system_clock::now()), duration(duration), frameDuration(duration / path.size()) {
        for(unsigned int i = 0; i < path.size(); ++i) {
            frames.push_back(new BMP);
            frames.at(i)->ReadFromFile(path[i]);
        }
    }
    
    AnimationEffect::~AnimationEffect() {
        for(BMP* tmp : frames)
            delete tmp;
    }
    
    void AnimationEffect::tick(DeviceController* dvct) {
        auto diff = std::chrono::system_clock::now() - last;
        if(diff >= frameDuration) {
            last = std::chrono::system_clock::now();
            diff = frameDuration;
            ++frameIndex;
        }
        if(frameIndex == frames.size())
            frameIndex = 0;

        for(unsigned int y = 0; y < frames[frameIndex]->TellHeight() && y < 6; ++y) {
            for(unsigned int x = 0; x < frames[frameIndex]->TellWidth() && x < 20; ++x) {
                auto col = frames[frameIndex]->GetPixel(x, y);
                dvct->setColor(KEY::keymap[y][x], {col.Red, col.Green, col.Blue});
            }
        }
    }
}