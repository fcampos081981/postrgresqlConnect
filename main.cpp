#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <filesystem>

#include "DatabaseFunctions.h"
#include "FilesFunctions.h"
#include "EnvLoader.h"

std::string getEnv() {
    try {
        std::string path = FilesFunctions::getUserHomeDir() + "/.env";
        EnvLoader::load(path);

        std::string host = EnvLoader::get("DB_HOST");
        std::string port = EnvLoader::get("DB_PORT", "000");
        std::string dbUser = EnvLoader::get("DB_USER");
        std::string dbName = EnvLoader::get("DB_NAME");
        std::string dbPass = EnvLoader::get("DB_PASSWORD");

        std::cout << "From .env: " << path << std::endl;
        std::cout << "Starting server on: " << host << ":" << port << std::endl;
        std::cout << "DbName: " << dbName << std::endl;
        std::cout << "Connecting as user: " << dbUser << std::endl;
        std::cout << "Connecting as password: " << dbPass << std::endl;

        std::string serverUrl = "dbname=" + dbName + " user=" + dbUser + " password=" + dbPass + " host=" + host +
                                " port=" + port;

        return serverUrl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return " ";
    }
}


int main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::string serverUrl = getEnv();
    std::string fileName = FilesFunctions::getUserHomeDir() + "/mydb_dump.txt";

    auto conn = DatabaseFunctions::connectToDB(serverUrl);

    DatabaseFunctions dbf;

    if (conn) {
        FilesFunctions::clearScreen();

        dbf.createTables(*conn);

        dbf.insertData(*conn, 399999);

        FilesFunctions::clearScreen();

        FilesFunctions::deleteFileIfExists(fileName);

        dbf.readData(*conn, fileName);
    } else {
        std::cerr << "Could not proceed with database operations due to connection failure." << std::endl;
        return 1;
    }
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::high_resolution_clock::now();

    FilesFunctions::showElapsed(start, end);

    FilesFunctions::getFileSize(fileName);

    std::cout << std::endl;
    return 0;
}
