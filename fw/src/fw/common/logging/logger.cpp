#include "logger.h"
#include <string>
#include <sstream>
#include <iomanip>
int Logger::logCount = 1;
std::ofstream Logger::logFile("main.log");

std::string zfill(const std::string& str, size_t width, char fill = '0') {
    std::ostringstream oss;
    oss << std::setw(width) << std::setfill(fill) << str;
    return oss.str();
}

void Logger::flushLog(std::string logMessage){
    std::cout << logMessage << std::endl;
    Logger::logFile << logMessage << std::endl;
}

void Logger::info(std::string message) {
    std::string logMessage = "[" + zfill(std::to_string(Logger::logCount++), 10) + "] INFO: " + message;
    flushLog(logMessage);
}

void Logger::error(std::string message) {
    std::string logMessage = "[" + zfill(std::to_string(Logger::logCount++), 10) + "] ERROR: " + message;
    flushLog(logMessage);
}
