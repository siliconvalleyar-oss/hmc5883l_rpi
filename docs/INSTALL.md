# INSTALL.md

## Installation

### Prerequisites
- Raspberry Pi OS (Debian)
- Internet connection

### Steps
```bash
# Clone repo
cd /opt
sudo git clone <repo> hmc5883l
cd hmc5883l

# Install dependencies
sudo ./scripts/install_deps.sh

# Build
make

# Run
sudo ./bin/App
```

### Manual Dependency Installation
```bash
sudo apt-get update
sudo apt-get install -y g++ make libbcm2835-dev
```

### Enable SPI
```bash
sudo raspi-config
# Interface Options -> SPI -> Enable
sudo reboot
```
