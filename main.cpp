#include <iostream>
#include <vector>
#include <random>
#include <typeinfo>
#include <numeric>
#include "Curves.h"

int GetRandomInt(int l, int r)
{
	std::random_device rd;
	std::uniform_int_distribution<> distType(l, r);

	return distType(rd);
}

double GetRandomDouble(double l, double r)
{
	std::random_device  rd;
	std::uniform_real_distribution<double> unif(l, r);

	return unif(rd);
}

std::shared_ptr<Curve> CreateCurve(int n)
{
	std::shared_ptr<Curve> c;

	if (n == 1)
	{
		c = std::shared_ptr<Curve>(new Circle(GetRandomDouble(1,10)));
	}
	else if (n == 2)
	{
		c = std::shared_ptr<Curve>(new Elipse(GetRandomDouble(1, 10), GetRandomDouble(1, 10)));
	}
	else
	{
		c = std::shared_ptr<Curve>(new Spiral(GetRandomDouble(1, 10), GetRandomDouble(M_PI/6, 5 * M_PI/6)));
	}

	return c;
}

bool comp(std::shared_ptr<Curve> a, std::shared_ptr<Curve> b)
{
	return a->GetDouble() < b->GetDouble();
}

int main()
{
	std::vector<std::shared_ptr<Curve>> curves;

	for (int i = 0; i < 60; i++)
	{
		curves.push_back(CreateCurve(GetRandomInt(1,3)));
		if (typeid(*curves[i]).name() == typeid(Circle).name())
		{
			Circle circle = *std::dynamic_pointer_cast<Circle>(curves[i]);
			std::cout << typeid(Circle).name() << ": r = " << circle.r << std::endl;
		}
		else if (typeid(*curves[i]).name() == typeid(Elipse).name())
		{
			Elipse elipse = *std::dynamic_pointer_cast<Elipse>(curves[i]);
			std::cout << typeid(Elipse).name() << ": a = " << elipse.a << " b = " << elipse.b << std::endl;
		}
		else if (typeid(*curves[i]).name() == typeid(Spiral).name())
		{
			Spiral spiral = *std::dynamic_pointer_cast<Spiral>(curves[i]);
			std::cout << typeid(Spiral).name() << ": r = " << spiral.r << " step = " << spiral.step << std::endl;
		}

		std::uniform_int_distribution<> distType2(0, 50);
		double t = GetRandomDouble(0, 12 * M_PI);
		std::cout << "t = " << t << std::endl;
		Point point = curves[i]->GetPoint(t);
		std::cout << "C(t) = (" << point.x << "," << point.y << "," << point.z << ")" << std::endl;
		std::vector<double> fd = curves[i]->GetFD(t);
		std::cout << "dC(t)/dt = (" << fd[0] << "," << fd[1] << "," << fd[2] << ")" << std::endl;
		std::cout << std::endl;
	}

	std::vector<std::shared_ptr<Circle>> circles;
	std::cout << "The original array of circles (radii): ";
	for (int i = 0; i < curves.size(); i++)
	{
		if (std::dynamic_pointer_cast<Circle>(curves[i]) != nullptr)
		{
			std::shared_ptr<Circle> c = std::dynamic_pointer_cast<Circle>(curves[i]);
			circles.push_back(c);
			std::cout << c->r << " ";
		}
	}
	std::cout << std::endl << std::endl;

	std::sort(circles.begin(), circles.end(), comp);
	std::cout << "Sorted array of circles (radii): ";
	for (int i = 0; i < circles.size(); i++)
	{
		std::cout << circles[i]->r << " ";
	}
	std::cout << std::endl << std::endl;

	double res = std::accumulate(circles.begin(), circles.end(), 0.0,
		[](double sum, const std::shared_ptr<Circle> next) { return sum + next->r; });

	std::cout << "Total sum of radii: " << res << std::endl;

	return 0;
}