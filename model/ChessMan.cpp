#include "ChessMan.h"

namespace model
{
	using namespace std;

	ChessMan::ChessMan(Coordinater c, bool side)
		:coord_(c),
		side_(side)
	{
		
	}

	ChessMan::ChessMan(const ChessMan & oth)
		: coord_(oth.coord_),
		side_(oth.side_)
	{

	}

	ChessMan::~ChessMan()
	{
	}

	bool ChessMan::getSide()
	{
		return side_;
	}

	Coordinater ChessMan::getCoord()
	{
		return coord_;
	}

	/************************************************************************
	pair.first is the adjacent direction relation                        
	pair.second the bool is the order relation for oth and this, this before oth == true                                                   
	************************************************************************/
	pair<adjacent,bool> ChessMan::Adjacent(std::shared_ptr<ChessMan> oth)
	{
		int diff_x = oth->getCoord().getX() - getCoord().getX();
		int diff_y = oth->getCoord().getY() - getCoord().getY();

		if (1 == abs(diff_x) && 0 == diff_y)
		{
			return make_pair(adjacent::row_adjacent, diff_x > 0);
		}
		else if (1 == abs(diff_y) && 0 == diff_x)
		{
			return make_pair(adjacent::col_adjacent, diff_y > 0);
		}
		
		return make_pair(adjacent::none_adjacent,false);
	}

	
}
