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
    logger_.info("Data::Data Entry");
    dbPath_ = "db/" + dbName;
    struct stat info;
    if (stat("db", &info) != 0) {
        // Directory does not exist, create it
        if (mkdir("db", 0777) == -1) {
            logger_.error("Error creating directory 'db'");
        }
    } else if (!(info.st_mode & S_IFDIR)) {
        // Path exists but is not a directory
        logger_.error("Path 'db' exists but is not a directory");
    }
    logger_.info("Data::Data Exit");

}

std::vector<std::vector<std::string>> Data::execute(std::string query)
{
    logger_.info("Data::execute Entry");
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
            sqlite3_close(db_);
            throw std::runtime_error("Error executing SQLite3 query: " + std::string(sqlite3_errmsg(db_)));
            sqlite3_free(messageError);
        }
        else
        {
            result = true;
        }
    }
    return results;
}

