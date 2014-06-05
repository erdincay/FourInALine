#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include "../model/Coordinater.h"

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
		virtual std::unordered_map<model::Coordinater, std::shared_ptr<action::Action>, model::Coordinater::KeyHasher> generateActions(std::shared_ptr<model::State> s, bool side) = 0;
	};

}

