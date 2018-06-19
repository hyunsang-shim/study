#include "stdafx.h"
#include "Course.h"
using namespace std;


Course::Course()
{
}

Course::Course(const string & sourseName, int capacity)
{
	numberOfStudents = 0;
	this->courseName = courseName;
	this->capacity = capacity;
	students = new string[capacity];
}

Course::Course(const Course &course)
{
	courseName = course.courseName;
	numberOfStudents = course.numberOfStudents;
	capacity = course.capacity;
	students = new string[capacity];
	for (int i = 0; i < numberOfStudents; i++)
		students[i] = course.students[i];
}

string Course::getCourseName() const
{
	return courseName;
}

void Course::addStudent(const string & name)
{
	if (numberOfStudents >= capacity)
	{
		cout << "The maximum size of array exceeded" << endl;
		cout << "Program teminates now" << endl;
	}
	exit(0);
	
students[numberOfStudents] = name;
numberOfStudents++;
}

void Course::dropStudent(const string& name)
{
	//½Ç½À
}

string* Course::getStudents() const
{
	return students;
}

int Course::getNumberOfStudents() const
{
	return numberOfStudents;
}

Course::~Course()
{
	delete [] students;
}
