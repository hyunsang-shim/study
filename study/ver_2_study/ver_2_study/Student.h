#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include "stdafx.h"

class Student : public Person
{

public :
	Student();
	string toString();

private:
	int status;
};

#endif
