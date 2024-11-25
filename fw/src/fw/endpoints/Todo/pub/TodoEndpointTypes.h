#ifndef TODOENDPOINTTYPES_H
#define TODOENDPOINTTYPES_H
#include <string>
#include <vector>
#include "TodoServiceTypes.h"
#include <boost/optional.hpp>

using TodoPostData = services::TodoService::TodoPostData;
using TodoDBData = services::TodoService::TodoDbData;
namespace endpoints {
    namespace TodoEndpoint{
        class TodosGetResponse{
        public:
            boost::optional<std::vector<TodoDBData>> members;
            std::vector<std::string> memberIds;

            TodosGetResponse() = default;

            TodosGetResponse(std::vector<std::string> memberIds, std::vector<TodoDBData> members){
                this->members = members;
                this->memberIds = memberIds;
            }

            TodosGetResponse(std::vector<std::string> memberIds){
                this->memberIds = memberIds;
            }

            friend void to_json(nlohmann::json &j, const TodosGetResponse &p)
            {
                j = nlohmann::json{
                    {"memberIds", p.memberIds}
                };
                if (p.members)
                {
                    j["members"] = p.members.value();
                }
            }
        };
    }
}
#endif // TODOENDPOINTTYPES_H
