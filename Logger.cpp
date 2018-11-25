#include <iostream>
#include <vector>
#include <fstream>
#include "Logger.h"
#include "time.h"

Logger::Logger() {}

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}


Logger& Logger::getInstance() {
    static Logger lg;
    return lg;
}

void Logger::log(User * user) {
    this->logs.push_back(user->email+" "+user->username+" "+currentDateTime());
}

void Logger::printLogs() {
    for (int i=0; i < logs.size();i++){
        std::cout << logs[i] << std::endl;
    }
}

void Logger::saveLogs(){
    int x;
    string X;

    ifstream dfile;
    dfile.open("./DATA/LOG.data");
    dfile >> x;
    dfile.close();

    ofstream logFile;
    X = std::to_string(x);
    logFile.open("./DATA/log."+X+".txt",ios::trunc);

    for (int i=0; i < logs.size();i++){
        logFile << logs[i] << "\n";
    }
    logFile.close();
    
    x++;
    X = std::to_string(x);

    ofstream dfile2;
    dfile2.open("./DATA/LOG.data",ios::trunc);
    dfile2 << X;
    dfile2.close();
}

std::vector<std::string>& Logger::getLogs() {
    return this->logs;
}