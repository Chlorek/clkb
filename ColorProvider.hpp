/* 
 * File:   ColorProvider.hpp
 * Author: chlorek
 *
 * Created on November 19, 2017, 12:32 AM
 */

#ifndef COLORPROVIDER_HPP
#define COLORPROVIDER_HPP

#include "DataTypes.hpp"

namespace clkb {
    class ColorProvider {
        public:
            ColorProvider();
            ColorProvider(const ColorProvider& orig);
            virtual ~ColorProvider();
            
            virtual RGB next() = 0;
        private:
    };
}

#endif /* COLORPROVIDER_HPP */

