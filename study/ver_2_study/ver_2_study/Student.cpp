#include "stdafx.h"
#include "Student.h"
#include "Person.h"
#include <string>
#include <iostream>
using namespace std;


Student::Student()
{	
}


string Student::toString()
{
	string tmp;
	tmp.append("Class : student. Name : ");
	tmp.append(this->getName());


	return tmp;
}
