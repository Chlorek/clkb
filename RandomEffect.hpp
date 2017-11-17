/* 
 * File:   RandomEffect.hpp
 * Author: chlorek
 *
 * Created on November 16, 2017, 1:16 AM
 */

#ifndef RANDOMEFFECT_HPP
#define RANDOMEFFECT_HPP

#include "Effect.hpp"
#include <vector>
#include <random>

namespace clkb {
    class RandomEffect : public Effect {
        public:
            RandomEffect(std::vector<KEY> keys, std::chrono::milliseconds duration);
            RandomEffect(std::vector<KEY::INDEX_TYPE> keys, std::chrono::milliseconds duration);
            RandomEffect(std::chrono::milliseconds duration);
            RandomEffect(const RandomEffect& orig);
            virtual ~RandomEffect();
            
            void tick(DeviceController* dvct);
        private:
            time_point last;
            std::chrono::milliseconds duration;
            std::vector<KEY::INDEX_TYPE> keys;
            
            std::default_random_engine gen;
            std::uniform_int_distribution<RGB::TYPE> randomColor;
            
            RGB from, to;
    };
}

#endif /* RANDOMEFFECT_HPP */

