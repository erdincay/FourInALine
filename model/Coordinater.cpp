#include "Coordinater.h"

namespace model
{
	using namespace std;

	Coordinater::Coordinater(int x, int y)
	{
		this->x_ = x;
		this->y_ = y;
	}

	Coordinater::Coordinater(string coord)
	{
		if (coord.length() != 2)
		{
			throw std::exception("invalid coordinate string");
		}

		char y = coord.front();
		char x = coord.back();

		x_ = atoi(&x);
		y_ = tolower(y) - 'a' + 1;
	}

	Coordinater::Coordinater(const Coordinater & oth)
	{
		this->x_ = oth.x_;
		this->y_ = oth.y_;
	}

	Coordinater::~Coordinater()
	{

	}

	int Coordinater::getX()
	{
		return x_;
	}

	int Coordinater::getY()
	{
		return y_;
	}

}
