/* 
 * File:   RandomEffect.hpp
 * Author: chlorek
 *
 * Created on November 16, 2017, 1:16 AM
 */

#ifndef RANDOMEFFECT_HPP
#define RANDOMEFFECT_HPP

#include "ColorProvider.hpp"
#include "LinearEffect.hpp"
#include <vector>
#include <random>

namespace clkb {
    class RandomEffect : public LinearEffect {
        public:
            RandomEffect(std::vector<KEY> keys, std::chrono::milliseconds duration, ColorProvider* provider);
            RandomEffect(std::vector<KEY::INDEX_TYPE> keys, std::chrono::milliseconds duration, ColorProvider* provider);
            RandomEffect(std::chrono::milliseconds duration, ColorProvider* provider);
            RandomEffect(const RandomEffect& orig);
            virtual ~RandomEffect();
            
            void render(DeviceController* dvct, float progress);
        private:
            std::vector<KEY::INDEX_TYPE> keys;
            
            RGB from, to;
            ColorProvider* provider;
    };
}

#endif /* RANDOMEFFECT_HPP */

