#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <chrono>
#include "customDataType.h"

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
            CustomDataType<std::string> status;

            TodoPostData() = default;

            TodoPostData(CustomDataType<std::string> title, CustomDataType<std::string> description, CustomDataType<std::string> status) : title(title), description(description), status(status) {}

            ~TodoPostData() = default;

            TodoPostData(const TodoPostData &other)
            {
                title = other.title;
                description = other.description;
                status = other.status;
            };

            TodoPostData(std::vector<CustomDataType<std::string>> data)
            {
                title = data[0];
                description = data[1];
                status = data[2];
            };

            friend void to_json(nlohmann::json &j, const TodoPostData &p)
            {
                j = nlohmann::json{{"title", p.title.value}, {"description", p.description.value}, {"status", p.status.value}};
            }

            friend void from_json(const nlohmann::json &j, TodoPostData &p)
            {
                j.at("title").get_to(p.title.value);
                j.at("description").get_to(p.description.value);
                j.at("status").get_to(p.status.value);
            }
        };

        class TodoDbData{
            public:
            CustomDataType<std::string> title;
            CustomDataType<std::string> description;
            CustomDataType<std::string> status;
            CustomDataType<time_point> creationDate;
            CustomDataType<time_point> dueDate;

            TodoDbData(std::string title, std::string description, std::string status, time_point creationDate, time_point dueDate){
                this->title.value = title;
                this->description.value = description;
                this->status.value = status;
                this->creationDate.value = creationDate;
                this->dueDate.value = dueDate;
            }


        };
    }
}