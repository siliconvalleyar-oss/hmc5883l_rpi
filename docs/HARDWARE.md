# HARDWARE.md

## Hardware

### HMC5883L Magnetometer
- Supply voltage: 3.3V DC
- Interface: SPI (up to 10 MHz)
- Resolution: 12-bit ADC
- Range: +/- 8.1 Gauss (default 1.3 Ga)

### Raspberry Pi SPI Pins
| Pin | GPIO | Function |
|-----|------|----------|
| 19  | 10   | MOSI     |
| 21  | 9    | MISO     |
| 23  | 11   | SCLK     |
| 24  | 8    | CE0      |

### Power
- Max current: ~5 mA
- Use 3.3V rail (not 5V).
