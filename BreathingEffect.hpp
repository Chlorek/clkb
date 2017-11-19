/* 
 * File:   BreathingEffect.hpp
 * Author: chlorek
 *
 * Created on November 15, 2017, 9:52 PM
 */

#ifndef BREATHINGEFFECT_HPP
#define BREATHINGEFFECT_HPP

#include "LinearEffect.hpp"
#include <vector>

namespace clkb {
    class BreathingEffect : public LinearEffect {
        public:
            BreathingEffect() = delete;
            BreathingEffect(std::vector<KEY> keys, std::chrono::milliseconds duration, const RGB col);
            BreathingEffect(std::vector<KEY::INDEX_TYPE> keys, std::chrono::milliseconds duration, const RGB col);
            BreathingEffect(std::chrono::milliseconds duration, const RGB col);
            BreathingEffect(const BreathingEffect& orig);
            virtual ~BreathingEffect();
            
            void render(DeviceController* dvct, float progress);
        private:
            std::vector<KEY::INDEX_TYPE> keys;
            const RGB col;
    };
}

#endif /* BREATHINGEFFECT_HPP */

