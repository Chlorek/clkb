/* 
 * File:   BreathingEffect.hpp
 * Author: chlorek
 *
 * Created on November 15, 2017, 9:52 PM
 */

#ifndef BREATHINGEFFECT_HPP
#define BREATHINGEFFECT_HPP

#include "Effect.hpp"
#include <vector>

namespace clkb {
    class BreathingEffect : public Effect {
        public:
            BreathingEffect() = delete;
            BreathingEffect(std::vector<KEY> keys, std::chrono::milliseconds duration, const RGB col);
            BreathingEffect(std::chrono::milliseconds duration, const RGB col);
            BreathingEffect(const BreathingEffect& orig);
            virtual ~BreathingEffect();
            
            void tick(DeviceController* dvct);
        private:
            time_point last;
            std::chrono::milliseconds duration;
            std::vector<KEY> keys;
            const RGB col;
    };
}

#endif /* BREATHINGEFFECT_HPP */

