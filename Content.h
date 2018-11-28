#pragma once

#include<vector>
#include<string>
#include"ContentRelation.h"


using namespace std;

enum ContentType {
	QUESTION,
	ANSWER
};

class Content {

private:

	string * topic; // topic is only for question, it must allocated only for question!
	string body;

	int visits;
	ContentType type;
	vector<ContentRelation> relations;

public:
	

};