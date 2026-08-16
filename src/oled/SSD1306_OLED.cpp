#include "oled/SSD1306_OLED.hpp"

namespace oled {

SSD1306_OLED::SSD1306_OLED(uint8_t address)
    : m_address(address), m_width(128), m_height(64), m_buffer(nullptr) {
}

bool SSD1306_OLED::begin() {
    return true;
}

void SSD1306_OLED::clear() {
}

void SSD1306_OLED::display() {
}

void SSD1306_OLED::setCursor(uint8_t x, uint8_t y) {
}

void SSD1306_OLED::drawPixel(uint8_t x, uint8_t y, bool color) {
}

uint8_t SSD1306_OLED::getWidth() const {
    return m_width;
}

uint8_t SSD1306_OLED::getHeight() const {
    return m_height;
}

}
