# DEPLOY.md

## Deployment

### Target Device
- Raspberry Pi 2W or Pi 4
- Raspberry Pi OS (Debian-based)

### Steps
1. Build on device or cross-compile.
2. Copy `bin/App`, `config/`, and `scripts/` to target.
3. Run `sudo ./scripts/install_deps.sh` if needed.
4. Execute with `sudo ./bin/App`.

### Systemd Service (optional)
Create `/etc/systemd/system/hmc5883l.service`:
```
[Unit]
Description=HMC5883L SPI App

[Service]
ExecStart=/usr/local/bin/App
WorkingDirectory=/opt/hmc5883l
Restart=always
User=root

[Install]
WantedBy=multi-user.target
```
