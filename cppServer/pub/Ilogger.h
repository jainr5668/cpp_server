#pragma once

#include <iostream>
#include <string>

namespace Server
{
    class Ilogger
    {
        public:
        virtual void debug(const std::string& message) = 0;
        virtual void error(const std::string& message) = 0;
        virtual void warning(const std::string& message) = 0;
        virtual void info(const std::string& message) = 0;
    }; // namespace Ilogger
} // namespace Server
