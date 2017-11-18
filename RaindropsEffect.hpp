/* 
 * File:   RaindropsEffect.hpp
 * Author: chlorek
 *
 * Created on November 18, 2017, 5:26 PM
 */

#ifndef RAINDROPSEFFECT_HPP
#define RAINDROPSEFFECT_HPP

#include <random>
#include <list>
#include "Effect.hpp"

namespace clkb {
    class RaindropsEffect : public Effect {
        private:
            struct drop_data {
                time_point begin;
                unsigned char x, y;
            };
        
        public:
            RaindropsEffect() = delete;
            RaindropsEffect(unsigned char maxDrops, std::chrono::milliseconds duration, RGB color);
            RaindropsEffect(const RaindropsEffect& orig);
            virtual ~RaindropsEffect();
            
            void tick(DeviceController* dvct);
        private:
            std::list<drop_data> drops;
            std::chrono::milliseconds duration;
            unsigned char maxDrops;
            RGB color;
            
            std::uniform_int_distribution<unsigned char> randX, randY;
            std::uniform_int_distribution<unsigned short> randDelay;
    };
}

#endif /* RAINDROPSEFFECT_HPP */

