#pragma once

#include "ServerTypes.h"
#include "IRouter.h"
#include <memory>

namespace Server
{
    class IServer
    {
    public:
        virtual void setRouter(std::shared_ptr<IRouter> router) = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
    };
}
