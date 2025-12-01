#include "EnvLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// Define the static member
std::unordered_map<std::string, std::string> EnvLoader::envMap;

void EnvLoader::load(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open .env file at: " + path);
    }

    std::string line;
    while (std::getline(file, line)) {
        // 1. Remove comments (anything after #)
        size_t commentPos = line.find('#');
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }

        // 2. Trim whitespace
        line = trim(line);

        // 3. Skip empty lines
        if (line.empty()) continue;

        // 4. Parse KEY=VALUE
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = trim(line.substr(0, delimiterPos));
            std::string value = trim(line.substr(delimiterPos + 1));

            // Handle quoted values (remove surrounding quotes if present)
            if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
                value = value.substr(1, value.size() - 2);
            } else if (value.size() >= 2 && value.front() == '\'' && value.back() == '\'') {
                 value = value.substr(1, value.size() - 2);
            }

            envMap[key] = value;
        }
    }

    file.close();
}

std::string EnvLoader::get(const std::string& key) {
    if (envMap.find(key) == envMap.end()) {
        throw std::out_of_range("Environment variable not found: " + key);
    }
    return envMap[key];
}

std::string EnvLoader::get(const std::string& key, const std::string& defaultValue) {
    if (envMap.find(key) == envMap.end()) {
        return defaultValue;
    }
    return envMap[key];
}

bool EnvLoader::has(const std::string& key) {
    return envMap.find(key) != envMap.end();
}

// Helper to trim leading/trailing whitespace
std::string EnvLoader::trim(const std::string& str) {
    const std::string whitespace = " \t\n\r";
    size_t start = str.find_first_not_of(whitespace);

    if (start == std::string::npos) {
        return ""; // The string is all whitespace
    }

    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}

