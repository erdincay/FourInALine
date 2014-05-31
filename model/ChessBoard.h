#pragma once

#include "State.h"
#include "ChessMen.h"

namespace model
{
	class ChessBoard : public State
	{
	public:
		ChessBoard(int size);
		virtual ~ChessBoard();

	private:
		int size_;
		ChessMen pieces_;
	};
}