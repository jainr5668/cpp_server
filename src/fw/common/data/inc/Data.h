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
    template <typename T>
    std::string createInsertQuery(const std::string& tableName, T jsonData);
    std::string getDbPath() { return dbPath_; }
private:
    sqlite3 *db_;
    std::string dbPath_;
};
