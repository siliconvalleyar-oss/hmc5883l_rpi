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

void SSD1306_OLED::setCursor([[maybe_unused]] uint8_t x, [[maybe_unused]] uint8_t y) {
}

void SSD1306_OLED::drawPixel([[maybe_unused]] uint8_t x, [[maybe_unused]] uint8_t y, [[maybe_unused]] bool color) {
}

uint8_t SSD1306_OLED::getWidth() const {
    return m_width;
}

uint8_t SSD1306_OLED::getHeight() const {
    return m_height;
}

}
