# TESTING.md

## Testing

### Build Test
```bash
make
```

### Runtime Test
```bash
sudo ./bin/App
```

### Manual Test Cases
1. **Sensor Detection**: App reports HMC5883L connected.
2. **Calibration**: App calibrates and prints "Calibration complete."
3. **Readings**: App outputs X, Y, Z and heading continuously.
4. **Shutdown**: Ctrl+C stops the app cleanly.

### Automated Testing (Future)
- Unit tests for `drivers::HMC5883L` using mocked SPI.
- Integration tests on hardware with pytest or bash scripts.
