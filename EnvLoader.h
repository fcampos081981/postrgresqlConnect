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
    static void load(const std::string &path = ".env");

    static std::string get(const std::string &key);

    static std::string get(const std::string &key, const std::string &defaultValue);

    static bool has(const std::string &key);

private:
    static std::unordered_map<std::string, std::string> envMap;

    static std::string trim(const std::string &str);
};

#endif //POSTRGRESQLCONNECT_ENVLOADER_H