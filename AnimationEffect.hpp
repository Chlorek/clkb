/* 
 * File:   AnimationEffect.hpp
 * Author: chlorek
 *
 * Created on November 17, 2017, 3:52 PM
 */

#ifndef ANIMATIONEFFECT_HPP
#define ANIMATIONEFFECT_HPP

#include <vector>
#include "easybmp/EasyBMP.h"
#include "DataTypes.hpp"
#include "Effect.hpp"

namespace clkb {
    class AnimationEffect : public Effect {
        public:
            AnimationEffect() = delete;
            AnimationEffect(std::vector<const char*> path, std::chrono::milliseconds duration);
            AnimationEffect(const AnimationEffect& orig) = delete;
            virtual ~AnimationEffect();
            
            void tick(DeviceController* dvct);
        private:
            std::vector<BMP*> frames;
            unsigned int frameIndex = 0;
            time_point last;
            std::chrono::milliseconds duration, frameDuration;
    };
}

#endif /* ANIMATIONEFFECT_HPP */

