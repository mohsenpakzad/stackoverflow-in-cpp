#include <string>
#include <iostream>
#include "Content.h"

using namespace std;

Content::Content(string T, string B):topic(T),body(B){}

string& Content::getTopic(){
    string& t = topic;
    return t;
}

string& Content::getBody(){
    string & b = body;
    return b;
}