#ifndef POSTRGRESQLCONNECT_FILESFUNCTIONS_H
#define POSTRGRESQLCONNECT_FILESFUNCTIONS_H

#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <chrono>


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

    static std::string getUserHomeDir();

    static void showProgressBar(float progress,int count);

    static void clearScreen();

    static std::string formatTime(std::chrono::time_point<std::chrono::system_clock> tp);

    static void showElapsed(std::chrono::time_point<std::chrono::system_clock> start,std::chrono::time_point<std::chrono::system_clock> end) ;

};


#endif
