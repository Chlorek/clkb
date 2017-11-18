/* 
 * File:   Effect.hpp
 * Author: chlorek
 *
 * Created on November 15, 2017, 9:27 PM
 */

#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "DataTypes.hpp"

namespace clkb {
    class DeviceController;
    
    class Effect {
        public:
            Effect();
            Effect(const Effect& orig);
            virtual ~Effect();
            
            virtual void tick(DeviceController* dvct) = 0;
            
            static RGB lerp(RGB a, RGB b, float weight);
        private:
    };
}

#endif /* EFFECT_HPP */

