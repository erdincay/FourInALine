#pragma once

#include "../model/ChessBoard.h"

namespace solution
{
	class Minimax
	{
	public:
		Minimax(int size);
		~Minimax();

	private:
		model::ChessBoard borad_;
	};
}

