# DESING.md

## Design Notes

- SPI Mode 0 (CPOL=0, CPHA=0).
- MSB-first bit order.
- 8x oversampling for noise reduction.
- Continuous mode for steady readings.
- Calibration runs once at startup; offsets stored in memory.
- Thread-safe logging via mutex.
- Signal-safe shutdown via global app pointer.
