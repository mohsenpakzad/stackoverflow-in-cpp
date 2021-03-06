#include <utility>

//
// Created by spsina on 11/8/18.
//

#include <iostream>
#include <sstream>
#include <string.h>
#include "Content.h"
#include "User.h"
#include "Exceptions.h"


vector<User> User::users;
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

void User::showAllQuestions(){

	for (auto &user : users) {
		for (auto &content : user.contents) {
			cout << content.showTopic() << endl;
		}
	}
}
void User::showMyQuestions()  {
    int i=1;
    for(auto &content : this->contents) {
        cout <<i<<"."<< content.showTopic() << endl;
        i++;
    }

}
void User::makeQuestion(string topic,string body){

	contents.emplace_back(topic, body);

}

void User::editQuestion(int i,string& topic,string& body){
    
    contents[i-1]=Content(topic,body);
    
}
void User::deleteQuestion(int i){
    
    auto vp=contents.begin();
    vp+=i-1;
    contents.erase(vp);

}

unsigned long User::kick_size() {
    return contents.size();
}

ostream& operator <<(ostream& outS, const User& user) {

	outS << "Email[" + user.email + "] Username[" + user.username + "]";
	return outS;
}
