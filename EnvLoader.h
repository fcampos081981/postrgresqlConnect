//
// Created by usuario on 12/1/25.
//

#ifndef POSTRGRESQLCONNECT_ENVLOADER_H
#define POSTRGRESQLCONNECT_ENVLOADER_H

#include <string>
#include <unordered_map>
#include <stdexcept>

class EnvLoader {
public:
    // Loads the .env file from the specified path.
    // Throws std::runtime_error if the file cannot be opened.
    static void load(const std::string& path = ".env");

    // Retrieves the value for a given key.
    // Returns the value or throws std::out_of_range if the key doesn't exist.
    static std::string get(const std::string& key);

    // Retrieves the value for a given key.
    // Returns "defaultValue" if the key doesn't exist.
    static std::string get(const std::string& key, const std::string& defaultValue);

    // Checks if a specific key exists in the loaded environment.
    static bool has(const std::string& key);

private:
    static std::unordered_map<std::string, std::string> envMap;

    // Helper to trim leading/trailing whitespace
    static std::string trim(const std::string& str);
};

#endif //POSTRGRESQLCONNECT_ENVLOADER_H