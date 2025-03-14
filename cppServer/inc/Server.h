#pragma once

#include "IServer.h"
#include "ServerTypes.h"

namespace Server
{
    class Server : public IServer
    {
    public:
        Server() = default;
        ~Server() = default;
        bool addRoute(ServerTypes::Route route) override;
        void start() override;
        void stop() override;
    private:
        void *impl;
        int port = 8080;
        int intitalBufferSize = 1024;
        bool isRunning = false;
        void handlerThread(int socket);
        std::string readRequest(int socket);
    };
} // namespace Server
