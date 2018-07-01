#include "stdafx.h"
#include "Employee.h"

int Employee::getSalary()
{
	return salary;
}

void Employee::setSalary(int salary)
{
	this->salary = salary;
}

string Employee::toString()
{
	string tmp;
	tmp.append("Class : Employee. Name : ");
	tmp.append(this->getName());

	return tmp;
}
