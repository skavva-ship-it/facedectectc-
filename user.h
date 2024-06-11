#pragma once //safety

#include <string> //string header

class user{
public:
	int rate = 1;
	std::string finalxml = "haarcascade_frontalcatface.xml"; //define public vars and defaults


	void getrate();
	void xchoice();
	void createprogram(); //define functions
};