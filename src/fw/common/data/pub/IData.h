#pragma once
#include <string>
#include <nlohmann/json.hpp>

class IData
{
public:
    virtual std::vector<std::vector<std::string>> execute(std::string) = 0;
    virtual std::string getDbPath() = 0;
    template <typename T>
    std::string objectToJson(const T &obj)
    {
        nlohmann::json j = obj;
        return j.dump();
    }
    template <typename T>
    std::string createInsertQuery(const std::string &tableName, T object){
        nlohmann::json data = nlohmann::json::parse(objectToJson(object));
        std::string keys = "";
        std::string values = "";

        for (auto it = data.begin(); it != data.end(); ++it)
        {
            if (it != data.begin())
            {
                keys += ", ";
                values += ", ";
            }
            keys += it.key();
            values += it.value().dump();
        }
        std::string query = "INSERT INTO " + tableName + " (" + keys + ") VALUES (" + values + ");";
        return query;
    }
};