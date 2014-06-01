#pragma once

#include "Coordinater.h"

namespace model 
{
	enum class adjacent
	{
		col_adjacent,
		row_adjacent,
		none_adjacent
	};

	class ChessMan
	{
	public:
		ChessMan(Coordinater c, bool side);
		ChessMan(const ChessMan & oth);
		~ChessMan();

		bool getSide();
		Coordinater getCoord();

		std::pair<adjacent,bool> Adjacent(std::shared_ptr<ChessMan> oth);
		
	private:
		bool side_;
		Coordinater coord_;
	};

}

