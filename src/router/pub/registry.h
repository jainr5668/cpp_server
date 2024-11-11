#pragma once
#include "ServiceRegistry.h"

#include "TodoService.h"
#include "TodoEndpoint.h"
REGISTER_SERVICE("services::TodoService::TodoService", services::TodoService::TodoService);
REGISTER_ROUTER("endpoints::TodoEndpoint::TodoEndpoint", endpoints::TodoEndpoint::TodoEndpoint);

#include "AuthenticationService.h"
#include "AuthenticationEndpoint.h"
REGISTER_SERVICE("services::AuthenticationService::AuthenticationService", services::AuthenticationService::AuthenticationService);
REGISTER_ROUTER("endpoints::AuthenticationEndpoint::AuthenticationEndpoint", endpoints::AuthenticationEndpoint::AuthenticationEndpoint);