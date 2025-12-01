#ifndef POSTRGRESQLCONNECT_FILESFUNCTIONS_H
#define POSTRGRESQLCONNECT_FILESFUNCTIONS_H

#include <string>

namespace pqxx {
    class result;
}

class FilesFunctions {
public:
    FilesFunctions() {
    }

    virtual ~FilesFunctions() = default;

    static void deleteFileIfExists(const std::string &filename);

    static void writeDataToFile(const pqxx::result &R, const std::string &filename);
};


#endif
