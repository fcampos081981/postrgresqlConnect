#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <filesystem>

#include "DatabaseFunctions.h"
#include "FilesFunctions.h"
#include "EnvLoader.h"


void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

std::string getEnv() {
    try {

        EnvLoader::load(FilesFunctions::getUserHomeDir() +"/.env");


        std::string host = EnvLoader::get("DB_HOST");
        std::string port = EnvLoader::get("DB_PORT", "000");
        std::string dbUser = EnvLoader::get("DB_USER");
        std::string dbName = EnvLoader::get("DB_NAME");
        std::string dbPass = EnvLoader::get("DB_PASSWORD");

        std::cout << "Starting server on: " << host << ":" << port << std::endl;
        std::cout << "DbName: " << dbName << std::endl;
        std::cout << "Connecting as user: " << dbUser << std::endl;
        std::cout << "Connecting as password: "  << dbPass<< std::endl;

        std::string serverUrl = "dbname="+dbName+" user="+dbUser+" password="+dbPass+" host="+host+" port="+port;

        return serverUrl;


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return " ";
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::string serverUrl = getEnv();
    std::string fileName = FilesFunctions::getUserHomeDir() + "/mydb_dump.txt";

    auto conn = DatabaseFunctions::connectToDB(serverUrl);

    if (conn) {

        DatabaseFunctions dbf;

        dbf.createTables(*conn);

        clearScreen();

        dbf.insertData(*conn, 1000000);

        clearScreen();

        FilesFunctions::deleteFileIfExists(fileName);

        dbf.readData(*conn, fileName);
    } else {
        std::cerr << "Could not proceed with database operations due to connection failure." << std::endl;
        return 1;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    int hours = elapsed_seconds / 3600;
    int minutes = (elapsed_seconds % 3600) / 60;
    int seconds = elapsed_seconds % 60;

    std::cout << "Elapsed Time: "
              << std::setfill('0') << std::setw(2) << hours << ":"
              << std::setfill('0') << std::setw(2) << minutes << ":"
              << std::setfill('0') << std::setw(2) << seconds << std::endl;

    return 0;
}
