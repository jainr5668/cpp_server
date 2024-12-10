#ifndef RESPONSE_H
#define RESPONSE_H
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
class Response {
public:
    int status_code;
    std::unordered_map<std::string, std::string> headers;
    std::string body;

    Response() : status_code(200) {
        headers["Content-Type"] = "application/json";
    }

    std::string to_string() const {
        std::ostringstream oss;
        oss << "HTTP/1.1 " << status_code << " " << get_status_text() << "\r\n";
        for (const auto& header : headers) {
            oss << header.first << ": " << header.second << "\r\n";
        }
        oss << "Content-Length: " << body.length() << "\r\n";
        oss << "\r\n";
        oss << body;
        return oss.str();
    }

private:
    std::string get_status_text() const {
        switch (status_code) {
            case 200: return "OK";
            case 201: return "Created";
            case 204: return "No Content";
            case 400: return "Bad Request";
            case 401: return "Unauthorized";
            case 403: return "Forbidden";
            case 404: return "Not Found";
            case 405: return "Method Not Allowed";
            case 409: return "Conflict";
            case 500: return "Internal Server Error";
            default: return "Unknown";
        }
    }
};
#endif // RESPONSE_H
