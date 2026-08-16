#include "core/App.hpp"
#include "core/Logger.hpp"
#include <iostream>

int main() {
    std::cout << "=== HMC5883L SPI Application ===" << std::endl;

    core::App app;
    if (!app.init(0, nullptr)) {
        std::cerr << "Failed to initialize application." << std::endl;
        return 1;
    }

    int result = app.run();
    app.shutdown();
    return result;
}
