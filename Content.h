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

	string & topic; // topic is only for question, it must allocated only for question!
	string body;

	int visits;
	ContentType type;
	static vector<ContentRelation> relations;

public:

	Content(string T="", string B="");

	string& getTopic();
	string& getBody();
};