#pragma once

#include "../heuristic/Heuristic.h"
#include <memory>

namespace model
{
	class State;
	class ChessBoard;
}

namespace action
{
	class Action;
}

namespace solution
{
	class Minimax
	{
	public:
		Minimax(int size, std::shared_ptr<heuristic::Heuristic> h);
		~Minimax();

		std::shared_ptr<action::Action> Alpha_Beta_Search(std::shared_ptr<model::State> s);
		void Run();

	protected:
		std::pair<typeEval, std::shared_ptr<action::Action>> Max_Value(std::shared_ptr<model::State> s, typeEval alpha, typeEval beta);
		std::pair<typeEval, std::shared_ptr<action::Action>> Min_Value(std::shared_ptr<model::State> s, typeEval alpha, typeEval beta);

	private:
		std::shared_ptr<model::State> borad_;
		std::shared_ptr<heuristic::Heuristic> heuristic_;
	};
}

