#pragma once

#include "../model/State.h"

namespace heuristic
{
	class Heuristic
	{
	public:
		Heuristic();
		virtual ~Heuristic();

		virtual int eval(model::State s) = 0;
	};

}

