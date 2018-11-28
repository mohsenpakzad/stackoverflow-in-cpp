#include<iostream>
#include"GeneralFunctions.h"


void cleanBuf() { // Don't you ever think user might be stupic!?
	while (getchar() != '\n');
}

void showMessageToUser(const char * message) {
	system(CLEAR);
	std::cout << message << std::endl;
	SystemPause;
}