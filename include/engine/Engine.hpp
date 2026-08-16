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
    std::string getStatus() const;

private:
    bool m_running;
    std::unique_ptr<HMC5883L> m_magnetometer;
    std::string m_status;
};

}

#endif
