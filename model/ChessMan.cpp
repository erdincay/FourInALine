#include "ChessMan.h"

namespace model
{

	ChessMan::ChessMan(Coordinater c, bool mine)
		:coord(c)
	{
		this->mine_ = mine;
	}


	ChessMan::~ChessMan()
	{
	}

}
