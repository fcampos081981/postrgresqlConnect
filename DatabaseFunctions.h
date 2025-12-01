// ... existing code ...
#ifndef POSTRGRESQLCONNECT_DATABASEFUNCTIONS_H
#define POSTRGRESQLCONNECT_DATABASEFUNCTIONS_H

#include <string>
#include <memory>
#include <pqxx/pqxx>
#include "DataGenerator.h"
#include "FilesFunctions.h"

class DatabaseFunctions {
public:
    DatabaseFunctions() {
    }

    virtual ~DatabaseFunctions() = default;

    static std::unique_ptr<pqxx::connection> connectToDB(const std::string &connStr);

    void createTables(pqxx::connection &C);

    void insertData(pqxx::connection &C, int count);

    void insertRandomPerson(pqxx::work &W, int age);

    auto readData(pqxx::connection &C, const std::string &filename) -> void;

private:
    FilesFunctions ff;
};


#endif