#include <string>
#include <iostream>
#include "Content.h"

using namespace std;




Content::Content(string body)
	:topic(nullptr),visits(nullptr), body(body), type(ContentType::ANSWER){} // constructor for answer
Content::Content(string topic, string body) 
	: topic(new string(topic)),visits(new int(0)), body(body),type(ContentType::QUESTION) {} // constructor for question

string& Content::showTopic() {
	return *topic;
}

