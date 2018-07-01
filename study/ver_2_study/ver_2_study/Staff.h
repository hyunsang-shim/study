#include "Person.h"
#include "stdafx.h"
using namespace std;

class Staff : public Person
{
public:
	Staff();
	string toString();

private:
	int salary;
	string office;
	string date_hired;
};