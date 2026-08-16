#ifndef CORE_LOGGER_HPP_
#define CORE_LOGGER_HPP_

#include <string>
#include <fstream>
#include <mutex>

namespace core {

class Logger {
public:
    enum class Level {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    static Logger& instance();

    void setLogFile(const std::string& path);
    void setLevel(Level level);
    void log(Level level, const std::string& message);

    void debug(const std::string& msg);
    void info(const std::string& msg);
    void warn(const std::string& msg);
    void error(const std::string& msg);

private:
    Logger() = default;
    std::string levelToString(Level level) const;

    std::ofstream m_file;
    std::mutex m_mutex;
    Level m_level = Level::INFO;
};

}

#endif
