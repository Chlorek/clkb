/* 
 * File:   Effect.hpp
 * Author: chlorek
 *
 * Created on November 15, 2017, 9:27 PM
 */

#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "DataTypes.hpp"
#include <random>

namespace clkb {
    class DeviceController;
    
    class Effect {
        friend class DeviceController;
        public:
            Effect();
            Effect(const Effect& o);
            virtual ~Effect();
            
            virtual void tick(DeviceController* dvct) = 0;
            
            static RGB lerp(RGB a, RGB b, float weight);
        protected:
            unsigned int layer;
    };
}

#endif /* EFFECT_HPP */

