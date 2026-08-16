# ARCHITECTURE.md

## Architecture

The application follows a layered architecture:

- **Core Layer**: Application lifecycle (`App`), logging (`Logger`).
- **Engine Layer**: Business logic (`Engine`), sensor processing loop.
- **Driver Layer**: Hardware abstraction (`HMC5883L`, `SSD1306_OLED`).
- **Configuration Layer**: INI-style config files parsed by nlohmann/json.

Communication flow:
`main.cpp` → `core::App` → `engine::Engine` → `drivers::HMC5883L` → `bcm2835` SPI.
