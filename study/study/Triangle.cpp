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
	// 헤론 공식.
	// 세 변의 길이를 알 때의 삼각형 넓이 구하기
	// S = 1/2 * a * b * sin세타 = 1/2 * a * b * root(1 - ((a제곱 + b제곱 - c제곱) / (2 * a * b))제곱)
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
