#pragma once
#include "Ilogger.h"

namespace Server
{
    class Logger : public Ilogger
    {
        public:
        void debug(const std::string& message) override;
        void error(const std::string& message) override;
        void info(const std::string& message) override;
        void warning(const std::string& message) override;
        static int logCount;
        private:
    };
} // namespace Server
