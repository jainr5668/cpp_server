#ifndef SERVER_H
#define SERVER_H
#include "IRouter.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <unordered_map>
#include <string.h>
#include <vector>
#include <cstring>
#include "logger.h"
#include "IServer.h"
#include <memory>

class Server : public IServer{
public:
   Server(std::unique_ptr<IRouter> router_);
   void addHandler(Route route);
   void start();
   void stop();
private:
   #define PORT 8080
   #define INITIAL_BUFFER_SIZE 1024
   std::unique_ptr<IRouter> router;
   bool running = false;
   Logger logger;
   std::string read_request(int socket);
};
#endif // SERVER_H