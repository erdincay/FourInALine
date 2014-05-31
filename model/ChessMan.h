#pragma once

#include "Coordinater.h"

namespace model 
{
	class ChessMan
	{
	public:
		ChessMan(Coordinater c, bool mine);
		~ChessMan();
		
	private:
		bool mine_;
		Coordinater coord;
	};

}

