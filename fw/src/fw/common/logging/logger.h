#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <fstream>

class Logger {
    public:
        void info(std::string message);
        void error(std::string message);
    private:
        static int logCount;
        static std::ofstream logFile;
        void flushLog(std::string logMessage);
};
#endif // LOGGER_H
