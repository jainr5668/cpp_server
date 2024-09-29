#include "Data.h"
#include <nlohmann/json.hpp>
#include <sys/stat.h>

// Callback function to process each row in the result set
static int callback(void* data, int argc, char** argv, char** azColName) {
    auto& results = *static_cast<std::vector<std::vector<std::string>>*>(data);
    std::vector<std::string> row;
    for (int i = 0; i < argc; i++) {
        row.push_back(argv[i] ? argv[i] : "NULL");
    }
    results.push_back(row);
    return 0;
}

Data::Data(std::string dbName) 
{
    dbPath_ = "db/" + dbName;
    struct stat info;
    if (stat("db", &info) != 0) {
        // Directory does not exist, create it
        if (mkdir("db", 0777) == -1) {
            std::cerr << "Error creating directory 'db'" << std::endl;
        }
        std::cout << "Created directory 'db'" << std::endl;
    } else if (!(info.st_mode & S_IFDIR)) {
        // Path exists but is not a directory
        std::cerr << "'db' exists but is not a directory" << std::endl;
    }

}

std::vector<std::vector<std::string>> Data::execute(std::string query)
{
    std::vector<std::vector<std::string>> results;
    bool result = false;
    char *messageError;
    auto exit = sqlite3_open(dbPath_.c_str(), &db_);
    if (!exit)
    {
        int rc = sqlite3_exec(db_, query.c_str(), callback, &results, &messageError);
        if (rc != SQLITE_OK)
        {
            std::cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db_) << std::endl;
            sqlite3_free(messageError);
        }
        else
        {
            result = true;
        }
    }
    return results;
}

template <typename T>
std::string Data::createInsertQuery(const std::string& tableName, T object) {
    nlohmann::json data = nlohmann::json::parse(object.to_json());
    std::string keys = "";
    std::string values = "";

    for (auto it = data.begin(); it != data.end(); ++it) {
        if (it != data.begin()) {
            keys += ", ";
            values += ", ";
        }
        keys += it.key();
        values += it.value().dump();
    }
    std::string query = "INSERT INTO " + tableName + " (" + keys + ") VALUES (" + values + ");";
    return query;
}