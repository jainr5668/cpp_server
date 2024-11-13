#include "server.h"
#include <fcntl.h>
#include <memory>
#include <sys/time.h>

Server::Server(std::unique_ptr<IRouter> router_)
{
   router = std::move(router_);
}
void Server::addHandler(Route route)
{
   router->addRoute(route);
}

std::string Server::read_request(int socket)
{
   const int BufferSize = 1024;
   std::vector<char> buffer(BufferSize);
   std::string requestData;

   while (true)
   {
      const ssize_t bytesRead = recv(socket, buffer.data(), BufferSize, 0);
      if (bytesRead < 0)
      {
         throw std::runtime_error("Error receiving data");
      }
      else if (bytesRead == 0)
      {
         // Connection closed
         break;
      }

      requestData.append(buffer.data(), bytesRead);

      if (bytesRead < BufferSize)
      {
         // No more data to read
         break;
      }
   }

   return requestData;
}
void Server::start()
{

   int server_fd, new_socket;
   struct sockaddr_in address;
   int opt = 1;
   int addrlen = sizeof(address);

   // Creating socket file descriptor
   if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
   {
      perror("socket failed");
      exit(EXIT_FAILURE);
   }

   // Attach socket to the port 8080
   if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
   {
      perror("setsockopt");
      exit(EXIT_FAILURE);
   }
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(PORT);

   if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
   {
      perror("bind failed");
      exit(EXIT_FAILURE);
   }

   if (listen(server_fd, 3) < 0)
   {
      perror("listen");
      exit(EXIT_FAILURE);
   }
   running = true;
   logger.info("Server listning on port " + std::to_string(PORT));

   while (running)
   {
      // Accept incoming connection
      if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
      {
         perror("accept");
         exit(EXIT_FAILURE);
      }

      std::string raw_request = read_request(new_socket);
      Request *req = new Request(raw_request);
      Response *res = new Response();
      if (req->path == "/stopServer"){
         stop();
         continue;
      }
      std::string reqPath = req->path;
      logger.info("Start Processing request: " + reqPath + " Method: " + req->method);
      try
      {
         router->handle_request(req, res);
      }
      catch (const std::exception &e)
      {
         res->status_code = 500;
         res->body = "{\"error\": \"" + std::string(e.what()) + "\"}";
      }
      logger.info("Stop Processing request: " + reqPath + " Method: " + req->method);
      send(new_socket, res->to_string().c_str(), res->to_string().length(), 0);
      close(new_socket);
      if(req)
      {
         delete req;
      } 
      if(res)
      {
      delete res;}
   }
}
void Server::stop()
{
   running = false;
   std::cout << "Server stopped..." << std::endl;
}