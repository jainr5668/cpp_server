#pragma once
#include "IResponseContent.h"
#include "logger.h"
#include <nlohmann/json.hpp>
#include <memory>
#include <fstream>

using IResponseContent = Server::IResponseContent;
using IAuthentication = Server::IAuthorization;
using Logger = Server::Logger;

namespace Server
{
    class ResponseContent : public IResponseContent
    {
    public:
        ResponseContent() = default;
        ResponseContent(std::string body, std::unordered_map<std::string, std::string> headers, int statusCode) : body(body), headers(headers), statusCode(statusCode) {};

        /**
         * @brief Creates a token using the payload provided
         *
         * @param payload std::unordered_map<std::string, std::string>
         * @return std::string
         */
        std::string createToken(const std::unordered_map<std::string, std::string> &payload);

        /**
         * @brief Gets the payload from the token provided
         *
         * @param token std::string
         * @return std::unordered_map<std::string, std::string>
         */
        std::unordered_map<std::string, std::string> getTokenPayload(std::string token);

        /**
         * @brief Gets the response body
         *
         * @returns std::string
         */
        std::string getBody() { return body; }

        /**
         * @brief Gets the response headers
         *
         * @returns std::unordered_map<std::string, std::string>
         */
        std::unordered_map<std::string, std::string> getHeaders() { return headers; }

        /**
         * @brief Gets the response status code
         *
         * @return int
         */
        int getStatusCode() { return statusCode; }

        /**
         * @brief Gets the server reaponse that has to be sent back to client
         *
         * @returns std::string
         */
        std::string getServerResponse();

        /**
         * @brief Sets the response body (string)
         * @param body std::string
         */
        void setBody(std::string body)
        {
            this->body = body;
        }

        /**
         * @brief Sets the response body (single char)
         * @param body char
         */
        void setBody(const char body)
        {
            this->body = std::to_string(body);
        }

        /**
         * @brief Sets the response body (integer)
         * @param body int
         */
        void setBody(int body)
        {
            this->body = std::to_string(body);
        }

        /**
         * @brief Sets the response body (long)
         * @param body long
         */
        void setBody(long body)
        {
            this->body = std::to_string(body);
        }

        /**
         * @brief Sets the response body (float)
         * @param body float
         */
        void setBody(float body)
        {
            this->body = std::to_string(body);
        }

        /**
         * @brief Sets the response body (double)
         * @param body double
         */
        void setBody(double body)
        {
            this->body = std::to_string(body);
        }

        /**
         * @brief Sets the response body (boolean)
         * @param body bool
         */
        void setBody(bool body)
        {
            this->body = body ? "true" : "false";
        }

        // Uncomment when using nlohmann::json
        /**
         * @brief Sets the response body from JSON
         * @param body nlohmann::json
         */
        void setBody(nlohmann::json body)
        {
            this->body = body.dump();
            this->contentType = getContentType(APPLICATION_JSON);
        }

        /**
         * @brief Sets the response body with content type
         * @param body std::string
         * @param type ResponseType
         */
        void setBody(const std::string &body, ResponseType type)
        {
            this->body = body;
            this->contentType = getContentType(type);
        }

        /**
         * @brief Sets the response body with explicit content type string
         * @param body std::string
         * @param contentType std::string
         */
        void setBody(const std::string &body, const std::string &contentType)
        {
            this->body = body;
            this->contentType = contentType;
        }

        /**
         * @brief Sets binary response body (for images, PDFs, files, etc.)
         * @param binaryData std::vector<unsigned char>
         * @param type ResponseType
         */
        void setBody(const std::vector<unsigned char> &binaryData, ResponseType type = APPLICATION_OCTET_STREAM)
        {
            // Convert binary data to string for storage
            this->body = std::string(binaryData.begin(), binaryData.end());
            this->contentType = getContentType(type);
        }

        /**
         * @brief Loads response body from file
         * @param filePath std::string
         * @param type ResponseType
         * @return bool - true if successful, false otherwise
         */
        bool setBodyFromFile(const std::string &filePath)
        {
            std::ifstream file(filePath, std::ios::binary | std::ios::ate);
            if (!file.is_open())
            {
                logger.error("Failed to open file: " + filePath);
                return false;
            }
            ResponseType type = getResponseTypeFromPath(filePath);
            // Get file size
            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);

            // Read file into string
            std::string buffer(size, '\0');
            if (!file.read(&buffer[0], size))
            {
                logger.error("Failed to read file: "+ filePath);
                file.close();
                return false;
            }

            file.close();

            this->body = buffer;
            this->contentType = getContentType(type);
            return true;
        }

        /**
         * @brief Setd the response headers
         *
         * @param headers std::unordered_map<std::string, std::string>
         */
        void setHeaders(std::unordered_map<std::string, std::string> headers) { this->headers = headers; }

        /**
         * @brief Sets the reaponse status code
         *
         * @param statusCode int
         */
        void setStatusCode(int statusCode) { this->statusCode = statusCode; }

        void setAuthorizationHandler(std::unique_ptr<IAuthorization> authHandler);

        void setResponseType(ResponseType responseType) { this->responseType = responseType; }

    private:
        std::string body;
        std::unordered_map<std::string, std::string> headers;
        Logger logger;
        int statusCode;
        std::unique_ptr<IAuthorization> authorizationHandler = nullptr;
        std::string contentType;
        void updateHeader();
        ResponseType responseType;
        std::string getFileExtension(const std::string &filePath)
        {
            size_t dotPos = filePath.find_last_of('.');
            if (dotPos == std::string::npos)
            {
                return "";
            }

            std::string ext = filePath.substr(dotPos + 1);
            // Convert to lowercase
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            return ext;
        }
        ResponseType getResponseTypeFromPath(const std::string &filePath)
        {
            std::string ext = getFileExtension(filePath);

            // JSON
            if (ext == "json")
            {
                return APPLICATION_JSON;
            }
            // XML
            else if (ext == "xml")
            {
                return APPLICATION_XML;
            }
            // HTML
            else if (ext == "html" || ext == "htm")
            {
                return TEXT_HTML;
            }
            // Plain text
            else if (ext == "txt" || ext == "text")
            {
                return TEXT_PLAIN;
            }
            // CSS
            else if (ext == "css")
            {
                return TEXT_CSS;
            }
            // JavaScript
            else if (ext == "js" || ext == "mjs")
            {
                return APPLICATION_JAVASCRIPT;
            }
            // PDF
            else if (ext == "pdf")
            {
                return APPLICATION_PDF;
            }
            // Images - PNG
            else if (ext == "png")
            {
                return IMAGE_PNG;
            }
            // Images - JPEG
            else if (ext == "jpg" || ext == "jpeg" || ext == "jpe")
            {
                return IMAGE_JPEG;
            }
            // Images - GIF
            else if (ext == "gif")
            {
                return IMAGE_GIF;
            }
            // Images - SVG
            else if (ext == "svg" || ext == "svgz")
            {
                return IMAGE_SVG;
            }
            // Images - WebP
            else if (ext == "webp")
            {
                return IMAGE_WEBP;
            }
            // Video - MP4
            else if (ext == "mp4" || ext == "m4v")
            {
                return VIDEO_MP4;
            }
            // Video - WebM
            else if (ext == "webm")
            {
                return VIDEO_WEBM;
            }
            // Audio - MPEG
            else if (ext == "mp3" || ext == "mpeg" || ext == "mpg")
            {
                return AUDIO_MPEG;
            }
            // Audio - WAV
            else if (ext == "wav")
            {
                return AUDIO_WAV;
            }
            // Audio - OGG
            else if (ext == "ogg" || ext == "oga")
            {
                return AUDIO_OGG;
            }
            // Archive - ZIP
            else if (ext == "zip")
            {
                return APPLICATION_ZIP;
            }
            // Archive - GZIP
            else if (ext == "gz" || ext == "gzip")
            {
                return APPLICATION_GZIP;
            }
            // Default to octet-stream for unknown types
            else
            {
                return APPLICATION_OCTET_STREAM;
            }
        }

        /**
         * @brief Gets the status text
         *
         * @return std::string
         */
        std::string getStatusText();

    }; // class ResponseContent
} // namespace Server
