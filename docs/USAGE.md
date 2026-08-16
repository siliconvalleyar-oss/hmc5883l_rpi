# USAGE.md

## Usage

### Basic Run
```bash
sudo ./bin/App
```

### Expected Output
```
=== HMC5883L Application ===
[INFO] Initializing application...
[INFO] Hardware initialized.
[INFO] Engine init: starting magnetometer...
[INFO] Calibrating magnetometer...
[INFO] Calibration complete.
[INFO] Application running. Press Ctrl+C to stop.
[INFO] Heading: 123 deg
```

### Configuration
Edit `config/config.cfg` to change:
- Gain (0.88 to 8.1 Ga)
- Data rate (0.75 to 75 Hz)
- Samples average (1, 2, 4, 8)
- Operation mode (continuous, single-shot, idle)

### Calibration
The app calibrates automatically at startup. For best results:
1. Keep the sensor flat.
2. Rotate it slowly in all directions (figure-8 pattern).
3. Avoid ferromagnetic materials nearby.

### Stopping
Press `Ctrl+C` to trigger SIGINT and clean shutdown.
