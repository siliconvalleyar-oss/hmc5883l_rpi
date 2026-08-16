#ifndef CORE_APP_HPP_
#define CORE_APP_HPP_

#include <string>
#include <memory>
#include "engine/Engine.hpp"
#include "drivers/HMC5883L.hpp"

namespace core {

class App {
public:
    App();
    ~App();

    bool init(int argc, char* argv[]);
    int run();
    void shutdown();

private:
    bool loadConfig();
    bool initHardware();
    bool initEngine();

    std::string m_configPath;
    std::string m_hardwareConfigPath;
    std::unique_ptr<engine::Engine> m_engine;
    bool m_running;
};

}

#endif
