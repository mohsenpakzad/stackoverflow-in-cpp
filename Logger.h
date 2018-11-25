#ifndef SINGLETONFACTORYMUTED_LOGGER_H
#define SINGLETONFACTORYMUTED_LOGGER_H

#include <vector>
#include <string>
#include "User.h"

#define _Log(x) Logger::getInstance().log((x));


class Logger {
public:
    static Logger& getInstance();

public:
    void printLogs();
    void log(User * user);
    void saveLogs();
    std::vector<std::string>& getLogs ();
private:
    Logger();
    std::vector<std::string> logs;
};


#endif //SINGLETONFACTORYMUTED_LOGGER_H