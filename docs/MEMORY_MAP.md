# MEMORY_MAP.md

## Memory Map

### HMC5883L Registers
| Address | Name      | R/W | Description                     |
|---------|-----------|-----|---------------------------------|
| 0x00    | DATA_X_H  | R   | Data output X MSB               |
| 0x01    | DATA_X_L  | R   | Data output X LSB               |
| 0x02    | DATA_Z_H  | R   | Data output Z MSB               |
| 0x03    | DATA_Z_L  | R   | Data output Z LSB               |
| 0x04    | DATA_Y_H  | R   | Data output Y MSB               |
| 0x05    | DATA_Y_L  | R   | Data output Y LSB               |
| 0x06    | STATUS    | R   | Status register                 |
| 0x07    | ID_A      | R   | Identification register A       |
| 0x08    | ID_B      | R   | Identification register B       |
| 0x09    | ID_C      | R   | Identification register C       |
| 0x0A    | CONFIG_A  | R/W | Configuration register A        |
| 0x0B    | CONFIG_B  | R/W | Configuration register B (gain) |
| 0x0C    | MODE      | R/W | Mode register                   |

### BCM2835 Peripherals
- SPI: Physical base 0x20204000 (ARM side) / 0x7E204000 (bus side)
- Managed by bcm2835 library; no direct memory access in user code.
