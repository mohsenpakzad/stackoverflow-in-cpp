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
public:
    string body;
    ContentType type;
    int visits;
    static list <ContentRelations> relations;
};
class User : public AbstractUser {
public:
    User(string username, string password, string email, UserType type);

    static void init(const string &salt);

public:
    void set_password(string password);
    bool check_password(string password);

public:
    bool authenticate(string username, string password);
    void deleteAccount();

public:
    static User& login(string username, string password);
    static User& signup(string username, string password, string email);

private:
    static string salt;
    static vector<User> users;
public:
    list<Content> contents;
};
