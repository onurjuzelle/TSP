#include "header/city.h"


City::City(int id, int x, int y)
{
	this->id = id;
	this->x = x;
	this->y = y;
}

City::~City()
{
}

int City::get_id()
{
    return id;
}

int City::get_x()
{
    return x;
}

int City::get_y()
{
    return y;
}

double City::distance(City& c)
{
	
	double x2 = c.get_x();
	double y2 = c.get_y();

	x2 -= x;
	y2 -= y;

	return sqrt(pow(x2, 2) + pow(y2, 2));
}
