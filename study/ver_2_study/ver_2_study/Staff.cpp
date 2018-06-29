#include "stdafx.h"
#include "Staff.h"



Staff::Staff()
{
	salary = 10000000;
	office = "ÀÎÇÏ´ë";
	date_hired = "2018-04-24";
}

string Staff::toString()
{
	string tmp;
	tmp.append("Class : Staff. Name : ");
	tmp.append(this->getName());

	return tmp;
}