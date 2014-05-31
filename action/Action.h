#pragma once

#include "../model/State.h"

namespace action
{
	class Action
	{
	public:
		Action();
		virtual ~Action();

		virtual model::State act(model::State s) = 0;
	};

}

