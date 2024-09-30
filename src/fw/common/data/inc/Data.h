#pragma once
#include "IData.h"
#include <iostream>
#include <sqlite3.h>
#include <vector>

class Data : public IData
{
public:
    Data(std::string);
    std::vector<std::vector<std::string>> execute(std::string);
    std::string getDbPath() { return dbPath_; }
    template <typename T>
    std::string createInsertQuery(const std::string &tableName, T object)
    {
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

private:
    sqlite3 *db_;
    std::string dbPath_;
};
