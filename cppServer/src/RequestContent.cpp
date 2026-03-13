#include "RequestContent.h"
#include <sstream>
#include <algorithm>

using RequestContent = Server::RequestContent;

namespace Server
{

    RequestContent::RequestContent(std::string rawRequest)
    {
        parseRequest(rawRequest);
    }

    void RequestContent::parseRequest(std::string rawRequest)
    {
        // Find the end of headers (double CRLF)
        size_t headerEndPos = rawRequest.find("\r\n\r\n");
        if (headerEndPos == std::string::npos)
        {
            logger.error("Invalid request: no header terminator found");
            return;
        }

        // Extract headers section
        std::string headersSection = rawRequest.substr(0, headerEndPos);
        std::istringstream headerStream(headersSection);

        // Parse request line
        std::string requestLine;
        std::getline(headerStream, requestLine);
        if (!requestLine.empty() && requestLine.back() == '\r')
            requestLine.pop_back();

        std::vector<std::string> requestParts = splitString(requestLine, ' ');
        if (requestParts.size() < 3)
        {
            logger.error("Invalid request line");
            return;
        }

        method = requestParts[0];
        route = requestParts[1];
        queryParameters = parseQueryParameters(route);
        size_t queryPos = route.find('?');
        if (queryPos != std::string::npos)
        {
            route = route.substr(0, queryPos);
        }
        std::string headerString;
        std::string line;
        while (std::getline(headerStream, line))
        {
            if (!line.empty() && line.back() == '\r')
                line.pop_back();
            if (!line.empty())
                headerString += line + "\n";
        }
        headers = parseHeaders(headerString);

        // Extract body (everything after the double CRLF)
        size_t bodyStartPos = headerEndPos + 4;
        if (bodyStartPos < rawRequest.length())
        {
            body = rawRequest.substr(bodyStartPos);

            // Check if this is a multipart request
            auto contentTypeIt = headers.find("Content-Type");
            if (contentTypeIt == headers.end())
                contentTypeIt = headers.find("content-type");

            if (contentTypeIt != headers.end() &&
                contentTypeIt->second.find("multipart/form-data") != std::string::npos)
            {
                parseMultipartBody(contentTypeIt->second, body);
            }
        }
    }

    void RequestContent::parseMultipartBody(const std::string &contentType, const std::string &bodyData)
    {
        // Extract boundary from Content-Type header
        size_t boundaryPos = contentType.find("boundary=");
        if (boundaryPos == std::string::npos)
        {
            logger.error("Multipart request missing boundary");
            return;
        }

        std::string boundary = "--" + contentType.substr(boundaryPos + 9);
        // Remove quotes if present
        if (!boundary.empty() && boundary.front() == '"')
            boundary = boundary.substr(1, boundary.length() - 2);

        logger.info("Parsing multipart with boundary: " + boundary);

        // Split body by boundary
        size_t pos = 0;
        size_t nextBoundary = bodyData.find(boundary, pos);

        while (nextBoundary != std::string::npos)
        {
            pos = nextBoundary + boundary.length();

            // Skip the CRLF after boundary
            if (pos + 2 <= bodyData.length() && bodyData.substr(pos, 2) == "\r\n")
                pos += 2;

            // Find next boundary
            nextBoundary = bodyData.find(boundary, pos);
            if (nextBoundary == std::string::npos)
                break;

            // Extract part between boundaries
            std::string part = bodyData.substr(pos, nextBoundary - pos);
            parseMultipartPart(part);
        }
    }

    void RequestContent::parseMultipartPart(const std::string &part)
    {
        // Find headers/content separation
        size_t partHeaderEnd = part.find("\r\n\r\n");
        if (partHeaderEnd == std::string::npos)
            return;

        std::string partHeaders = part.substr(0, partHeaderEnd);
        std::string partContent = part.substr(partHeaderEnd + 4);

        // Remove trailing CRLF from content
        if (partContent.length() >= 2 && partContent.substr(partContent.length() - 2) == "\r\n")
            partContent = partContent.substr(0, partContent.length() - 2);

        // Parse Content-Disposition header
        size_t cdPos = partHeaders.find("Content-Disposition:");
        if (cdPos == std::string::npos)
            cdPos = partHeaders.find("content-disposition:");

        if (cdPos == std::string::npos)
            return;

        size_t cdEnd = partHeaders.find("\r\n", cdPos);
        std::string contentDisposition = partHeaders.substr(cdPos, cdEnd - cdPos);

        // Extract field name
        size_t namePos = contentDisposition.find("name=\"");
        if (namePos != std::string::npos)
        {
            namePos += 6;
            size_t nameEnd = contentDisposition.find("\"", namePos);
            std::string fieldName = contentDisposition.substr(namePos, nameEnd - namePos);

            // Check if this is a file upload
            size_t filenamePos = contentDisposition.find("filename=\"");
            if (filenamePos != std::string::npos)
            {
            filenamePos += 10;
            size_t filenameEnd = contentDisposition.find("\"", filenamePos);
            std::string filename = contentDisposition.substr(filenamePos, filenameEnd - filenamePos);

            // Store file data (you'll need to add a files map to your class)
            files[fieldName] = {filename, partContent};
            requestBodyParts[fieldName] = partContent;
            }
            else
            {
            formFields[fieldName] = partContent;
            requestBodyParts[fieldName] = partContent;
            }
        }
    }

    std::unordered_map<std::string, std::string> RequestContent::parseQueryParameters(std::string query)
    {
        std::vector<std::string> queryParts = splitString(query, '?');
        std::unordered_map<std::string, std::string> queryParameters_;
        if (queryParts.size() > 1)
        {
            std::vector<std::string> parameters = splitString(queryParts[1], '&');
            for (auto parameter : parameters)
            {
                std::vector<std::string> keyValue = splitString(parameter, '=');
                queryParameters_[keyValue[0]] = keyValue[1];
            }
        }
        return queryParameters_;
    }

    std::unordered_map<std::string, std::string> RequestContent::parseHeaders(std::string headers)
    {
        std::vector<std::string> headerLines = splitString(headers, '\n');
        std::unordered_map<std::string, std::string> headers_;
        for (auto headerLine : headerLines)
        {
            headerLine.erase(std::remove(headerLine.begin(), headerLine.end(), '\r'), headerLine.end());
            std::vector<std::string> header = splitString(headerLine, ':');
            if (header.size() > 1)
            {
                headers_[header[0]] = header[1];
            }
        }
        return headers_;
    }

    std::vector<std::string> RequestContent::splitString(std::string str, char delimiter)
    {
        std::vector<std::string> parts;
        std::string part;
        std::istringstream stream(str);
        while (std::getline(stream, part, delimiter))
        {
            parts.push_back(part);
        }
        return parts;
    }

}
