#ifndef PERSON_H
#define PERSON_H
#include "stdafx.h"
#include <iostream>
//#include <string>
using namespace std;

class Person
{
public:
	Person();
	~Person();
	string getName();
	virtual string toString()=0;


private:
	string name;
};

#endif