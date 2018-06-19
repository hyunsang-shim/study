#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <iostream>
using namespace std;

class Course
{
public:
	Course();
	Course(const string& sourseName, int capacity);
	Course(const Course&);
	string getCourseName() const;
	void addStudent(const string& name);
	void dropStudent(const string& name);
	string* getStudents() const;
	int getNumberOfStudents() const;
	~Course();
private:
	string courseName;
	string* students;
	int numberOfStudents;
	int capacity;

};

#endif