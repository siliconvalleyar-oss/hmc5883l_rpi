#include "core/App.hpp"
#include "core/Logger.hpp"
#include "nlohmann/json.hpp"
#include <iostream>
#include <cstdlib>
#include <unistd.h>

using json = nlohmann::json;

namespace core {

App::App()
    : m_running(false) {
}

App::~App() {
    shutdown();
}

bool App::init(int argc, char* argv[]) {
    core::Logger::instance().info("Initializing application...");

    if (!loadConfig()) {
        core::Logger::instance().error("Failed to load configuration.");
        return false;
    }

    if (!initHardware()) {
        core::Logger::instance().error("Failed to initialize hardware.");
        return false;
    }

    if (!initEngine()) {
        core::Logger::instance().error("Failed to initialize engine.");
        return false;
    }

    m_running = true;
    core::Logger::instance().info("Application initialized successfully.");
    return true;
}

int App::run() {
    if (!m_running) {
        return EXIT_FAILURE;
    }

    core::Logger::instance().info("Application running. Press Ctrl+C to stop.");

    while (m_running && m_engine && m_engine->isRunning()) {
        m_engine->process();
        usleep(50000);
    }

    return EXIT_SUCCESS;
}

void App::shutdown() {
    if (m_engine) {
        m_engine->stop();
    }
    m_running = false;
    core::Logger::instance().info("Application shutdown complete.");
}

bool App::loadConfig() {
    std::ifstream file(m_configPath);
    if (!file.is_open()) {
        core::Logger::instance().warn("Config file not found, using defaults.");
        return true;
    }

    try {
        json j;
        file >> j;
        core::Logger::instance().info("Configuration loaded from " + m_configPath);
    } catch (const std::exception& e) {
        core::Logger::instance().error("Error parsing config: " + std::string(e.what()));
        return false;
    }

    return true;
}

bool App::initHardware() {
    core::Logger::instance().info("Initializing hardware via BCM2835...");

    if (!bcm2835_init()) {
        core::Logger::instance().error("bcm2835_init() failed. Are you root?");
        return false;
    }

    bcm2835_spi_begin();
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, 0);

    core::Logger::instance().info("Hardware initialized.");
    return true;
}

bool App::initEngine() {
    core::Logger::instance().info("Initializing engine...");
    m_engine = std::make_unique<engine::Engine>();
    return m_engine->init();
}

}
