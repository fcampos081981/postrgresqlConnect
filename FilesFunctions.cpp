#include "FilesFunctions.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <pqxx/pqxx>
#include <iomanip>

namespace fs = std::filesystem;

void FilesFunctions::deleteFileIfExists(const std::string &filename) {
    try {
        if (fs::remove(filename)) {
            std::cout << "File '" << filename << "' deleted successfully." << std::endl;
        } else {
            std::cout << "File '" << filename << "' not found." << std::endl;
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Error deleting file: " << e.what() << std::endl;
    }
}

void FilesFunctions::writeDataToFile(const pqxx::result &R, const std::string &filename) {
    std::ofstream outFile(filename);

    if (outFile.is_open()) {
        for (auto row: R) {
            int id = row[0].as<int>();
            std::stringstream ss;
            ss << std::setw(5) << std::setfill('0') << id;

            std::string line =
                    "ID: " + ss.str() + " | " +
                    "Nome: " + row[1].c_str() + " | " +
                    "Idade: " + std::to_string(row[2].as<int>()) + " | " +
                    "Telefone: " + (row[3].is_null() ? "N/A" : row[3].c_str());


            outFile << line << std::endl;
        }
        outFile.close();
    } else {
        std::cerr << "Error: Could not open file '" << filename << "' for writing." << std::endl;
    }
}