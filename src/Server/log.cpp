#include "Server.hpp"

#include <ctime>
#include <cstring>
#include <iomanip>
#include <sstream>

void logError(const std::string& msg) 
{
    std::time_t t = std::time(0);
    std::tm* tm_info = std::localtime(&t);

    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
    std::clog << "[" << timestamp << "] [ERROR] " << msg << std::endl;
}

void log(const std::string& msg) 
{
    std::time_t t = std::time(0);
    std::tm* tm_info = std::localtime(&t);

    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    std::clog << "[" << timestamp << "]" << msg << std::endl;
}

void logPerror(const std::string& msg) {
    // Get the error message from perror
    std::string error_msg = strerror(errno);

    // Log the error with a formatted message
    logError(msg + ": " + error_msg);
}