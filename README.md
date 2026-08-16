# HMC5883L SPI Application

Aplicación en C++ para Raspberry Pi (2W / Pi 4) que lee el magnetómetro HMC5883L mediante bus SPI utilizando la librería BCM2835.

## Tabla de Contenidos

- [Descripción](#descripción)
- [Requisitos de Hardware](#requisitos-de-hardware)
- [Requisitos de Software](#requisitos-de-software)
- [Compilación e Instalación](#compilación-e-instalación)
- [Uso Básico](#uso-básico)
- [Arquitectura](#arquitectura)
- [Compatibilidad](#compatibilidad)
- [Configuración](#configuración)

## Descripción

Esta aplicación demuestra el uso de la librería BCM2835 para comunicarse con el sensor HMC5883L (brújula digital de 3 ejes) a través de SPI. Incluye calibración de offsets, conversión a Gauss y cálculo de heading.

## Requisitos de Hardware

- Raspberry Pi 2W o Raspberry Pi 4
- Módulo HMC5883L
- Conexiones SPI:
  - VCC → 3.3V
  - GND → GND
  - SDA → MOSI (GPIO10)
  - SCL → MISO (GPIO9)
  - CS → CE0 (GPIO8)

## Requisitos de Software

- Raspberry Pi OS (Debian)
- g++ con soporte C++17
- make
- bcm2835 library

## Compilación e Instalación

```bash
# Instalar dependencias
sudo ./scripts/install_deps.sh

# Compilar
make

# Ejecutar
sudo ./bin/App
```

## Uso Básico

Al ejecutar la aplicación, esta:
1. Inicializa la librería BCM2835.
2. Detecta el HMC5883L leyendo los registros de identificación.
3. Realiza una calibración automática (rotar el sensor).
4. Muestra lecturas X/Y/Z en crudo, valor en Gauss y heading en grados.

## Arquitectura

```
├── include/
│   ├── core/          - App, Logger
│   ├── drivers/       - HMC5883L.hpp
│   ├── engine/        - Engine.hpp
│   ├── libraries/     - nlohmann/json.hpp
│   └── oled/          - SSD1306 drivers (stub)
├── src/
│   ├── main.cpp       - Punto de entrada
│   ├── core/          - App.cpp, Logger.cpp
│   ├── engine/        - Engine.cpp
│   └── oled/          - OLED implementation (stub)
├── config/
│   ├── config.cfg     - Configuración de aplicación
│   └── hardware.cfg   - Configuración de hardware
├── bin/App            - Ejecutable final
└── Makefile           - Build system
```

## Compatibilidad

- **32-bit**: Raspberry Pi OS 32-bit (armhf)
- **64-bit**: Raspberry Pi OS 64-bit (arm64)

El Makefile detecta automáticamente la arquitectura y aplica los flags correspondientes (`-m32` o `-m64`). Para compilación cruzada, usar `make CROSS_COMPILE=aarch64-linux-gnu-`.

## Configuración

- `config/config.cfg` - Parámetros de la aplicación y sensor.
- `config/hardware.cfg` - Mapeo de pines y parámetros eléctricos.
