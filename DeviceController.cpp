/* 
 * File:   DeviceController.cpp
 * Author: chlorek
 * 
 * Created on October 10, 2016, 7:59 PM
 */

#include "DeviceController.hpp"

#include <cstring>
#include <iostream>
#include <boost/algorithm/string.hpp>

namespace clkb {
    DeviceController::DeviceController(FileDevice* fd, unsigned char framerate)
        : fd(fd), timestep(1000/framerate), last_count(std::chrono::system_clock::now()) {
        colors = std::shared_ptr<RGB[]>(new RGB[KEY::count]);
    }

    DeviceController::DeviceController(const DeviceController& o) : fd(o.fd), colors(o.colors),
            timestep(o.timestep), last_count(o.last_count), frames(o.frames), effects(o.effects) {
    }
    
    DeviceController::~DeviceController() {
    }

    void DeviceController::nextFrame() {
        // Apply effects
        for(std::shared_ptr<Effect> e : effects)
            e->tick(this);
        
        // Every command begins with rgb followed by main color
        std::string cmd("rgb");
        
        // Then per-key colors are applied
        for(KEY::INDEX_TYPE i = 0; i < KEY::count; ++i)
            cmd.append(" ").append(KEY::NAME[i]).append(":").append(rgbToHex(colors[i]));
        
        // debug line
        //std::cout << cmd << std::endl;
        
        // Finally write command to device
        if(fd->write(cmd) < cmd.length())
            std::cout << "> Write error: could not write all the data" << std::endl;
        else if(errno == EWOULDBLOCK)
            std::cout << "> Write error: would be blocking" << std::endl;
        else if(errno == EINVAL)
            ;//std::cout << "> Write error: EINVAL" << std::endl;
        else if(errno != 0)
            std::cout << "> Write error: unknown <" << errno << ">" << std::endl;
        
        // Frames control
        ++frames;
        if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_count).count() > 1000) {
            last_count = std::chrono::system_clock::now();
            if(frames < 30)
                std::cout << "> Framerate went low @ " << (int)frames << std::endl;
            frames = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(timestep));
    }

    void DeviceController::setColor(clkb::RGB color) {
        bgcolor = color;
        for(KEY::INDEX_TYPE i = 0; i < KEY::count; ++i)
            setColor(i, color);
    }
    
    void DeviceController::setColor(std::vector<KEY> keys, clkb::RGB color) {
        for(KEY key : keys)
            colors[key.i] = color;
    }
    
    void DeviceController::setColor(std::vector<KEY::INDEX_TYPE> keys, clkb::RGB color) {
        for(KEY::INDEX_TYPE key : keys)
            colors[key] = color;
    }
    
    void DeviceController::setColor(KEY key, clkb::RGB color) {
        colors[key.i] = color;
    }
    
    void DeviceController::setColor(KEY::INDEX_TYPE key, clkb::RGB color) {
        colors[key] = color;
    }
    
    void DeviceController::resetColor(std::vector<KEY> keys) {
        for(KEY key : keys)
            colors[key.i] = bgcolor;
    }
    
    void DeviceController::resetColor(std::vector<KEY::INDEX_TYPE> keys) {
        for(KEY::INDEX_TYPE key : keys)
            colors[key] = bgcolor;
    }
    
    void DeviceController::resetColor(KEY key) {
        colors[key.i] = bgcolor;
    }
    
    void DeviceController::resetColor(KEY::INDEX_TYPE key) {
        colors[key] = bgcolor;
    }
    
    void DeviceController::apply(Effect* effect) {
        std::shared_ptr<Effect> sptr(effect);
        effects.push_back(sptr);
    }
    
    RGB DeviceController::getColor(KEY key) {
        return getColor(key.i);
    }
            
    RGB DeviceController::getColor(KEY::INDEX_TYPE key) {
        if(key >= KEY::count)
            return {0,0,0};
        return colors[key];
    }
    
    std::vector<DeviceInfo> DeviceController::getDevices() {
        int dev = open("/dev/input/ckb0/connected", O_RDONLY | O_NONBLOCK);
        if(dev < 0)
            throw NoDeviceException("Driver not available - is ckb-daemon running?");

        char c;
        std::string line;
        std::vector<DeviceInfo> devices;
        for(;;) {
            ssize_t size = read(dev, &c, 1);
            if(size < 1)
                break;
            if(c != '\n') //load line
                line += c;
            else { //parse loaded line
                std::vector<std::string> words;
                boost::split(words, line, boost::is_any_of(" \t"));
                //keyboard name (which is last) may (and does) contain spaces
                if(words.size() >= 3) {
                    std::string name;
                    for(int j = 2; j < words.size(); j++)
                        name += words.at(j) + (j+1 >= words.size() ? "" : " ");
                    devices.push_back({words[0], words[1], name});
                }
                line.clear();
            }
        }

        return devices;
    }
    
    void rgbToHex(clkb::RGB rgb, char* dest) {
        // 6 chars + 1 for null
        snprintf(dest, 7, "%02x%02x%02x", rgb.r, rgb.g, rgb.b);
    }
    
    std::string rgbToHex(clkb::RGB rgb) {
        // 6 chars + 1 for null
        char hex[7] {};
        snprintf(hex, 7, "%02x%02x%02x", rgb.r, rgb.g, rgb.b);
        return hex;
    }
}