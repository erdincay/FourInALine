#pragma once

#include "../heuristic/Heuristic.h"
#include <memory>
//#include <boost/asio/deadline_timer.hpp>

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
		//Minimax(int size, int goalSize, std::shared_ptr<heuristic::Heuristic> h, boost::asio::io_service & io_service);
		Minimax(int size, int goalSize, std::shared_ptr<heuristic::Heuristic> h);
		~Minimax();

		std::shared_ptr<action::Action> Alpha_Beta_Search(std::shared_ptr<model::State> s);
		void Run();

	protected:
		std::pair<heuristic::typeEval, std::shared_ptr<action::Action>> Max_Value(std::shared_ptr<model::State> s, heuristic::typeEval alpha, heuristic::typeEval beta, int deep);
		std::pair<heuristic::typeEval, std::shared_ptr<action::Action>> Min_Value(std::shared_ptr<model::State> s, heuristic::typeEval alpha, heuristic::typeEval beta, int deep);

	private:
		std::shared_ptr<model::State> borad_;
		std::shared_ptr<heuristic::Heuristic> heuristic_;
		//boost::asio::deadline_timer timer_;
	};
}

