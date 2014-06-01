#pragma once
#include "Action.h"
#include "../model/Coordinater.h"

namespace action
{
	class MoveTo :
		public Action
	{
	public:
		MoveTo(model::Coordinater coord, bool side);
		virtual ~MoveTo();

		std::shared_ptr<model::State> act(std::shared_ptr<model::State> s);

		bool getSide();
		model::Coordinater getCoordinater();

	private:
		model::Coordinater destination_;
		bool chess_side_;
	};
}

