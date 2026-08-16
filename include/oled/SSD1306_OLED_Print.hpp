#ifndef OLED_SSD1306_OLED_PRINT_HPP_
#define OLED_SSD1306_OLED_PRINT_HPP_

#include "SSD1306_OLED.hpp"
#include <string>

namespace oled {

class SSD1306_OLED_Print {
public:
    static void print(SSD1306_OLED& display, const std::string& text);
    static void println(SSD1306_OLED& display, const std::string& text);
};

}

#endif
