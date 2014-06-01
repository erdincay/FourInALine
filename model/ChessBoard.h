#pragma once

#include "State.h"
#include "ChessMen.h"

namespace model
{
	class ChessBoard : public State
	{
	public:
		ChessBoard(int size, int goalSize);
		ChessBoard(const ChessBoard & oth);
		virtual ~ChessBoard();

		bool IsTerminal();

		bool NewChess(Coordinater coord, bool side);

	private:
		int size_;
		int goalSize_;
		ChessMen pieces_;
	};
}