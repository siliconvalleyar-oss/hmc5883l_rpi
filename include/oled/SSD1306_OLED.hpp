#ifndef OLED_SSD1306_OLED_HPP_
#define OLED_SSD1306_OLED_HPP_

#include <cstdint>
#include <string>

namespace oled {

class SSD1306_OLED {
public:
    SSD1306_OLED(uint8_t address = 0x3C);
    bool begin();
    void clear();
    void display();
    void setCursor(uint8_t x, uint8_t y);
    void drawPixel(uint8_t x, uint8_t y, bool color);
    uint8_t getWidth() const;
    uint8_t getHeight() const;

private:
    uint8_t m_address;
    uint8_t m_width;
    uint8_t m_height;
    uint8_t* m_buffer;
};

}

#endif
