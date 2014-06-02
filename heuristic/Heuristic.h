#pragma once

#include <memory>
#include <vector>

namespace model
{
	class State;
}

namespace action
{
	class Action;
}

namespace heuristic
{
	typedef int typeEval;

	class Heuristic
	{
	public:
		Heuristic();
		virtual ~Heuristic();

		virtual typeEval eval(std::shared_ptr<model::State> s, bool side) = 0;
		virtual std::vector<std::shared_ptr<action::Action>> generateActions(std::shared_ptr<model::State> s, bool side) = 0;
	};

}

