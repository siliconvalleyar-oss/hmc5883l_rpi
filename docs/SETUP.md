# SETUP.md

## Setup Guide

### 1. Hardware Setup
Connect HMC5883L to Raspberry Pi SPI pins as described in `docs/HARDWARE.md`.

### 2. Enable SPI
```bash
sudo raspi-config
# Interface Options -> SPI -> Enable
sudo reboot
```

### 3. Install Dependencies
```bash
sudo ./scripts/install_deps.sh
```

### 4. Build
```bash
make
```

### 5. Run
```bash
sudo ./bin/App
```
