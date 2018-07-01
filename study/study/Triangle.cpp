#include "Triangle.h"
#include <iostream>


Triangle::Triangle()
{
}

Triangle::Triangle(double side1, double side2, double side3)
{
	this->side1 = side1;
	this->side2 = side2;
	this->side3 = side3;
}

Triangle::Triangle(double side1, double side2, double side3, string color, bool filled)
{
	this->side1 = side1;
	this->side2 = side2;
	this->side3 = side3;
	setColor(color);
	setFilled(filled);
}

double Triangle::getSide1()
{
	return side1;
}

double Triangle::getSide2()
{
	return side2;
}

double Triangle::getSide3()
{
	return side3;
}

void Triangle::setSide1(double side1)
{
	this->side1 = side1;
}

void Triangle::setSide2(double side2)
{
	this->side2 = side2;
}

void Triangle::setSide3(double side3)
{
	this->side3 = side3;

}

double Triangle::getArea()
{
	// ��� ����.
	// �� ���� ���̸� �� ���� �ﰢ�� ���� ���ϱ�
	// S = 1/2 * a * b * sin��Ÿ = 1/2 * a * b * root(1 - ((a���� + b���� - c����) / (2 * a * b))����)
	double a2 = pow(side1, 2);
	double b2 = pow(side2, 2);
	double c2 = pow(side3, 2);

	double result;

	double first = 0.5 * side1 * side2;
	double child = a2 + b2 - c2;
	double mother = 2 * side1 * side2;
	result = first * (1 - pow((child / mother), 2));
	cout << " Result = " << result << endl;
	return result;
}

double Triangle::getPerimeter()
{
	return side1+side2+side3;
}

string Triangle::toString()
{
	return "Triangle Object";
}



Triangle::~Triangle()
{
}
