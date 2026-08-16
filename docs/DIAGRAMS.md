# DIAGRAMS.md

## Diagrams

### SPI Connection
```
Raspberry Pi        HMC5883L
   CE0 (GPIO8)  ---  CS
   SCLK (GPIO11) --- SCL
   MOSI (GPIO10) --- SDA
   MISO (GPIO9)  --- SDO
   3.3V         --- VCC
   GND          --- GND
```

### Software Flow
```
main.cpp
  -> core::App::init()
       -> bcm2835_init()
       -> engine::Engine::init()
            -> HMC5883L::begin()
            -> HMC5883L::calibrate()
  -> core::App::run()
       -> engine::Engine::process()
            -> HMC5883L::readData()
```
