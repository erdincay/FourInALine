#include "Minimax.h"
#include "../model/ChessBoard.h"
#include "../action/Action.h"

namespace solution
{
	using namespace std;
	using namespace heuristic;
	using namespace model;
	using namespace action;

	Minimax::Minimax(int size, int goalSize, shared_ptr<Heuristic> h)
		:heuristic_(h),
		borad_(shared_ptr<State>(new ChessBoard(size, goalSize)))
	{

	}


	Minimax::~Minimax()
	{
	}

	pair<typeEval, shared_ptr<action::Action>> Minimax::Max_Value(shared_ptr<model::State> s, typeEval alpha, typeEval beta)
	{
		if (s->IsTerminal())
		{
			return make_pair(heuristic_->eval(s), shared_ptr<Action>(NULL));
		}

		auto v = make_pair(numeric_limits<typeEval>::min(), shared_ptr<Action>(NULL));

		for (auto action : heuristic_->generateActions(s))
		{
			v.second = action;
			shared_ptr<State> newState = action->act(s);
			auto newV = Min_Value(newState, alpha, beta);
			v.first = v.first > newV.first ? v.first : newV.first;

			if (v.first >= beta)
			{
				return v;
			}

			alpha = max(alpha, v.first);
		}

		return v;
	}

	pair<typeEval, shared_ptr<action::Action>> Minimax::Min_Value(shared_ptr<model::State> s, typeEval alpha, typeEval beta)
	{
		if (s->IsTerminal())
		{
			return make_pair(heuristic_->eval(s), shared_ptr<Action>(NULL));
		}

		auto v = make_pair(numeric_limits<typeEval>::min(), shared_ptr<Action>(NULL));

		for (auto action : heuristic_->generateActions(s))
		{
			v.second = action;
			shared_ptr<State> newState = action->act(s);
			auto newV = Max_Value(newState, alpha, beta);
			v.first = v.first < newV.first ? v.first : newV.first;

			if (v.first <= alpha)
			{
				return v;
			}

			beta = min(beta, v.first);
		}

		return v;
	}

	shared_ptr<Action> Minimax::Alpha_Beta_Search(shared_ptr<model::State> s)
	{
		return Max_Value(s, numeric_limits<typeEval>::min(), numeric_limits<typeEval>::max()).second;
	}

	void Minimax::Run() 
	{
		auto bestAction = Alpha_Beta_Search(borad_);
		borad_ = bestAction->act(borad_);
	}
}
