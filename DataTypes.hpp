/* 
 * File:   DataTypes.hpp
 * Author: chlorek
 *
 * Created on October 10, 2016, 8:03 PM
 */

#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include <string>
#include <chrono>
#include <vector>

namespace clkb {
    /*
     * Duration with milliseconds accuracy
     */
    typedef std::chrono::duration<int, std::chrono::milliseconds> time_duration;
    typedef std::chrono::time_point<std::chrono::system_clock> time_point;
    
    struct RGB {
            typedef unsigned char TYPE;
            
            /*RGB() = delete;
            RGB(TYPE r, TYPE g, TYPE b) : r(r), g(g), b(b) {};
            RGB(const RGB& o) : r(r), g(g), b(b) {};*/
            
            TYPE r, g, b;
    };
    
    struct DeviceInfo {
        std::string devPath, serial, name;
    };
    
    /* An attempt to implement Java-like enum */
    class KEY {
        public:
            typedef unsigned char INDEX_TYPE;
            
            // "Enum" fields
            static const KEY BRIGHTNESS, WINLOCK, MUTE,
            ESC, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, PRINT_SCREEN, SCROLL_LOCK, PAUSE, MEDIA_STOP, MEDIA_PREV, MEDIA_PAUSE, MEDIA_NEXT,
            GRAVE, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO, MINUS, EQUAL, BACKSPACE, INSERT, HOME, PAGE_UP, NUMLOCK, NUM_DIV, NUM_MUL, NUM_MIN,
            TAB, Q, W, E, R, T, Y, U, I, O, P, LBRACE, RBRACE, BACKSLASH, DELETE, END, PAGE_DOWN, NUM_7, NUM_8, NUM_9, NUM_PLUS,
            CAPS_LOCK, A, S, D, F, G, H, J, K, L, SEMICOLON, APOSTROPHE, ENTER, NUM_4, NUM_5, NUM_6,
            LSHIFT, Z, X, C, V, B, N, M, COMMA, DOT, SLASH, RSHIFT, UP, NUM_1, NUM_2, NUM_3, NUM_ENTER,
            LCTRL, LSUPER, LALT, SPACE, RALT, RSUPER, MENU, RCTRL, LEFT, DOWN, RIGHT, NUM_0, NUM_DOT;
            
            static std::vector<const char*> NAME;
            
            // Public members
            const char* name;
            const INDEX_TYPE i;
            
            static INDEX_TYPE count;
            static std::vector<KEY> keymap[6][20];
            //KEY operator[] (INDEX_TYPE i);
        private:
            KEY() = delete;
            KEY(const char* name);
    };
}


#endif /* DATATYPES_HPP */

