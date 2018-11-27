#include<iostream>


void cleanBuf() { // Don't you ever think user might be stupic!?
	while (getchar() != '\n');
}