#pragma once

#include "Coordinater.h"

namespace model 
{
	class ChessMan
	{
	public:
		ChessMan(Coordinater c, bool side);
		ChessMan(const ChessMan & oth);
		~ChessMan();
		
	private:
		bool side_;
		Coordinater coord_;
	};

}

