#pragma once

#include <string>
#include <fstream>
#include "User.h"

#define MAXLOGSIZE 1000


class Logger{

private:

	static Logger *logger;
	fstream * logFile;
	
	Logger();
	int findCurrentLogNum();
	void addLog(string)const;

public:

	static string currentDateTime();
	static Logger& getInstance();
	void closeLogFile();

	void startApp_log();
	void unsuccessfulLogin_log();
	void unsuccessfulSignup_log();
	void endApp_log();

	void signup_log(User&)const;
	void login_log(User&)const;
	void logout_log(User&)const;
	void deleteAccount_log(string)const;
	void unsuccessfulDeleteAccount_log(string)const;


};


