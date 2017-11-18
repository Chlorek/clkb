/* 
 * File:   RandomEffect.hpp
 * Author: chlorek
 *
 * Created on November 16, 2017, 1:16 AM
 */

#ifndef RANDOMEFFECT_HPP
#define RANDOMEFFECT_HPP

#include "LinearEffect.hpp"
#include <vector>
#include <random>

namespace clkb {
    class RandomEffect : public LinearEffect {
        public:
            RandomEffect(std::vector<KEY> keys, std::chrono::milliseconds duration);
            RandomEffect(std::vector<KEY::INDEX_TYPE> keys, std::chrono::milliseconds duration);
            RandomEffect(std::chrono::milliseconds duration);
            RandomEffect(const RandomEffect& orig);
            virtual ~RandomEffect();
            
            void render(DeviceController* dvct, float progress);
        private:
            std::vector<KEY::INDEX_TYPE> keys;
            
            std::default_random_engine gen;
            std::uniform_int_distribution<RGB::TYPE> randomColor;
            
            RGB from, to;
    };
}

#endif /* RANDOMEFFECT_HPP */

