#ifndef ENGINE_ENGINE_HPP_
#define ENGINE_ENGINE_HPP_

#include <string>
#include <memory>
#include "drivers/HMC5883L.hpp"

namespace engine {

class Engine {
public:
    Engine();
    ~Engine();

    bool init();
    void start();
    void stop();
    void process();

    bool isRunning() const;
    bool isSimulated() const;
    std::string getStatus() const;
    HMC5883L::MagData getMagData() const;
    float getHeading() const;

private:
    void simulateData();
    void publishHeading(float heading);

    bool m_running;
    bool m_simulated;
    std::unique_ptr<HMC5883L> m_magnetometer;
    std::string m_status;
    float m_simulated_heading;
    HMC5883L::MagData m_last_data;
    float m_last_heading;
};

}

#endif
