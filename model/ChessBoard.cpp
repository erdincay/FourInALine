#include "ChessBoard.h"
#include "ChessMan.h"

namespace model
{
	using namespace std;

	ChessBoard::ChessBoard(int size, int goalSize)
		:size_(size),
		goalSize_(goalSize),
		pieces_()
	{

	}

	ChessBoard::ChessBoard(const ChessBoard & oth)
		:size_(oth.size_),
		goalSize_(oth.goalSize_),
		pieces_(oth.pieces_)
	{

	}

	ChessBoard::~ChessBoard()
	{
	}

	bool ChessBoard::NewChess(Coordinater coord, bool side)
	{
		if (!(coord.getX() > 0 && coord.getX() <= size_ && coord.getY() > 0 && coord.getY() <= size_))
		{
			return false;
		}

		return pieces_.AddChessMan(coord, side);
	}

	bool ChessBoard::IsTerminal()
	{
		if (pieces_.size() >= size_*size_)
		{
			return true;
		}

		return pieces_.IsTerminal(goalSize_);
	}
}