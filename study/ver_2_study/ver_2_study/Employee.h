#include "Person.h"
#include "stdafx.h"

using namespace std;

class Employee : public Person
{
public :
	int getSalary();
	void setSalary(int salary);
	string toString();

private:	
	int salary;
	string office;
	string date_hired;
};