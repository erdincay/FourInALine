#include "ChessBoard.h"

namespace model
{
	ChessBoard::ChessBoard(int size)
		:size_(size),
		pieces_()
	{

	}

	ChessBoard::~ChessBoard()
	{
	}

	ChessBoard::ChessBoard(const ChessBoard & oth)
		:size_(oth.size_),
		pieces_(oth.pieces_)
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

		return false;
	}
}