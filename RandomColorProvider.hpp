/* 
 * File:   RandomColorProvider.hpp
 * Author: chlorek
 *
 * Created on November 19, 2017, 12:37 AM
 */

#ifndef RANDOMCOLORPROVIDER_HPP
#define RANDOMCOLORPROVIDER_HPP

#include <random>
#include "ColorProvider.hpp"
#include "Effect.hpp"

namespace clkb {
    class RandomColorProvider : public ColorProvider {
        public:
            RandomColorProvider();
            RandomColorProvider(const RandomColorProvider& o);
            virtual ~RandomColorProvider();
            
            virtual RGB next();
        private:
            static std::uniform_int_distribution<RGB::TYPE> randChannel;
    };
}
#endif /* RANDOMCOLORPROVIDER_HPP */

