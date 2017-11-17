/* 
 * File:   FileDevice.cpp
 * Author: chlorek
 * 
 * Created on October 10, 2016, 8:04 PM
 */

#include "FileDevice.hpp"

#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>

namespace clkb {
    FileDevice::FileDevice(DeviceInfo di, int flags) {
        dev = open((di.devPath + "/cmd").c_str(), flags);
    }

    bool FileDevice::isOpen() {
        return dev > 0;
    }
    
    ssize_t FileDevice::write(std::string data) {
        this->write(data.c_str(), data.length());
    }
    
    ssize_t FileDevice::write(const char* data, size_t len) {
        char* newData = new char[len+1];
        std::memcpy(newData, data, len);
        newData[len] = '\n';
        auto s = ::write(dev, newData, len+1);
        delete[] newData;
        fsync(dev);
        return s;
    }

    ssize_t FileDevice::raw_write(const char* data, size_t len) {
        return ::write(dev, data, len);
    }
    
    void FileDevice::flush() {
        fsync(dev);
    }
}