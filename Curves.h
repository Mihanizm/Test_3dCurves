#include <vector>

# define M_PI           3.14159265358979323846 

class Point
{
public:
	double x;
	double y;
	double z;

	Point(double, double, double);
};

class Curve
{
public:
	virtual Point GetPoint(double) = 0;
	virtual std::vector<double> GetFD(double) = 0;
	virtual double GetDouble();
};

class Circle : public Curve
{
public:
	double r;

	Circle(double);
	Point GetPoint(double) override;
	std::vector<double> GetFD(double) override;
	double GetDouble() override;
};

class Elipse : public Curve
{
public:
	double a;
	double b;

	Elipse(double,double);
	Point GetPoint(double) override;
	std::vector<double> GetFD(double) override;
};

class Spiral : public Curve
{
public:
	double r;
	double step;

	Spiral(double, double);
	Point GetPoint(double) override;
	std::vector<double> GetFD(double) override;
};