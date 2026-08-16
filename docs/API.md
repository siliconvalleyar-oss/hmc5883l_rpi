# API.md

## API Reference

### core::App
- `bool init(int argc, char* argv[])`
- `int run()`
- `void shutdown()`

### core::Logger
- `static Logger& instance()`
- `void setLogFile(const std::string& path)`
- `void setLevel(Level level)`
- `void debug/info/warn/error(const std::string& msg)`

### engine::Engine
- `bool init()`
- `void start()`
- `void stop()`
- `void process()`
- `bool isRunning() const`
- `std::string getStatus() const`

### drivers::HMC5883L
- `bool begin()`
- `void end()`
- `MagData readData()`
- `bool isDataReady()`
- `void calibrate(uint16_t samples)`
- `float getGaussX/Y/Z(int16_t raw)`

### oled::SSD1306_OLED
- `bool begin()`
- `void clear()`
- `void display()`
- `void setCursor(uint8_t x, uint8_t y)`
- `void drawPixel(uint8_t x, uint8_t y, bool color)`
