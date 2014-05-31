#include "ChessBoard.h"

namespace model
{
	ChessBoard::ChessBoard(int size)
		:pieces_()
	{
		this->size_ = size;
	}

	ChessBoard::~ChessBoard()
	{
	}
}