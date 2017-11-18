/* 
 * File:   DataTypes.cpp
 * Author: chlorek
 * 
 * Created on October 10, 2016, 8:03 PM
 */

#include "DataTypes.hpp"

namespace clkb {
    KEY::INDEX_TYPE KEY::count = 0;
    std::vector<const char*> KEY::NAME(111);

    KEY::KEY(const char* name) : name(name), i(count) {
        ++count;
        KEY::NAME[i] = name;
    }
    
    const KEY KEY::BRIGHTNESS{"light"}, KEY::WINLOCK{"lock"}, KEY::MUTE{"mute"}, KEY::ESC{"esc"}, KEY::F1{"f1"}, KEY::F2{"f2"}, KEY::F3{"f3"}, KEY::F4{"f4"}, KEY::F5{"f5"},
        KEY::F6{"f6"}, KEY::F7{"f7"}, KEY::F8{"f8"}, KEY::F9{"f9"}, KEY::F10{"f10"}, KEY::F11{"f11"}, KEY::F12{"f12"},
        KEY::PRINT_SCREEN{"prtscn"}, KEY::SCROLL_LOCK{"scroll"}, KEY::PAUSE{"pause"}, KEY::MEDIA_STOP{"stop"}, KEY::MEDIA_PREV{"prev"},
        KEY::MEDIA_PAUSE{"play"}, KEY::MEDIA_NEXT {"next"}, KEY::GRAVE{"grave"}, KEY::ONE {"1"}, KEY::TWO {"2"}, KEY::THREE{"3"}, KEY::FOUR{"4"},
        KEY::FIVE{"5"}, KEY::SIX{"6"}, KEY::SEVEN{"7"}, KEY::EIGHT{"8"}, KEY::NINE{"9"}, KEY::ZERO{"0"}, KEY::MINUS{"minus"}, KEY::EQUAL{"equal"},
        KEY::BACKSPACE {"bspace"}, KEY::INSERT{"ins"}, KEY::HOME{"home"}, KEY::PAGE_UP{"pgup"}, KEY::NUMLOCK{"numlock"}, KEY::NUM_DIV{"numslash"},
        KEY::NUM_MUL("numstar"), KEY::NUM_MIN{"numminus"}, KEY::TAB{"tab"}, KEY::Q{"q"}, KEY::W{"w"}, KEY::E{"e"}, KEY::R{"r"}, KEY::T{"t"}, KEY::Y{"y"},
        KEY::U{"u"}, KEY::I{"i"}, KEY::O{"o"}, KEY::P{"p"}, KEY::LBRACE{"lbrace"}, KEY::RBRACE{"rbrace"}, KEY::BACKSLASH{"bslash"},
        KEY::DELETE{"del"}, KEY::END{"end"}, KEY::PAGE_DOWN{"pgdn"}, KEY::NUM_7{"num7"}, KEY::NUM_8{"num8"}, KEY::NUM_9{"num9"}, KEY::NUM_PLUS{"numplus"},
        KEY::CAPS_LOCK{"caps"}, KEY::A{"a"}, KEY::S{"s"}, KEY::D{"d"}, KEY::F{"f"}, KEY::G{"g"}, KEY::H{"h"}, KEY::J{"j"}, KEY::K{"k"}, KEY::L{"l"},
        KEY::SEMICOLON{"colon"}, KEY::APOSTROPHE{"quote"}, KEY::ENTER{"enter"}, KEY::NUM_4{"num4"}, KEY::NUM_5{"num5"}, KEY::NUM_6{"num6"},
        KEY::LSHIFT{"lshift"}, KEY::Z{"z"}, KEY::X{"x"}, KEY::C{"c"}, KEY::V{"v"}, KEY::B{"b"}, KEY::N{"n"}, KEY::M{"m"}, KEY::COMMA{"comma"}, KEY::DOT{"dot"},
        KEY::SLASH{"slash"}, KEY::RSHIFT{"rshift"}, KEY::UP{"up"}, KEY::NUM_1{"num1"}, KEY::NUM_2{"num2"}, KEY::NUM_3{"num3"}, KEY::NUM_ENTER{"numenter"},
        KEY::LCTRL{"lctrl"}, KEY::LSUPER{"lwin"}, KEY::LALT{"lalt"}, KEY::SPACE{"space"}, KEY::RALT{"ralt"}, KEY::RSUPER{"rwin"},
        KEY::MENU{"rmenu"}, KEY::RCTRL{"rctrl"}, KEY::LEFT{"left"}, KEY::DOWN{"down"}, KEY::RIGHT{"right"}, KEY::NUM_0{"num0"}, KEY::NUM_DOT{"numdot"};
        
    std::vector<KEY> KEY::keymap[6][20] {
        {{KEY::ESC}, {KEY::F1}, {KEY::F2}, {KEY::F3}, {KEY::F4}, {KEY::F5}, {KEY::F6}, {KEY::F7}, {KEY::F8}, {}, {KEY::F9}, {KEY::F10}, {KEY::F11, KEY::F12}, {KEY::PRINT_SCREEN}, {KEY::SCROLL_LOCK}, {KEY::PAUSE}, {KEY::MEDIA_STOP}, {KEY::MEDIA_PREV}, {KEY::MEDIA_PAUSE}, {KEY::MEDIA_NEXT}},
        {{KEY::GRAVE}, {KEY::ONE, KEY::TWO}, {KEY::THREE}, {KEY::FOUR}, {KEY::FIVE}, {KEY::SIX}, {KEY::SEVEN}, {KEY::EIGHT}, {KEY::NINE}, {KEY::ZERO}, {KEY::MINUS}, {KEY::EQUAL}, {KEY::BACKSPACE}, {KEY::INSERT}, {KEY::HOME}, {KEY::PAGE_UP}, {KEY::NUMLOCK}, {KEY::NUM_DIV}, {KEY::NUM_MUL}, {KEY::NUM_MIN}},
        {{KEY::TAB}, {KEY::Q}, {KEY::W}, {KEY::E}, {KEY::R, KEY::T}, {KEY::Y}, {KEY::U}, {KEY::I}, {KEY::O}, {KEY::P}, {KEY::LBRACE}, {KEY::RBRACE}, {KEY::BACKSLASH}, {KEY::DELETE}, {KEY::END}, {KEY::PAGE_DOWN}, {KEY::NUM_7}, {KEY::NUM_8}, {KEY::NUM_9}, {}},
        {{KEY::CAPS_LOCK}, {KEY::A}, {KEY::S}, {KEY::D}, {KEY::F}, {KEY::G, KEY::H}, {KEY::J}, {KEY::K}, {KEY::L}, {KEY::SEMICOLON}, {KEY::APOSTROPHE}, {}, {KEY::ENTER}, {}, {}, {}, {KEY::NUM_4}, {KEY::NUM_5}, {KEY::NUM_6}, {KEY::NUM_PLUS}},
        {{KEY::LSHIFT}, {KEY::Z}, {KEY::X}, {KEY::C}, {KEY::V}, {KEY::B}, {KEY::N}, {KEY::M}, {KEY::COMMA}, {KEY::DOT}, {KEY::SLASH}, {}, {KEY::RSHIFT}, {}, {KEY::UP}, {}, {KEY::NUM_1}, {KEY::NUM_2}, {KEY::NUM_3}, {KEY::NUM_ENTER}},
        {{KEY::LCTRL}, {KEY::LSUPER, KEY::LALT}, {}, {}, {}, {KEY::SPACE}, {}, {}, {}, {KEY::RALT}, {KEY::RSUPER}, {KEY::MENU}, {KEY::RCTRL}, {KEY::LEFT}, {KEY::DOWN}, {KEY::RIGHT}, {KEY::NUM_0}, {}, {KEY::NUM_DOT}, {}}
    };
    
    std::vector<KEY> KEY::fromKeymap(unsigned char x, unsigned char y) {
        if(y < 6)
            if(x < 20)
                return KEY::keymap[y][x];
        return {};
    }
}