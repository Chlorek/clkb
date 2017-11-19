/* 
 * File:   DeviceController.hpp
 * Author: chlorek
 *
 * Created on October 10, 2016, 7:59 PM
 */

#ifndef DEVICECONTROLLER_HPP
#define DEVICECONTROLLER_HPP

#include "FileDevice.hpp"
#include "NoDeviceException.hpp"
#include "Effect.hpp"

#include <thread>
#include <string>
#include <vector>
#include <memory>

namespace clkb {
    extern std::default_random_engine rng;
    
    enum class LAYER : unsigned int { BACKGROUND = 0, FOREGROUND = 1 };
    
    /*
     * Expects dest to be 7-bytes long, undefined behavior otherwise.
     * Resulting c-string is null-terminated.
     */
    static void rgbToHex(clkb::RGB rgb, char* dest);

    /*
     * More comfortable C++ version of rgbToHex()
     */
    static std::string rgbToHex(clkb::RGB rgb);
    
    class DeviceController {
        public:
            DeviceController() = delete;
            DeviceController(FileDevice* fd, unsigned char framerate = 30);
            DeviceController(const DeviceController& o);
            virtual ~DeviceController();

            /*
             * Sends commands to the keyboard and sleeps for fixed time to keep frame-rate
             */
            void nextFrame();
            
            /*
             * Set all colors of specified layer.
             * Also sets background color if layer == LAYER::BACKGROUND
             */
            void setColor(clkb::RGB color, unsigned int layer = (unsigned int)LAYER::BACKGROUND);
            
            /*
             * Apply color to given list of keys
             */
            void setColor(std::vector<KEY> keys, clkb::RGB color, unsigned int layer = (unsigned int)LAYER::FOREGROUND);
            
            /*
             * Apply color to given list of keys
             */
            void setColor(std::vector<KEY::INDEX_TYPE> keys, clkb::RGB color, unsigned int layer = (unsigned int)LAYER::FOREGROUND);
            
            /*
             * Apply color to given key
             */
            void setColor(KEY key, clkb::RGB color, unsigned int layer = (unsigned int)LAYER::FOREGROUND);
            
            /*
             * Apply color to given key
             */
            void setColor(KEY::INDEX_TYPE key, clkb::RGB color, unsigned int layer = (unsigned int)LAYER::FOREGROUND);
            
            /*
             * Removes color for given keys (sets to RGB::NONE)
             */
            void resetColor(std::vector<KEY> keys, unsigned int layer = (unsigned int)LAYER::FOREGROUND);
            
            /*
             * Removes color for given keys (sets to RGB::NONE)
             */
            void resetColor(std::vector<KEY::INDEX_TYPE> keys, unsigned int layer = (unsigned int)LAYER::FOREGROUND);
            
            /*
             * Removes color for given key (sets to RGB::NONE)
             */
            void resetColor(KEY key, unsigned int layer = (unsigned int)LAYER::FOREGROUND);
            
            /*
             * Removes color for given key (sets to RGB::NONE)
             */
            void resetColor(KEY::INDEX_TYPE key, unsigned int layer = (unsigned int)LAYER::FOREGROUND);
            
            /*
             * If specified layer has no color search goes deeper, if there is no active RGB color at all
             * then RGB::NONE is returned.
             */
            RGB getColor(KEY key, unsigned int layer = (unsigned int)LAYER::FOREGROUND);
            
            /*
             * If specified layer has no color search goes deeper, if there is no active RGB color at all
             * then RGB::NONE is returned.
             */
            RGB getColor(KEY::INDEX_TYPE key, unsigned int layer = (unsigned int)LAYER::FOREGROUND);
            
            /*
             * Returns background color set with setColor(RGB) for background layer
             */
            RGB getBackgroundColor();
            
            /*
             * Applies effect, animation on keys
             */
            void apply(Effect* effect);
            
            /*
             * Returns list of connected devices
             */
            static std::vector<DeviceInfo> getDevices();
        private:
            FileDevice* fd;
            
            /*
             * First two layers are in order: background and foreground colormap.
             */
            std::vector<RGB*> colors;
            clkb::RGB bgcolor {0, 0, 0};
            
            // used frame-rate control and counting
            unsigned short timestep;
            std::chrono::system_clock::time_point last_count;
            unsigned char frames = 0;
            
            std::vector<std::shared_ptr<Effect>> effects;
    };
}

#endif /* DEVICECONTROLLER_HPP */

