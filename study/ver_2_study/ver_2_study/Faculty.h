#ifndef FACULTY_H
#define FACULTY_H
#include "Person.h"
#include "stdafx.h"

class Faculty : public Person
{

public:
	Faculty();
	string toString();

private:
	int status;
};

#endif
