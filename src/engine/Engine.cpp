#include "engine/Engine.hpp"
#include "core/Logger.hpp"
#include <cmath>

namespace engine {

Engine::Engine()
    : m_running(false) {
}

Engine::~Engine() {
    stop();
}

bool Engine::init() {
    core::Logger::instance().info("Engine init: starting magnetometer...");

    m_magnetometer = std::make_unique<HMC5883L>(BCM2835_SPI_CS0);
    if (!m_magnetometer->begin()) {
        core::Logger::instance().error("Failed to initialize HMC5883L.");
        m_status = "HMC5883L init failed";
        return false;
    }

    core::Logger::instance().info("Calibrating magnetometer...");
    m_magnetometer->calibrate(100);
    core::Logger::instance().info("Calibration complete.");

    m_status = "Ready";
    return true;
}

void Engine::start() {
    m_running = true;
    core::Logger::instance().info("Engine started.");
}

void Engine::stop() {
    m_running = false;
    if (m_magnetometer) {
        m_magnetometer->end();
    }
    core::Logger::instance().info("Engine stopped.");
}

void Engine::process() {
    if (!m_running || !m_magnetometer) {
        return;
    }

    if (m_magnetometer->isDataReady()) {
        HMC5883L::MagData data = m_magnetometer->readData();
        float bx = m_magnetometer->getGaussX(data.x);
        float by = m_magnetometer->getGaussY(data.y);
        float bz = m_magnetometer->getGaussZ(data.z);

        float heading = std::atan2(by, bx) * 180.0f / 3.14159265f;
        if (heading < 0.0f) {
            heading += 360.0f;
        }

        m_status = "Heading: " + std::to_string(static_cast<int>(heading)) + " deg";
    }
}

bool Engine::isRunning() const {
    return m_running;
}

std::string Engine::getStatus() const {
    return m_status;
}

}
