#include "server.h"
#include "router.h"
#include "SubRouterMap.h"

int main(){
    std::unique_ptr<Router> router = std::make_unique<Router>();
    SubRouterMap subRouterMap;
    for (auto &subRouter : subRouterMap.getRouterMap())
        router->addSubRouter(subRouter.first, subRouter.second);
    std::shared_ptr<Server> server = std::make_shared<Server>(std::move(router));
    server->start();
    return 0;
}

// docker build -t cpp-dev . && docker run -it --rm -p 8080:8080 --name cpp-app cpp-dev

// uint32_t StringToUint32(const std::string& str) {
//     uint32_t hash = 0;
//     for (char c : str) {
//         hash = (hash * 31) + static_cast<uint32_t>(c);
//     }
//     return hash;
// }
