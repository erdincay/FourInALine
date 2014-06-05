#pragma once
#include <string>
#include "Coordinater.h"

namespace model
{
	class State
	{
	public:
		State();
		virtual ~State();

		virtual std::string toString() = 0;
		virtual bool IsTerminal() = 0;
		virtual bool NewChess(Coordinater coord, bool side) = 0;
	};

}

