#pragma once

#include <iostream>
#include "AbstractUser.h"
#include <list>
class Content;
enum ContentRelationType{
    DUPLICATE_OF,
    ANSWER_TO
};
enum ContentType{
    QUESTION,
    ANSWER
};
class ContentRelations{
    Content* destination;
    ContentRelationType type;
};
class Content{
	string* topic;
    string body;
    int visits;
    ContentType type;
    static list <ContentRelations> relations;
public:
    void set_body(string body);
};
class User : public AbstractUser {

	friend ostream& operator<<(ostream&, const User&);

private:

	static string salt;
	static vector<User> users;


public:

    User(string username, string password, string email, UserType type);

    static void init(const string &salt);


    void set_password(string password);
    bool check_password(string password);


    bool authenticate(string username, string password);
    void deleteAccount();


    static User& login(string username, string password);
    static User& signup(string username, string password, string email);

public:
	list<Content> contents;

};
