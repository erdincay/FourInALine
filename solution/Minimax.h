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
	class Timer;

	class Minimax
	{
	public:
		Minimax(int size, int goalSize, std::shared_ptr<heuristic::Heuristic> h, int time_duration /* unit: seconds*/);
		~Minimax();

		std::shared_ptr<action::Action> Alpha_Beta_Search(std::shared_ptr<model::State> s);
		void Run();

	protected:
		std::pair<heuristic::typeEval, std::shared_ptr<action::Action>> Max_Value(std::shared_ptr<model::State> s, heuristic::typeEval alpha, heuristic::typeEval beta, int deep, Timer & timer);
		std::pair<heuristic::typeEval, std::shared_ptr<action::Action>> Min_Value(std::shared_ptr<model::State> s, heuristic::typeEval alpha, heuristic::typeEval beta, int deep, Timer & timer);

	private:
		std::shared_ptr<model::State> borad_;
		std::shared_ptr<heuristic::Heuristic> heuristic_;
		int time_duration_; /* unit: seconds*/
	};
}

