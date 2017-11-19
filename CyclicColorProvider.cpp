/* 
 * File:   CyclicColorProvider.cpp
 * Author: chlorek
 * 
 * Created on November 19, 2017, 9:05 PM
 */

#include "CyclicColorProvider.hpp"

namespace clkb {
    CyclicColorProvider::CyclicColorProvider(std::vector<RGB> colors) : colors(colors) {
    }

    CyclicColorProvider::CyclicColorProvider(const CyclicColorProvider& o) : colors(o.colors) {
    }

    CyclicColorProvider::~CyclicColorProvider() {
    }
    
    RGB CyclicColorProvider::next() {
        if(nextColor == colors.size())
            nextColor = 0;
        return colors.at(nextColor++);
    }
}