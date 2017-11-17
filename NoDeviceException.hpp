/* 
 * File:   NoDeviceException.hpp
 * Author: chlorek
 *
 * Created on October 10, 2016, 8:06 PM
 */

#ifndef NODEVICEEXCEPTION_HPP
#define NODEVICEEXCEPTION_HPP

class NoDeviceException : public std::exception
{
    private:
        const char* msg;
    public:
        NoDeviceException(const char* msg);
        virtual const char* what() const throw();
};

#endif /* NODEVICEEXCEPTION_HPP */

