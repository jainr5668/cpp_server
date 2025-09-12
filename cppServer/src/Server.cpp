#include "Server.h"
#include <vector>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <stdexcept>
#include <iostream>
#include "IRouter.h"

#include "RequestContent.h"
#include "ResponseContent.h"

using RequestContent = Server::RequestContent;
using ResponseContent = Server::ResponseContent;
using RouteContext = Server::ServerTypes::RouteContext;

namespace Server
{

    std::string Server::readRequest(int socket)
    {
        logger.info("Server::readRequest - entering");
        const int BufferSize = 1024;
        std::vector<char> buffer(BufferSize);
        std::string requestData;
        while (true)
        {
            const ssize_t bytesRead = recv(socket, buffer.data(), buffer.size(), 0);
            if (bytesRead < 0)
            {
                logger.error("Error reading from socket");
                throw std::runtime_error("Error reading from socket");
            }
            else if (bytesRead == 0)
            {
                break;
            }
            requestData.append(buffer.data(), bytesRead);
            if (bytesRead < BufferSize)
            {
                break;
            }
        }
        logger.info("Server::readRequest - exiting");
        return requestData;
    }

    void Server::handlerThread(int socket)
    {
        logger.info("Server::handlerThread - entering");
        std::string requestData = readRequest(socket);
        RequestContent *request = new RequestContent(requestData);
        ResponseContent *response = new ResponseContent();
        logger.info("Request Route: " + request->getRoute() + " Method: " + request->getMethod());
        if (router)
        {
            RouteContext routeContext;
            routeContext.requestContext = request;
            routeContext.responseContext = response;
            router->routeHandler(routeContext);
        }
        else
        {
            response->setStatusCode(500);
            response->setBody("Initial Router is not set.");
        }
        logger.info("Response Status: " + std::to_string(response->getStatusCode()));
        auto serverResponse = response->getServerResponse();
        send(socket, serverResponse.c_str(), serverResponse.size(), 0);
        delete request;
        delete response;
        close(socket);
        logger.info("Server::handlerThread - exiting");
    }

    void Server::setRouter(std::shared_ptr<IRouter> router)
    {
        logger.info("Server::setRouter - entering");
        this->router = router;
        logger.info("Server::setRouter - exiting");
    }

    void Server::start()
    {
        logger.info("Server::start - entering");
        int server_fd, new_socket;
        struct sockaddr_in address;
        int addrlen = sizeof(address);
        int opt = 1;
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            logger.error("Failed to create socket");
            throw std::runtime_error("Failed to create socket");
            exit(EXIT_FAILURE);
        }
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        {
            logger.error("Failed to set socket options");
            throw std::runtime_error("Failed to set socket options");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        {
            logger.error("Failed to bind socket");
            throw std::runtime_error("Failed to bind socket");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0)
        {
            logger.error("Failed to listen on socket");
            throw std::runtime_error("Failed to listen on socket");
            exit(EXIT_FAILURE);
        }
        isRunning = true;
        logger.info("Server::start Server started on port: " + std::to_string(port));
        logger.info("Server::start Server URL: http://localhost:" + std::to_string(port));
        while (isRunning)
        {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
            {
                logger.error("Failed to accept connection");
                throw std::runtime_error("Failed to accept connection");
                exit(EXIT_FAILURE);
            }
            if (new_socket < 0)
            {
                logger.error("Failed to accept connection");
                throw std::runtime_error("Failed to accept connection");
                exit(EXIT_FAILURE);
            }
            std::thread handler(&Server::handlerThread, this, new_socket);
            handler.detach();
        }
        close(server_fd);
        logger.info("Server stopped");
        logger.info("Server::start - exiting");
    }

    void Server::stop()
    {
        logger.info("Server::stop - entering");
        isRunning = false;
        logger.info("Server::stop - exiting");
    }

} // namespace Server