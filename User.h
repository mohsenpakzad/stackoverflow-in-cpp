#pragma once

#include <iostream>
#include "AbstractUser.h"
#include "Content.h"

class User : public AbstractUser {

	friend ostream& operator<<(ostream&, const User&);
private:

	static string salt;
	static vector<User> users;
    static vector<Content> contents;

public:

    User(string username, string password, string email, UserType type);

    static void init(const string &salt);

    void set_password(string password);
    bool check_password(string password);


    bool authenticate(string username, string password);
    void deleteAccount();

    string showAllQuestions();
    void makeQuestion(string topic,string body);

    static User& login(string username, string password);
    static User& signup(string username, string password, string email);

};
