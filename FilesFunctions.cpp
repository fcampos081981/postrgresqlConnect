#include "FilesFunctions.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <pqxx/pqxx>
#include <iomanip>
#include <thread>

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
            ss << std::setw(9) << std::setfill('0') << id;

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

std::string FilesFunctions::getUserHomeDir() {
    uid_t uid = getuid();

    struct passwd *pw = getpwuid(uid);

    if (pw == nullptr) {
        std::cerr << "Error: Could not retrieve user information." << std::endl;
        return "";
    }

    return std::string(pw->pw_dir);
}

void FilesFunctions::showProgressBar(float progress, int count, int countTotal) {
    int barWidth = 70;
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " % - Done: " << count << " of " << countTotal << std::endl;
    std::cout.flush();
}

void FilesFunctions::clearScreen() {
    std::cout << "\033[2J\033[3J\033[H" << std::flush;
}

std::string FilesFunctions::formatTime(std::chrono::time_point<std::chrono::system_clock> tp) {
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::tm *now_tm = std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(now_tm, "%H:%M:%S");

    return ss.str();
}

void FilesFunctions::showElapsed(std::chrono::time_point<std::chrono::system_clock> start,
                                 std::chrono::time_point<std::chrono::system_clock> end) {
    std::string startTime = "Start: " + FilesFunctions::formatTime(start);
    std::string endTime = "Start: " + FilesFunctions::formatTime(end);
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    int hours = elapsed_seconds / 3600;
    int minutes = (elapsed_seconds % 3600) / 60;
    int seconds = elapsed_seconds % 60;

    std::cout << std::endl;
    std::cout << startTime << std::endl;
    std::cout << endTime << std::endl;
    std::cout << "Elapsed Time: "
            << std::setfill('0') << std::setw(2) << hours << ":"
            << std::setfill('0') << std::setw(2) << minutes << ":"
            << std::setfill('0') << std::setw(2) << seconds << std::endl;
}

std::string FilesFunctions::sformatFileSize(uintmax_t bytes) {
    static constexpr const char *suffixes[] = {"B", "KB", "MB", "GB", "TB", "PB"};
    static constexpr double unitScale = 1024.0;

    double size = static_cast<double>(bytes);
    size_t suffixIndex = 0;
    const size_t maxSuffixIndex = std::size(suffixes) - 1;

    while (size >= unitScale && suffixIndex < maxSuffixIndex) {
        size /= unitScale;
        suffixIndex++;
    }

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << size << " " << suffixes[suffixIndex];
    return oss.str();
}

uintmax_t FilesFunctions::getFileSize(const std::string &filePath) {
    try {
        if (std::filesystem::exists(filePath)) {
            auto fsize = std::filesystem::file_size(filePath);
            std::cout << "File size: " << sformatFileSize(fsize);
            return fsize;
        } else {
            std::cout << "File not found: " << filePath << std::endl;
            return 0;
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Error accessing file: " << e.what() << std::endl;
        return 0;
    }
}
