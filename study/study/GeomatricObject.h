#pragma once
#ifndef GEOMETRICOBJECT_H;

#include <string>
using namespace std;

class GeometricObject
{
public :
	GeometricObject();
	GeometricObject(const string &color, bool fill);
	string getColor() const;
	void setColor(const string &color);
	bool isFilled();	

	void setFilled(bool filled);	
	string toString() const;


private:
	string color;
	bool filled;
};

#endif // !GEOMETRICOBJECT_H;