#ifndef RECTANGLE2D_H
#define RECTANGLE2D_H

extern double Get_Length(double, double, double, double);

class Rectangle2D
{
public:
	Rectangle2D();
	Rectangle2D(double center_x, double center_y, double width, double height);

	double getArea();
	double getPerimeter();

	void setCenterX(double center_x); 
	double getCenterX();
	void setCenterY(double center_y);
	double getCenterY();

	void setWidth(double width);
	double getWidth();
	void setHeight(double height);
	double getHeight();	
	
	bool contains(double x, double y);
	bool contains(const Rectangle2D &r);
	bool overlaps(const Rectangle2D &r);

	~Rectangle2D();



private:
	double centerX;
	double centerY;
	double width;
	double height;
	double area;
	double perimeter;
};

#endif

