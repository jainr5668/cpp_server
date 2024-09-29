#pragma once
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