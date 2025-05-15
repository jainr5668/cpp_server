#include "logger.h"

int Server::Logger::logCount = 1;
namespace Server
{
    void Logger::debug(const std::string& message)
    {
        std::cout << logCount++ << " [DEBUG] " << message << std::endl;
    }

    void Logger::error(const std::string& message)
    {
        std::cerr << logCount++ << " [ERROR] " << message << std::endl;
    }

    void Logger::warning(const std::string& message)
    {
        std::cerr << logCount++ << " [WARNING] " << message << std::endl;
    }

    void Logger::info(const std::string& message)
    {
        std::cout << logCount++ << " [INFO] " << message << std::endl;
    }
} // namespace Server