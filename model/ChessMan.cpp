#include "ChessMan.h"

namespace model
{

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

}
