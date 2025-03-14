#pragma once

#include "ServerTypes.h"

namespace Server
{
    class IServer
    {
    public:
        virtual bool addRoute(Server::ServerTypes::Route route) = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
    };
}
