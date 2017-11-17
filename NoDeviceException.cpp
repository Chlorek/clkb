/* 
 * File:   NoDeviceException.cpp
 * Author: chlorek
 * 
 * Created on October 10, 2016, 8:06 PM
 */

#include <exception>

#include "NoDeviceException.hpp"

NoDeviceException::NoDeviceException(const char* msg)
{
    this->msg = msg;
}

const char* NoDeviceException::what() const throw()
{
    return msg;
}

