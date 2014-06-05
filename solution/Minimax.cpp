#include "Minimax.h"
#include "../model/ChessBoard.h"
#include "../action/Action.h"
#include "Timer.h"

namespace solution
{
	using namespace std;
	using namespace heuristic;
	using namespace model;
	using namespace action;

	Minimax::Minimax(int size, int goalSize, shared_ptr<Heuristic> h, int time_duration /* unit: seconds*/)
		:heuristic_(h),
		borad_(shared_ptr<State>(new ChessBoard(size, goalSize))),
		time_duration_(time_duration)
	{

	}

	Minimax::Minimax(int size, int goalSize, shared_ptr<Heuristic> h, shared_ptr<State> s, int time_duration /* unit: seconds*/)
		:heuristic_(h),
		borad_(s),
		time_duration_(time_duration)
	{

	}


	Minimax::~Minimax()
	{
	}

	pair<typeEval, shared_ptr<action::Action>> Minimax::Max_Value(shared_ptr<model::State> s, typeEval alpha, typeEval beta, int deep, Timer & timer)
	{
		if (s->IsTerminal() || timer.TimeOver())
		{
			return make_pair(heuristic_->eval(s,true), shared_ptr<Action>(NULL));
		}

		auto v = make_pair(numeric_limits<typeEval>::min(), shared_ptr<Action>(NULL));

		for (auto action_map : heuristic_->generateActions(s, true))
		{
			auto action = action_map.second;
			shared_ptr<State> newState = action->act(s);
			auto newV = Min_Value(newState, alpha, beta, ++deep, timer);
			newV.second = action;

			v = v.first > newV.first ? v : newV;

			if (v.first >= beta)
			{
				return v;
			}

			alpha = max(alpha, v.first);
		}

		return v;
	}

	pair<typeEval, shared_ptr<action::Action>> Minimax::Min_Value(shared_ptr<model::State> s, typeEval alpha, typeEval beta, int deep, Timer & timer)
	{
		if (s->IsTerminal() || timer.TimeOver())
		{
			return make_pair(heuristic_->eval(s, false), shared_ptr<Action>(NULL));
		}

		auto v = make_pair(numeric_limits<typeEval>::min(), shared_ptr<Action>(NULL));

		for (auto action_map : heuristic_->generateActions(s, false))
		{
			auto action = action_map.second;
			shared_ptr<State> newState = action->act(s);
			auto newV = Max_Value(newState, alpha, beta, ++deep, timer);
			newV.second = action;

			v = v.first < newV.first ? v : newV;

			if (v.first <= alpha)
			{
				return v;
			}

			beta = min(beta, v.first);
		}

		return v;
	}

	shared_ptr<model::State> Minimax::getCurState()
	{
		return borad_;
	}

	shared_ptr<Action> Minimax::Alpha_Beta_Search(shared_ptr<model::State> s)
	{
		Timer timer(time_duration_ * 1000 /*timer unit millisecond*/);
		return Max_Value(s, numeric_limits<typeEval>::min(), numeric_limits<typeEval>::max(), 0, timer).second;
	}

	shared_ptr<Action> Minimax::Run() 
	{
		auto bestAction = Alpha_Beta_Search(borad_);
		borad_ = bestAction->act(borad_);

		return bestAction;
	}
}
