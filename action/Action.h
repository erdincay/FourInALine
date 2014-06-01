#pragma once

#include <memory>

namespace model
{
	class State;
}

namespace action
{
	class Action
	{
	public:
		Action();
		virtual ~Action();

		virtual std::shared_ptr<model::State> act(std::shared_ptr<model::State> s) = 0;
	};

}

