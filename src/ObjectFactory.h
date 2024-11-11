
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>
#include "BaseService.h"

class DependencyResolver
{
public:
    static void loadDependencies(const std::string &filename)
    {
        std::ifstream file(filename);
    }
};
