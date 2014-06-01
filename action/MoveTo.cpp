#include "MoveTo.h"
#include "../model/ChessBoard.h"

namespace action
{
	using namespace std;
	using namespace model;

	MoveTo::MoveTo(Coordinater coord, bool side)
		:destination_(coord),
		chess_side_(side)
	{

	}


	MoveTo::~MoveTo()
	{
	}

	shared_ptr<State> MoveTo::act(const std::shared_ptr<State> s)
	{
		shared_ptr<ChessBoard> newS = shared_ptr<ChessBoard>(new ChessBoard(*static_pointer_cast<ChessBoard>(s)));
		if (newS->NewChess(destination_, chess_side_))
		{
			return newS;
		}

		return shared_ptr<State>(NULL);
	}

	bool MoveTo::getSide()
	{
		return chess_side_;
	}

	Coordinater MoveTo::getCoordinater()
	{
		return destination_;
	}
}
