# ARCHITECTURE.md

## Architecture

The application follows a layered architecture:

- **Core Layer**: Application lifecycle (`App`), logging (`Logger`).
- **Engine Layer**: Business logic (`Engine`), sensor processing loop.
- **Driver Layer**: Hardware abstraction (`HMC5883L`, `SSD1306_OLED`).
- **Configuration Layer**: INI-style config files parsed by nlohmann/json.

Communication flow:
`main.cpp` → `core::App` → `engine::Engine` → `drivers::HMC5883L` → `bcm2835` SPI.
# ARQUITECTURA.md

## Arquitectura

La aplicación sigue una arquitectura por capas:

- **Núcleo (core)**: Ciclo de vida de la aplicación (`App`), logging (`Logger`).
- **Motor (engine)**: Lógica de negocio (`Engine`), bucle de procesamiento del sensor.
- **Drivers**: Abstracción de hardware (`HMC5883L`, `SSD1306_OLED`).
- **Configuración**: Archivos de configuración en formato INI/JSON.

Flujo de comunicación:
`main.cpp` → `core::App` → `engine::Engine` → `drivers::HMC5883L` → SPI bcm2835.
