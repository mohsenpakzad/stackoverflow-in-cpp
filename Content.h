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

	char * topic; // topic is only for question, it must allocated only for question!
	string body;

	int visits;
	ContentType type;
	static vector<ContentRelation> relations;

public:

	Content(char* T, string B="");
	Content(string B="");

	string getQ();
};