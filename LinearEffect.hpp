/* 
 * File:   LinearEffect.hpp
 * Author: chlorek
 *
 * Created on November 18, 2017, 11:24 PM
 */

#ifndef LINEAREFFECT_HPP
#define LINEAREFFECT_HPP

#include "Effect.hpp"

namespace clkb {
    class LinearEffect : public Effect {
        public:
            LinearEffect() = delete;
            LinearEffect(std::chrono::milliseconds duration);
            LinearEffect(const LinearEffect& o);
            virtual ~LinearEffect();
            
            virtual void tick(DeviceController* dvct);
            virtual void render(DeviceController* dvct, float progress) = 0;
        private:
            time_point begin;
            std::chrono::milliseconds duration;
    };
}
#endif /* LINEAREFFECT_HPP */

