#include "Endpoint1Service.h"

namespace Example
{
namespace Endpoint
{
    std::pair<bool, Example::Endpoint::Endpoint1Response> Endpoint1Service::processRequest1(Example::Endpoint::Endpoint1Request &request)
    {
        // Implement the logic for processing the request here.
        // For demonstration purposes, we'll just print the request and return a dummy response.

        // std::cout << "Processing request: " << request.data << std::endl;

        // Create a dummy response
        Example::Endpoint::Endpoint1Response response;
        response.setEndpoint1Request([request]() {
            Example::Endpoint::Endpoint1Request req;
            req.setName(request.getName().value_or("Default Name"));
            req.setId(request.getId().value_or(0));
            return req;
        }());

        return {true, response};
    }
} // namespace Endpoint
} // namespace Example