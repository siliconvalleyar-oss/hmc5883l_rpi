#ifndef OLED_SSD1306_OLED_GRAPHICS_HPP_
#define OLED_SSD1306_OLED_GRAPHICS_HPP_

#include "SSD1306_OLED.hpp"

namespace oled {

class SSD1306_OLED_graphics {
public:
    static void drawLine(SSD1306_OLED& display, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color);
    static void drawRect(SSD1306_OLED& display, uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color);
    static void drawCircle(SSD1306_OLED& display, uint8_t x0, uint8_t y0, uint8_t r, bool color);
};

}

#endif
