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
    std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
    
    DeviceController::DeviceController(FileDevice* fd, unsigned char framerate)
        : fd(fd), timestep(1000/framerate), last_count(std::chrono::system_clock::now()) {
        RGB* bg = new RGB[KEY::count];
        RGB* fg = new RGB[KEY::count];
        std::fill(bg, bg + KEY::count, RGB{255,0,0});
        std::fill(fg, fg + KEY::count, RGB::NONE);
        colors.push_back(bg); //background
        colors.push_back(fg); //foreground
    }

    DeviceController::DeviceController(const DeviceController& o)
        : fd(o.fd), timestep(o.timestep), last_count(o.last_count), frames(o.frames), effects(o.effects) {
        for(RGB* orgLayer : o.colors) {
            RGB* newLayer = new RGB[KEY::count];
            std::memcpy(newLayer, orgLayer, KEY::count);
            colors.push_back(newLayer);
        }
    }
    
    DeviceController::~DeviceController() {
        for(RGB* layer : colors)
            delete[] layer;
    }

    void DeviceController::nextFrame() {
        // Apply effects
        for(unsigned int i = 0; i < effects.size(); ++i) {
            effects[i]->layer = i+2;
            effects[i]->tick(this);
        }
        
        // Every command begins with rgb followed by main color
        std::string cmd("rgb");
        
        // Then per-key colors are applied
        /*for(RGB* layer : colors)
            for(KEY::INDEX_TYPE i = 0; i < KEY::count; ++i)
                if(layer[i].active)
                    cmd.append(" ").append(KEY::NAME[i]).append(":").append(rgbToHex(layer[i]));*/
        for(KEY::INDEX_TYPE i = 0; i < KEY::count; ++i)
            cmd.append(" ").append(KEY::NAME[i]).append(":").append(rgbToHex(getColor(i, colors.size()-1)));
        
        // debug line
        //std::cout << colors.size() << std::endl;
        
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

    void DeviceController::setColor(clkb::RGB color, unsigned int layer) {
        if(layer == 0)
            bgcolor = color;
        for(KEY::INDEX_TYPE i = 0; i < KEY::count; ++i)
            setColor(i, color, layer);
    }
    
    void DeviceController::setColor(std::vector<KEY> keys, clkb::RGB color, unsigned int layer) {
        for(KEY key : keys)
            setColor(key.i, color, layer);
    }
    
    void DeviceController::setColor(std::vector<KEY::INDEX_TYPE> keys, clkb::RGB color, unsigned int layer) {
        for(KEY::INDEX_TYPE key : keys)
            setColor(key, color, layer);
    }
    
    void DeviceController::setColor(KEY key, clkb::RGB color, unsigned int layer) {
        setColor(key.i, color, layer);
    }
    
    void DeviceController::setColor(KEY::INDEX_TYPE key, clkb::RGB color, unsigned int layer) {
        if(colors.size() > layer)
            colors[layer][key] = color;
        else {
            RGB* newLayer = new RGB[KEY::count];
            std::fill(newLayer, newLayer+KEY::count, RGB::NONE);
            newLayer[key] = color;
            colors.push_back(newLayer);
        }
    }
    
    void DeviceController::resetColor(std::vector<KEY> keys, unsigned int layer) {
        for(KEY key : keys)
            resetColor(key.i, layer);
    }
    
    void DeviceController::resetColor(std::vector<KEY::INDEX_TYPE> keys, unsigned int layer) {
        for(KEY::INDEX_TYPE key : keys)
            resetColor(key, layer);
    }

    void DeviceController::resetColor(KEY key, unsigned int layer) {
        if(colors.size() > layer)
            colors[layer][key.i] = RGB::NONE;
    }

    void DeviceController::resetColor(KEY::INDEX_TYPE key, unsigned int layer) {
        if(colors.size() > layer)
            colors[layer][key] = RGB::NONE;
    }
    
    void DeviceController::apply(Effect* effect) {
        std::shared_ptr<Effect> sptr(effect);
        effects.push_back(sptr);
    }
    
    RGB DeviceController::getColor(KEY key, unsigned int layer) {
        return getColor(key.i, layer);
    }
            
    RGB DeviceController::getColor(KEY::INDEX_TYPE key, unsigned int layer) {
        // invalid values are reported inactive
        if(key >= KEY::count)
            return RGB::NONE;
        
        if(layer >= colors.size())
            layer = colors.size()-1;
        
        // find top-most layer with color
        for(RGB color = colors[layer][key]; layer >= 0; --layer, color = colors[layer][key])
            if(color.active)
                return color;
        
        return RGB::NONE;
    }
    
    RGB DeviceController::getBackgroundColor() {
        return bgcolor;
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