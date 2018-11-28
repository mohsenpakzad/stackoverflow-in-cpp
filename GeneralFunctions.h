#pragma once

#ifdef _WIN32
#define CLEAR "cls" // Clear screen for Windows OS
#else 
#define CLEAR "clear" // Clear screen for Linux OS
#endif

void cleanBuf();

#define SystemPause std::cout<<"Press any key to continue . . ."; cleanBuf();


void showMessageToUser(const char *);
