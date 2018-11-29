#pragma once

#include <iostream>
#include "AbstractUser.h"
#include <vector>
class Content;


class User : public AbstractUser {

	friend ostream& operator<<(ostream&, const User&);
private:

	static string salt;
	static vector<User> users;
    vector<Content> contents;

public:

    User(string username, string password, string email, UserType type);

    static void init(const string &salt);

    void set_password(string password);
    bool check_password(string password);


    bool authenticate(string username, string password);
    void deleteAccount();

 
    void makeQuestion(string topic,string body);
	static void showAllQuestions();
    void showMyQuestions();

    void editQuestion(int i,string& topic,string& body);
    void deleteQuestion(int i);


    static User& login(string username, string password);
    static User& signup(string username, string password, string email);

	unsigned long kick_size();
};
