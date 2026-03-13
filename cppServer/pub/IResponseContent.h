#pragma once

#include <string>
#include <unordered_map>
#include <IAuthorization.h>
#include <memory>
#include <nlohmann/json.hpp>

using IAuthorization = Server::IAuthorization;

namespace Server
{
    class IResponseContent
    {
    public:
        enum ResponseType
        {
            APPLICATION_JSON = 0,
            APPLICATION_XML,
            TEXT_HTML,
            TEXT_PLAIN,
            TEXT_CSS,
            TEXT_JAVASCRIPT,
            APPLICATION_JAVASCRIPT,
            APPLICATION_PDF,
            APPLICATION_OCTET_STREAM,
            IMAGE_PNG,
            IMAGE_JPEG,
            IMAGE_GIF,
            IMAGE_SVG,
            IMAGE_WEBP,
            MULTIPART_FORM_DATA,
            APPLICATION_FORM_URLENCODED,
            VIDEO_MP4,
            VIDEO_WEBM,
            AUDIO_MPEG,
            AUDIO_WAV,
            AUDIO_OGG,
            APPLICATION_ZIP,
            APPLICATION_GZIP
        };
        virtual std::string createToken(const std::unordered_map<std::string, std::string> &payload) = 0;
        virtual std::string getBody() = 0;
        virtual std::unordered_map<std::string, std::string> getHeaders() = 0;
        virtual int getStatusCode() = 0;
        virtual std::string getServerResponse() = 0;
        virtual std::string getStatusText() = 0;
        virtual void setBody(std::string body) = 0;
        virtual void setBody(const char body) = 0;
        virtual void setBody(int body) = 0;
        virtual void setBody(long body) = 0;
        virtual void setBody(float body) = 0;
        virtual void setBody(double body) = 0;
        virtual void setBody(bool body) = 0;
        virtual void setBody(nlohmann::json body) = 0;
        virtual void setBody(const std::string &body, ResponseType type) = 0;
        virtual void setBody(const std::string &body, const std::string &contentType) = 0;
        virtual void setBody(const std::vector<unsigned char> &binaryData, ResponseType type = APPLICATION_OCTET_STREAM) = 0;
        virtual bool setBodyFromFile(const std::string &filePath) = 0;
        virtual void setHeaders(std::unordered_map<std::string, std::string> headers) = 0;
        virtual void setStatusCode(int statusCode) = 0;
        virtual void setAuthorizationHandler(std::unique_ptr<IAuthorization> authHandler) = 0;
        virtual std::unordered_map<std::string, std::string> getTokenPayload(std::string token) = 0;
        virtual void setResponseType(ResponseType responseType) = 0;
        std::string getContentType(ResponseType type)
        {
            switch (type)
            {
            case APPLICATION_JSON:
                return "application/json";
            case APPLICATION_XML:
                return "application/xml";
            case TEXT_HTML:
                return "text/html";
            case TEXT_PLAIN:
                return "text/plain";
            case TEXT_CSS:
                return "text/css";
            case TEXT_JAVASCRIPT:
                return "text/javascript";
            case APPLICATION_JAVASCRIPT:
                return "application/javascript";
            case APPLICATION_PDF:
                return "application/pdf";
            case APPLICATION_OCTET_STREAM:
                return "application/octet-stream";
            case IMAGE_PNG:
                return "image/png";
            case IMAGE_JPEG:
                return "image/jpeg";
            case IMAGE_GIF:
                return "image/gif";
            case IMAGE_SVG:
                return "image/svg+xml";
            case IMAGE_WEBP:
                return "image/webp";
            case MULTIPART_FORM_DATA:
                return "multipart/form-data";
            case APPLICATION_FORM_URLENCODED:
                return "application/x-www-form-urlencoded";
            case VIDEO_MP4:
                return "video/mp4";
            case VIDEO_WEBM:
                return "video/webm";
            case AUDIO_MPEG:
                return "audio/mpeg";
            case AUDIO_WAV:
                return "audio/wav";
            case AUDIO_OGG:
                return "audio/ogg";
            case APPLICATION_ZIP:
                return "application/zip";
            case APPLICATION_GZIP:
                return "application/gzip";
            default:
                return "application/octet-stream";
            }
        }
    }; // namespace IResponseContent
} // namespace Server
