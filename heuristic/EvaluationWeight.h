#pragma once
#include "C:\Users\Mark Lai\Documents\fourinaline\heuristic\Heuristic.h"

namespace heuristic
{
	class EvaluationWeight :
		public Heuristic
	{
	public:
		EvaluationWeight();
		virtual ~EvaluationWeight();
		typeEval eval(std::shared_ptr<model::State> s, bool side);
		std::vector<std::shared_ptr<action::Action>> generateActions(std::shared_ptr<model::State> s, bool side);
	};
}
