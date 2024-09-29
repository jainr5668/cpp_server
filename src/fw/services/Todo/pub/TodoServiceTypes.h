#pragma once
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
            CustomDataType<std::string> title;
            CustomDataType<std::string> description;
            CustomDataType<std::string> status;
            CustomDataType<time_point> creationDate;
            CustomDataType<time_point> dueDate;
            boost::optional<std::string> userId;

            TodoDbData() = default;

            TodoDbData(std::string title, std::string description, std::string status, time_point creationDate, time_point dueDate)
            {
                this->title.value = title;
                this->description.value = description;
                this->status.value = status;
                this->creationDate.value = creationDate;
                this->dueDate.value = dueDate;
            }

            TodoDbData(TodoPostData todoPostData_)
            {
                this->title.value = todoPostData_.title.value;
                this->description.value = todoPostData_.description.value;
                this->status.value = todoPostData_.status.value();
                this->creationDate.value = std::chrono::system_clock::now();
                this->dueDate.value = todoPostData_.dueDate.value;
            }

            friend void to_json(nlohmann::json &j, const TodoDbData &p)
            {
                j = nlohmann::json{
                    {"title", p.title.value},
                    {"description", p.description.value},
                    {"status", p.status.value},
                    {"creationDate", Utils::timepoint_to_string(p.creationDate.value)},
                    {"dueDate", Utils::timepoint_to_string(p.dueDate.value)}};
                if (p.userId)
                {
                    j["userId"] = p.userId.value();
                }
            }
        };
    }
}