// platform.h
// f-cs that interact with the platform

#pragma once
#include <sstream>
#include <iostream>
#include <conio.h>

//#include "windows.h" //библиотека audiere её требует
//#include "audiere.h" //звуковая библиотека

void clear() {
	system("cls"); // Windows

	//system("clear"); // UNIX
}

void resize_window(unsigned short int x, unsigned short int y) {
	std::stringstream ss;
	ss << "MODE " << x << "," << y;
	system(ss.str().c_str());

	//system("???"); // UNIX
}

char wait_key_press(){
	while(!kbhit());
    //printf("\n key (%c) was pressed!\n", getch());
	return getch();
}
