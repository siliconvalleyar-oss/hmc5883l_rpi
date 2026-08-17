#include "engine/Engine.hpp"
#include "core/Logger.hpp"
#include <cmath>
#include <ctime>

namespace engine {

Engine::Engine()
    : m_running(false), m_simulated(false), m_simulated_heading(0.0f), m_last_heading(0.0f) {
    m_last_data.x = 0;
    m_last_data.y = 0;
    m_last_data.z = 0;
}

Engine::~Engine() {
    stop();
}

bool Engine::init() {
    core::Logger::instance().info("Engine init: starting magnetometer...");

    m_magnetometer = std::make_unique<HMC5883L>(BCM2835_SPI_CS0);
    if (!m_magnetometer->begin()) {
        core::Logger::instance().warn("HMC5883L not detected. Continuing in SIMULATED mode.");
        m_simulated = true;
        m_status = "Simulated mode";
        return true;
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
    if (m_magnetometer && !m_simulated) {
        m_magnetometer->end();
    }
    core::Logger::instance().info("Engine stopped.");
}

void Engine::process() {
    if (!m_running) {
        return;
    }

    if (m_simulated) {
        simulateData();
        return;
    }

    if (!m_magnetometer) {
        return;
    }

    if (m_magnetometer->isDataReady()) {
        HMC5883L::MagData data = m_magnetometer->readData();
        float bx = m_magnetometer->getGaussX(data.x);
        float by = m_magnetometer->getGaussY(data.y);
        m_last_data = data;
        m_last_heading = std::atan2(by, bx) * 180.0f / 3.14159265f;
        if (m_last_heading < 0.0f) {
            m_last_heading += 360.0f;
        }
        publishHeading(m_last_heading);
    }
}

void Engine::simulateData() {
    static float phase = 0.0f;
    phase += 0.02f;
    if (phase > 360.0f) {
        phase -= 360.0f;
    }

    float heading = phase + (std::sin(phase * 0.1f) * 10.0f);
    if (heading < 0.0f) {
        heading += 360.0f;
    }
    if (heading >= 360.0f) {
        heading -= 360.0f;
    }

    m_last_heading = heading;
    m_last_data.x = static_cast<int16_t>(std::cos(heading * 3.14159265f / 180.0f) * 500);
    m_last_data.y = static_cast<int16_t>(std::sin(heading * 3.14159265f / 180.0f) * 500);
    m_last_data.z = 0;

    publishHeading(heading);
}

void Engine::publishHeading(float heading) {
    m_status = "Heading: " + std::to_string(static_cast<int>(std::round(heading))) + " deg";
}

bool Engine::isRunning() const {
    return m_running;
}

bool Engine::isSimulated() const {
    return m_simulated;
}

std::string Engine::getStatus() const {
    return m_status;
}

HMC5883L::MagData Engine::getMagData() const {
    return m_last_data;
}

float Engine::getHeading() const {
    return m_last_heading;
}

}
