#include "core/Logger.hpp"
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace core {

Logger& Logger::instance() {
    static Logger instance;
    return instance;
}

void Logger::setLogFile(const std::string& path) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_file.is_open()) {
        m_file.close();
    }
    m_file.open(path, std::ios::app);
}

void Logger::setLevel(Level level) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_level = level;
}

void Logger::log(Level level, const std::string& message) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (level < m_level) {
        return;
    }

    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    std::string timestamp = ss.str();

    std::string output = "[" + timestamp + "] " + levelToString(level) + ": " + message;

    if (m_file.is_open()) {
        m_file << output << std::endl;
    }

    std::cout << output << std::endl;
}

void Logger::debug(const std::string& msg) {
    log(Level::DEBUG, msg);
}

void Logger::info(const std::string& msg) {
    log(Level::INFO, msg);
}

void Logger::warn(const std::string& msg) {
    log(Level::WARN, msg);
}

void Logger::error(const std::string& msg) {
    log(Level::ERROR, msg);
}

std::string Logger::levelToString(Level level) const {
    switch (level) {
        case Level::DEBUG: return "DEBUG";
        case Level::INFO:  return "INFO";
        case Level::WARN:  return "WARN";
        case Level::ERROR: return "ERROR";
    }
    return "UNKNOWN";
}

}
