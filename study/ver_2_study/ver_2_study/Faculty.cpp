#include "stdafx.h"
#include "Faculty.h"

Faculty::Faculty()
{
	status = 1;
}

string Faculty::toString()
{
	string tmp;
	tmp.append("Class : Faculty. Name : ");
	tmp.append(this->getName());

	return tmp;
}
