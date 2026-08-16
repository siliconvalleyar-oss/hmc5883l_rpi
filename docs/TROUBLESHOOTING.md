# TROUBLESHOOTING.md

## Troubleshooting

### bcm2835_init() failed
**Cause**: Not running as root or /dev/mem unavailable.  
**Fix**: Run with `sudo`.

### SPI not responding
**Cause**: SPI disabled in raspi-config.  
**Fix**: `sudo raspi-config` → Interface Options → SPI → Enable. Reboot.

### Sensor not detected
**Cause**: Wrong wiring or CS pin mismatch.  
**Fix**: Verify connections against `config/hardware.cfg`.

### Erratic readings
**Cause**: Missing calibration or electrical noise.  
**Fix**: Ensure calibration runs. Add decoupling capacitor near sensor.

### Build fails with "nlohmann/json.hpp: No such file"
**Cause**: Include path missing.  
**Fix**: Ensure `-Iinclude` is present in Makefile.

### Cross-compile fails
**Cause**: Missing sysroot or toolchain.  
**Fix**: Install `g++-aarch64-linux-gnu` and set `CROSS_COMPILE`.

### Binary crashes immediately
**Cause**: Running on non-BCM2835 hardware (e.g., x86 PC).  
**Fix**: Build and run on Raspberry Pi only.
