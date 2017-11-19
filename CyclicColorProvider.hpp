/* 
 * File:   CyclicColorProvider.hpp
 * Author: chlorek
 *
 * Created on November 19, 2017, 9:05 PM
 */

#ifndef CYCLICCOLORPROVIDER_HPP
#define CYCLICCOLORPROVIDER_HPP

#include "ColorProvider.hpp"

namespace clkb {
    class CyclicColorProvider : public ColorProvider {
        public:
            CyclicColorProvider() = delete;
            CyclicColorProvider(std::vector<RGB> colors);
            CyclicColorProvider(const CyclicColorProvider& o);
            virtual ~CyclicColorProvider();
            
            virtual RGB next();
        private:
            std::vector<RGB> colors;
            std::size_t nextColor = 0;
    };
}

#endif /* CYCLICCOLORPROVIDER_HPP */

