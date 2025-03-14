#include "Server.h"
#include <vector>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <stdexcept>
#include <iostream>

#include "RequestContent.h"
#include "ResponseContent.h"

using RequestContent = Server::RequestContent;
using ResponseContent = Server::ResponseContent;

namespace Server
{
    bool Server::addRoute(ServerTypes::Route route)
    {
        return false;
    }

    std::string Server::readRequest(int socket)
    {
        const int BufferSize = 1024;
        std::vector<char> buffer(BufferSize);
        std::string requestData;
        while(true)
        {
            const ssize_t bytesRead = recv(socket, buffer.data(), buffer.size(), 0);
            if (bytesRead < 0)
            {
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
        return requestData;
    }

    void Server::handlerThread(int socket)
    {
        std::string requestData = readRequest(socket);
        RequestContent *request = new RequestContent(requestData);
        ResponseContent *response = new ResponseContent();
        std::cout << "Request Route: " << request->getRoute() <<" Method: " << request->getMethod() << std::endl;
        for (auto header : request->getHeaders())
        {
            std::cout << header.first << ": " << header.second << std::endl;
        }
        for (auto param : request->getQueryParameters())
        {
            std::cout << param.first << ": " << param.second << std::endl;
        }
        // std::string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello World!";
        response->setStatusCode(200);
        response->setBody("Hello World! from Ravi");
        auto serverResponse = response->getServerResponse();
        send(socket, serverResponse.c_str(), serverResponse.size(), 0);
        delete request;
        delete response;
        close(socket);
    }

    void Server::start()
    {
        int server_fd, new_socket;
        struct sockaddr_in address;
        int addrlen = sizeof(address);
        int opt = 1;
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            throw std::runtime_error("Failed to create socket");
            exit(EXIT_FAILURE);
        }
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        {
            throw std::runtime_error("Failed to set socket options");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        {
            throw std::runtime_error("Failed to bind socket");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0)
        {
            throw std::runtime_error("Failed to listen on socket");
            exit(EXIT_FAILURE);
        }
        isRunning = true;
        while (isRunning)
        {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
            {
                throw std::runtime_error("Failed to accept connection");
                exit(EXIT_FAILURE);
            }
            if (new_socket < 0)
            {
                throw std::runtime_error("Failed to accept connection");
                exit(EXIT_FAILURE);
            }
            // handlerThread(new_socket);
            std::thread handler(&Server::handlerThread, this, new_socket);
            handler.detach();
        }
    }

    void Server::stop()
    {
        isRunning = false;
    }
} // namespace Server