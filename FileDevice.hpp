/* 
 * File:   FileDevice.hpp
 * Author: chlorek
 *
 * Created on October 10, 2016, 8:04 PM
 */

#ifndef FILEDEVICE_HPP
#define FILEDEVICE_HPP

#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <string>
#include <cstring>
#include "DataTypes.hpp"

namespace clkb {
    class FileDevice {
        public:
            FileDevice(DeviceInfo df, int flags = O_WRONLY | O_ASYNC);
            
            bool isOpen();
            
            /* 
             * Appends new line character and flushes automatically
             */
            ssize_t write(std::string data);
            
            /* 
             * Appends new line character and flushes automatically
             */
            ssize_t write(const char* data, size_t len);
            
            /* 
             * Writes just the data you passed, nothing more.
             * Does not flush automatically (if opened with O_ASYNC - default).
             */
            ssize_t raw_write(const char* data, size_t len);
            
            void flush();
        private:
            int dev;
    };
}

#endif /* FILEDEVICE_HPP */

