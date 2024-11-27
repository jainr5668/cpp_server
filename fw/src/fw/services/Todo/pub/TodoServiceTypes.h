#ifndef TODOSERVICETYPES_H
#define TODOSERVICETYPES_H
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <chrono>
#include "customDataType.h"
#include "boost/optional.hpp"
#include "Utils.h"

using time_point = std::chrono::system_clock::time_point;
namespace services
{
    namespace TodoService
    {
        class TodoPostData
        {
        public:
            CustomDataType<std::string> title;
            CustomDataType<std::string> description;
            boost::optional<std::string> status;
            CustomDataType<time_point> dueDate;

            TodoPostData() = default;

            TodoPostData(std::string title, std::string description, std::string status, time_point dueDate)
            {
                this->title.value = title;
                this->description.value = description;
                this->status = status;
                this->dueDate.value = dueDate;
            }

            ~TodoPostData() = default;

            TodoPostData(const TodoPostData &other)
            {
                title.value = other.title.value;
                description.value = other.description.value;
                status = other.status;
                dueDate.value = other.dueDate.value;
            };

            TodoPostData(std::vector<std::string> data)
            {
                title.value = data[0];
                description.value = data[1];
                status = data[2];
                dueDate.value = Utils::string_to_timepoint(data[3]);
            };

            friend void to_json(nlohmann::json &j, const TodoPostData &p)
            {
                j = nlohmann::json{
                    {"title", p.title.value},
                    {"description", p.description.value},
                    {"dueDate", Utils::timepoint_to_string(p.dueDate.value)}};
                if (p.status)
                {
                    j["status"] = p.status.value();
                }
            }

            friend void from_json(const nlohmann::json &j, TodoPostData &p)
            {
                j.at("title").get_to(p.title.value);
                j.at("description").get_to(p.description.value);
                if (j.contains("dueDate"))
                {
                    p.dueDate.value = Utils::string_to_timepoint(j.at("dueDate").get<std::string>());
                }
                else
                {
                    p.dueDate.value = std::chrono::system_clock::now() + std::chrono::hours(24);
                }
                if (j.contains("status"))
                {
                    p.status = j.at("status").get<std::string>();
                } else {
                    p.status = "pending";
                }
            }
        };

        class TodoDbData
        {
        public:
        boost::optional<std::string> id;
            CustomDataType<std::string> title;
            CustomDataType<std::string> description;
            CustomDataType<std::string> status;
            CustomDataType<time_point> created_at;
            CustomDataType<time_point> updated_at;
            CustomDataType<time_point> dueDate;
            boost::optional<std::string> userId;

            TodoDbData() = default;

            TodoDbData(std::string title, std::string description, std::string status,
            time_point created_at, time_point updated_at, time_point dueDate)
            {
                this->title.value = title;
                this->description.value = description;
                this->status.value = status;
                this->created_at.value = created_at;
                this->dueDate.value = dueDate;
                this->updated_at.value = updated_at;
            }

            TodoDbData(const TodoDbData &todoDBData_)
            {
                this->title.value = todoDBData_.title.value;
                this->description.value = todoDBData_.description.value;
                this->status.value = todoDBData_.status.value;
                this->created_at.value = todoDBData_.created_at.value;
                this->dueDate.value = todoDBData_.dueDate.value;
                this->updated_at.value = todoDBData_.updated_at.value;
                if (todoDBData_.userId)
                {
                    this->userId = todoDBData_.userId.value();
                }
                if (todoDBData_.id)
                {
                    this->id = todoDBData_.id.value();
                }
            }

            TodoDbData(TodoPostData todoPostData)
            {
                this->title.value = todoPostData.title.value;
                this->description.value = todoPostData.description.value;
                this->status.value = todoPostData.status.value();
                this->created_at.value = std::chrono::system_clock::now();
                this->dueDate.value = todoPostData.dueDate.value;
                this->id = Utils::get_uuid();
                this->updated_at.value = this->created_at.value;
            }

            TodoDbData(std::vector<std::string> data)
            {
                this->title.value = data[2];
                this->description.value = data[3];
                this->status.value = data[4];
                this->created_at.value = Utils::string_to_timepoint(data[6]);
                this->dueDate.value = Utils::string_to_timepoint(data[5]);
                this->updated_at.value = Utils::string_to_timepoint(data[7]);
                this->userId = data[1];
                this->id = data[0];
            };

            friend void to_json(nlohmann::json &j, const TodoDbData &p)
            {
                j = nlohmann::json{
                    {"title", p.title.value},
                    {"description", p.description.value},
                    {"status", p.status.value},
                    {"created_at", Utils::timepoint_to_string(p.created_at.value)},
                    {"dueDate", Utils::timepoint_to_string(p.dueDate.value)},
                    {"updated_at", Utils::timepoint_to_string(p.updated_at.value)}};
                if (p.userId)
                {
                    j["userId"] = p.userId.value();
                }
                if (p.id)
                {
                    j["id"] = p.id.value();
                }
            }
        };
    }
}
#endif // TODOSERVICETYPES_H
