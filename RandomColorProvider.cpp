/* 
 * File:   RandomColorProvider.cpp
 * Author: chlorek
 * 
 * Created on November 19, 2017, 12:37 AM
 */

#include "RandomColorProvider.hpp"
#include "DeviceController.hpp"

namespace clkb {
    std::uniform_int_distribution<RGB::TYPE> RandomColorProvider::randChannel(0, 255);
    
    RandomColorProvider::RandomColorProvider() {
    }

    RandomColorProvider::RandomColorProvider(const RandomColorProvider& o) {
    }

    RandomColorProvider::~RandomColorProvider() {
    }
    
    RGB RandomColorProvider::next() {
        return {randChannel(rng), randChannel(rng), randChannel(rng)};
    }
}