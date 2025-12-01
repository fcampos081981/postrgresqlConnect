#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <vector>
#include <random>
#include <memory>
#include <fstream>
#include <filesystem>

#include "DatabaseFunctions.h"
#include "FilesFunctions.h"


void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}


int main() {
    std::string serverUrl = "dbname=mydb user=postgres password=12345 host=localhost port=5432";

    auto conn = DatabaseFunctions::connectToDB(serverUrl);

    if (conn) {
        DatabaseFunctions dbf;

        dbf.createTables(*conn);

        clearScreen();

        dbf.insertData(*conn, 100000);

        clearScreen();

        std::string fileName = "/home/usuario/mydb_dump.txt";

        FilesFunctions::deleteFileIfExists(fileName);

        dbf.readData(*conn, fileName);
    } else {
        std::cerr << "Could not proceed with database operations due to connection failure." << std::endl;
        return 1;
    }
    return 0;
}
