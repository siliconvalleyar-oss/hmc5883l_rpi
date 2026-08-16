# SECURITY.md

## Security

### Privileges
- The application requires root privileges to access `/dev/mem` via bcm2835.
- Do not run untrusted code as root.

### SPI Isolation
- SPI bus is shared. Ensure chip select pins are unique per device.
- CS polarity is set to LOW (active).

### Data Integrity
- Magnetometer data is raw; no cryptographic signing required for local use.
- If transmitting data externally, implement authentication.

### Updates
- Keep Raspberry Pi OS updated: `sudo apt-get update && sudo apt-get upgrade`.
- Monitor BCM2835 library security advisories.
