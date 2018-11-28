#include <string>
#include <iostream>
#include <string.h>
#include "Content.h"

using namespace std;

Content::Content(string B){
    body = B;
}
Content::Content(char* T, string B){
    body = B;
    topic = new char[strlen(T)];
    strcpy(topic,T);
}

string Content::getQ(){
    string out;
    string t = string(topic);
    out = out+t+"\n"+body;
    return out;
}
