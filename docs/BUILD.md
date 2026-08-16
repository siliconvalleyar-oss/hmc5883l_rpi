# BUILD.md

## Build Instructions

### Native Build
```bash
make
```

### Cross Compile (x86_64 → arm64)
```bash
make CROSS_COMPILE=aarch64-linux-gnu-
```

### Clean
```bash
make clean
make distclean
```

### Dependencies
- g++ (C++17)
- make
- bcm2835 library
- nlohmann/json.hpp (header-only, included)
