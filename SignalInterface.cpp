/* 
 * File:   SignalInterface.cpp
 * Author: chlorek
 * 
 * Created on November 16, 2017, 2:30 PM
 */

#include <iostream>
#include <cassert>
#include <chrono>
#include "SignalInterface.hpp"
#include "BreathingEffect.hpp"

namespace clkb {
    SignalInterface* SignalInterface::instance = nullptr;
    
    SignalInterface::SignalInterface(DeviceController* dc) : dc(dc), byte(-1) {
        if(instance != nullptr)
            throw std::runtime_error("no more than one instance of SignalInterface allowed");
        instance = this;
        
        for(unsigned char i = 0; i < 16; ++i)
            std::signal(SIGRTMIN+i, signalHandler);
        
        using namespace std;
        // Register commands
        registerCommand(0, {{&r, &g, &b}, [dc, this]() -> void {dc->setColor({r, g, b});}});
        registerCommand(1, {{&key, &r, &g, &b}, [dc, this]() -> void {dc->setColor(key, {r, g, b});}});
        registerCommand(2, {{&r, &g, &b}, [dc, this]() -> void {dc->apply(new BreathingEffect(3s, {r, g, b}));}});
    }

    SignalInterface::~SignalInterface() {
    }
    
    void SignalInterface::signalHandler(int sig) {
        instance->signalHandler_(sig);
    }
    
    void SignalInterface::signalHandler_(int sig) {
        if(readSigByte(sig)) {
            if(index < 0)
                index = byte;
            else {
                // check if command with such id exists
                if(commands.find(index) != commands.end()) {
                    // set value of bound argument
                    *(commands[index].binds.at(bindIndex++)) = byte;
                    // check if it is last bound value
                    if(bindIndex == commands[index].binds.size()) {
                        // make call to apply command
                        commands[index].func();
                        // reset values
                        bindIndex = 0;
                        index = -1;
                    }
                }
                else {
                    bindIndex = 0;
                    index = -1;
                }
            }
            byte = -1;
        }
    }
    
    bool SignalInterface::readSigByte(int sig) {
        if(byte < 0)
            byte = sig - SIGRTMIN;
        else {
            byte = byte*16 + (sig - SIGRTMIN);
            assert(byte >= 0 && byte <= 255);
            return true;
        }
        return false;
    }
    
    void SignalInterface::registerCommand(unsigned char id, commandData data) {
        commands.insert({id, data});
    }
}