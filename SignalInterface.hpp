/* 
 * File:   SignalInterface.hpp
 * Author: chlorek
 *
 * Created on November 16, 2017, 2:30 PM
 */

#ifndef SIGNALINTERFACE_HPP
#define SIGNALINTERFACE_HPP

#include <csignal>
#include <map>
#include <vector>
#include <functional>

#include "DeviceController.hpp"

namespace clkb {
    class SignalInterface;
    struct commandData {
        std::vector<unsigned char*> binds;
        std::function<void()> func;
    };
    
    class SignalInterface {       
        public:
            SignalInterface() = delete;
            SignalInterface(DeviceController* dc);
            SignalInterface(const SignalInterface& o) = delete;
            virtual ~SignalInterface();
            
            static void signalHandler(int sig);
        private:
            DeviceController* dc;
            KEY::INDEX_TYPE key;
            std::map<unsigned char, commandData> commands;
            static SignalInterface* instance;
            short index = -1, bindIndex = 0;
            short byte = -1;
            unsigned char r, g, b;
                        
            void signalHandler_(int sig);
            
            /*
             * Sets cmd member to 0-255, value is ready when method returns true
             */
            bool readSigByte(int sig);
            
            void registerCommand(unsigned char id, commandData data);
    };
}

#endif /* SIGNALINTERFACE_HPP */

