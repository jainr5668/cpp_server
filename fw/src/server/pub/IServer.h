#ifndef ISERVER_H
#define ISERVER_H
#include "IRouter.h"
#include <string.h>

class IServer {
public:
   virtual void addHandler(Route route) = 0;
   virtual void start() = 0;
   virtual void stop() = 0;
};
#endif // ISERVER_H