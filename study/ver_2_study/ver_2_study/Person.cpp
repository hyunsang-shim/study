#include "stdafx.h"
#include "Person.h"
#include <iostream>
#include <string>

Person::Person()
{
	name = "Default";
}

string Person::getName()
{
	return name;
}


Person::~Person()
{
}
