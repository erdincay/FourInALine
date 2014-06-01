#pragma once

#include "../model/State.h"
#include <memory>

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

