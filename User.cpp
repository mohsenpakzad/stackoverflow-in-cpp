#include <utility>

//
// Created by spsina on 11/8/18.
//

#include <sstream>
#include <string.h>
#include "Content.h"
#include "User.h"
#include "Exceptions.h"
#include <iostream>


vector<User> User::users;
vector<Content> User::contents;
string User::salt;


User::User(string username, string password, string email, UserType type){
    lower(username);
    this->username = username;
    set_password(std::move(password));
    this->email = email;
    this->type = type;
}

void User::set_password(string password){
    size_t ps = pass_hash(password + salt);
    stringstream out;
    out << ps;
    this->password = out.str();
}

bool User::check_password(string password){
    size_t check = pass_hash(password + salt);
    stringstream out;
    out << check;
    return (this->password == out.str());
}

bool User::authenticate(string username, string password){
    lower(username);
    return this->username == username and check_password(password);
}

void User::deleteAccount(){
    if (this->type == UserType::ADMIN) {
        throw DeleteAdminException();
    }

    for (auto user = users.begin(); user != users.end();user++){
        if ( user->username == this->username  ) {
            users.erase(user);
            break;
        }
    }
}

User& User::login(string username, string password){
    for (auto &user : users) {
        if(user.authenticate(username, password)) {
            return user;
        }
    }
    throw WrongUsernameOrPasswordException();
}

User& User::signup(string username, string password, string email){
    for (auto &user : users) {
        if (user.username == username) {
            throw UsernameAlreadyExistsException();
        }
        else if (user.email == email) {
            throw EmailAlreadyExistsException();
        }
    }
    //Create user
    users.emplace_back(username, password, email, UserType::MEMBER);
    return users[users.size() - 1];
}

void User::init(const string &salt) {
    User::salt = salt;
    users.reserve(20);
    users.emplace_back("admin", "admin", "admin@stackoverflow.com", UserType::ADMIN);
}

string User::showAllQuestions(){
    string out;
    for(auto user = users.begin(); user != users.end();user++){
        for(auto &content : user->contents){
            out = out+content.getQ()+"\n\n";
        }
    }
    return out;
}

void User::makeQuestion(string topic,string body){
    char * T;
    strcpy(T,topic.c_str());
    contents.emplace_back(T,body);
}

ostream& operator <<(ostream& outS, const User& user) {

	outS << "Email[" + user.email + "] Username[" + user.username + "]";
	return outS;
}
