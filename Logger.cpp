#include <iostream>

#include <sstream>
#include <fstream>
#include <time.h>
#include "Logger.h"

Logger* Logger::logger = nullptr;

std::string Logger::currentDateTime() {

	char timeAndDate[MAXLOGSIZE];

	time_t now = time(0);
	struct tm  tstruct;
	tstruct = *localtime(&now);

	strftime(timeAndDate, MAXLOGSIZE, "%Y/%m/%d %X", &tstruct);

	return std::string(timeAndDate, strlen(timeAndDate));
}

int Logger::findCurrentLogNum() {

	int currentLogNum;

	fstream logNumberFile;


	logNumberFile.open("./LogsDirectory/_Current_Log.data",std::ios::in);
	logNumberFile >> currentLogNum;
	logNumberFile.close();

	logNumberFile.open("./LogsDirectory/_Current_Log.data", std::ios::out);
	logNumberFile << currentLogNum + 1;
	logNumberFile.close();


	return currentLogNum;

}

Logger::Logger() {

	int newLogFileName = findCurrentLogNum();

	std::string fileName = "./LogsDirectory/log." + std::to_string(newLogFileName) + ".txt";
	// stringstream ss; string str = ""; int num = 1; ss << a << k;

	logFile = new fstream();
	logFile->open(fileName.c_str(), std::ios::app); // Create file and ready for store logs
}
 
Logger& Logger::getInstance() {

	if (logger == nullptr) {
		logger = new Logger();
	}
	return *logger;
}

void Logger::addLog(std::string log)const {

	*logFile << log << std::endl;
}

void Logger::closeLogFile() {

	logFile->close();
}

void Logger::startApp_log() {

	std::string log = "***** System started on " + currentDateTime() + " *****";
	addLog(log);
}
void Logger::endApp_log(){

	std::string log = "***** System ended on " + currentDateTime() + " *****";
	addLog(log);
}
void Logger::unsuccessfulLogin_log() {

	std::string log = "***** Unsuccessful Login " + currentDateTime() + " *****";
	addLog(log);
}
void Logger::unsuccessfulSignup_log() {

	std::string log = "***** Unsucessful Signup " + currentDateTime() + " *****";
	addLog(log);
}

void Logger::login_log(User& user)const {

	std::stringstream log;
	log << "Login --> " << user << " Date[" << currentDateTime() << "]";

	addLog(log.str());
}
void Logger::logout_log(User& user)const {

	std::stringstream log;
	log << "Logout --> " << user << " Date[" << currentDateTime() << "]";

	addLog(log.str());
}
void Logger::deleteAccount_log(string deletedUserInfo)const {

	std::stringstream log;
	log << "Delete Account --> " << deletedUserInfo << " Date[" << currentDateTime() << "]";

	addLog(log.str());
}
void Logger::unsuccessfulDeleteAccount_log(string deletedUserInfo)const {

	std::stringstream log;
	log << "Unsuccessful Delete Account --> " << deletedUserInfo << " Date[" << currentDateTime() << "]";

	addLog(log.str());
}
void Logger::signup_log(User& user)const {
	std::stringstream log;
	log << "Signup --> " << user << " Date[" << currentDateTime() << "]";

	addLog(log.str());
}
