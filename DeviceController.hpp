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
             * Set background color (simply default for all keys)
             */
            void setColor(clkb::RGB color);
            
            /*
             * Apply color to given list of keys
             */
            void setColor(std::vector<KEY> keys, clkb::RGB color);
            
            /*
             * Apply color to given list of keys
             */
            void setColor(std::vector<KEY::INDEX_TYPE> keys, clkb::RGB color);
            
            /*
             * Apply color to given key
             */
            void setColor(KEY key, clkb::RGB color);
            
            /*
             * Apply color to given key
             */
            void setColor(KEY::INDEX_TYPE key, clkb::RGB color);
            
            /*
             * Removes color for given keys (background is used instead)
             */
            void resetColor(std::vector<KEY> keys);
            
            /*
             * Removes color for given keys (background is used instead)
             */
            void resetColor(std::vector<KEY::INDEX_TYPE> keys);
            
            /*
             * Removes color for given key (background is used instead)
             */
            void resetColor(KEY key);
            
            /*
             * Removes color for given key (background is used instead)
             */
            void resetColor(KEY::INDEX_TYPE keys);
            
            /*
             * Applies effect, animation on keys
             */
            void apply(Effect* effect);
            
            RGB getColor(KEY key);
            
            RGB getColor(KEY::INDEX_TYPE key);
            
            RGB getBackgroundColor();
            
            /*
             * Returns list of connected devices
             */
            static std::vector<DeviceInfo> getDevices();
        private:
            FileDevice* fd;
            std::shared_ptr<RGB[]> colors; // pointer to array
            clkb::RGB bgcolor {0, 0, 0};
            
            // used frame-rate control and counting
            unsigned short timestep;
            std::chrono::system_clock::time_point last_count;
            unsigned char frames = 0;
            
            std::vector<std::shared_ptr<Effect>> effects;
    };
}

#endif /* DEVICECONTROLLER_HPP */

