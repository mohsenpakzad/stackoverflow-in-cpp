#pragma once

#include<vector>
#include<string>
#include"ContentRelation.h"
#include "User.h"

using namespace std;

enum ContentType {
	QUESTION,
	ANSWER
};

class Content {

private:


	string* topic; // topic is only for question, it must allocated only for question!
	string body;

	int* visits; // visits is only for question too, it must allocated only for question!
	ContentType type;
	static vector<ContentRelation> relations;
public:


	Content(string topic, string body);
	Content(string topic);

	string& showTopic();

	friend void User::editQuestion(int i,string& topic,string& body);
};