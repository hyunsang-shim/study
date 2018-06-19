#pragma once
#include "stdafx.h"
#include "Circle2D.h"


Circle2D::Circle2D()
{
}

Circle2D::Circle2D(double x, double y, double radius)
{
	PosX = x;
	PosY = y;
	this->radius = radius;

}

double Circle2D::getPosX()
{
	return PosX;
}

void Circle2D::setPosX(double X)
{
	this->PosX = X;
}

double Circle2D::getPosY()
{
	return PosY;
}

void Circle2D::setPosY(double Y)
{
	this->PosY = Y;
}

double Circle2D::getRadius()
{
	return radius;
}

double Circle2D::getArea()
{
	return radius*radius * PI;
}

double Circle2D::getPerimeter()
{
	return 2 * PI * radius;
}

bool Circle2D::contains(double x, double y)
{
	double a = x - PosX;
	double b = y - PosY;
	double dist_centers = pow((pow(a, 2.0) + pow(b, 2.0)), 0.5);

	if (dist_centers <= radius)
		return true;
	else
		return false;
}

bool Circle2D::contains(const Circle2D & circle)
{
	double a = circle.PosX - PosX;
	double b = circle.PosY - PosY;
	double dist_centers = pow((pow(a, 2.0) + pow(b, 2.0)), 0.5);
	double dist_centers_comp = pow((circle.PosX - radius) + pow(circle.PosY - radius, 2), 0.5);

	if (dist_centers <= radius && dist_centers_comp <= radius)
		return true;
	else
		return false;
}

bool Circle2D::overlaps(const Circle2D & circle)
{
	double a = circle.PosX - PosX;
	double b = circle.PosY - PosY;
	double dist_centers = pow((pow(a, 2.0) + pow(b, 2.0)), 0.5);
	double dist_centers_comp = pow((circle.PosX - radius) + pow(circle.PosY - radius, 2), 0.5);

	if (dist_centers <= radius || dist_centers_comp <= radius)
		return true;
	else
		return false; 
}

Circle2D::~Circle2D()
{
}
