#pragma once

#include "../model/State.h"
#include "../action/Action.h"
#include <memory>
#include <vector>

typedef int typeEval;

namespace heuristic
{
	class Heuristic
	{
	public:
		Heuristic();
		virtual ~Heuristic();

		virtual typeEval eval(std::shared_ptr<model::State> s) = 0;
		virtual std::vector<std::shared_ptr<action::Action>> generateActions(std::shared_ptr<model::State> s) = 0;
	};

}

