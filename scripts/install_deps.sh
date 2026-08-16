#!/bin/bash
# ==============================================================================
# install_deps.sh - Dependency installer for Raspberry Pi OS (Debian)
# ==============================================================================

set -e

echo "=== Installing dependencies for HMC5883L SPI App ==="

echo "[1/4] Updating package lists..."
sudo apt-get update -y

echo "[2/4] Installing build tools..."
sudo apt-get install -y g++ make

echo "[3/4] Installing BCM2835 library..."
sudo apt-get install -y libbcm2835-dev

echo "[4/4] Enabling SPI interface..."
if ! grep -q "dtparam=spi=on" /boot/config.txt; then
    echo "Enabling SPI in /boot/config.txt..."
    echo "dtparam=spi=on" | sudo tee -a /boot/config.txt
else
    echo "SPI already enabled in /boot/config.txt"
fi

echo ""
echo "=== Dependencies installed successfully ==="
echo "Please reboot if SPI was just enabled:"
echo "  sudo reboot"
