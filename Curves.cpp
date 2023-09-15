#include "Curves.h"

Point::Point(double x = 0, double y = 0, double z = 0)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

double Curve::GetDouble() 
{ 
	return 0.0;
}

Circle::Circle(double r = 1) 
{ 
	this->r = r;
};

Point Circle::GetPoint(double t)
{
	Point res;
	res.x = this->r * sin(t);
	res.y = this->r * cos(t);
	res.z = 0.0;

	return res;
}

std::vector<double> Circle::GetFD(double t)
{
	std::vector<double> res(3);
	res[0] = this->r * cos(t);
	res[1] = -this->r * sin(t);
	res[2] = 0;

	return res;
}

double Circle::GetDouble()
{
	return this->r;
}

Elipse::Elipse(double a = 1, double b = 1) 
{ 
	this->a = a; 
	this->b = b; 
};

Point Elipse::GetPoint(double t)
{
	Point res;
	res.x = this->a * sin(t);
	res.y = this->b * cos(t);
	res.z = 0.0;

	return res;
}

std::vector<double> Elipse::GetFD(double t)
{
	std::vector<double> res(3);
	res[0] = this->a * cos(t);
	res[1] = -this->b * sin(t);
	res[2] = 0;

	return res;
}

Spiral::Spiral(double r = 1, double step = 2 * M_PI) 
{ 
	this->r = r; 
	this->step = step; 
};

Point Spiral::GetPoint(double t)
{
	Point res;
	res.x = this->r * sin(t);
	res.y = this->r * cos(t);
	res.z = step * t;

	return res;
}

std::vector<double> Spiral::GetFD(double t) 
{
	std::vector<double> res(3);
	res[0] = this->r * cos(t);
	res[1] = -this->r * sin(t);
	res[2] = step;

	return res;
}
