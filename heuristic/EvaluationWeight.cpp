#include "EvaluationWeight.h"
#include "../model/ChessBoard.h"
#include "../model/Coordinater.h"
#include "../action/MoveTo.h"
#include "../heuristic/Evaluate.h"
#include <iostream>

namespace heuristic
{
	using namespace std;
	using namespace model;
	using namespace action;
	EvaluationWeight::EvaluationWeight()
	{
	}


	EvaluationWeight::~EvaluationWeight()
	{
	}

	typeEval EvaluationWeight::eval(shared_ptr<model::State> s, bool side)
	{
		/*shared_ptr<ChessBoard> newS = shared_ptr<ChessBoard>(new ChessBoard(*static_pointer_cast<ChessBoard>(s)));*/
		shared_ptr<ChessBoard> board = static_pointer_cast<ChessBoard>(s);
		shared_ptr<ChessMen> chesses = board->getPieces();
		typeEval resultTrueSide = 0;
		typeEval resultFalseSide = 0;
		auto linear_statistics = chesses->getStatistics();
		for (auto statistic : *linear_statistics)
		{
			for (auto linears : *(statistic.second))
			{
				for (auto linear : *(linears.second))
				{
					auto currentSide = linear->getStart()->getSide();
					auto available = board->getLinearAvailable(linear);
					Evaluate evaluateFn(linear);
					// the next is True
					if (side == true)
					{
						switch (available)
						{
						case model::avarible::before_avarible: /* before_avarible and  after_avarible are the same situation */
						{
							vector<typeEval> tempEval = evaluateFn.oneAvailable(board, currentSide, 15, 10); // double dead 3 (true side) : 30 , double dead 3 (false side) : 100
							resultTrueSide += tempEval[0];
							resultFalseSide += tempEval[1];
						}
							break;
						case model::avarible::after_avarible:
						{
							vector<typeEval> tempEval = evaluateFn.oneAvailable(board, currentSide, 15, 10); // double dead 3 (true side) : 30 , double dead 3 (false side) : 100
							resultTrueSide += tempEval[0];
							resultFalseSide += tempEval[1];
						}
							break;
						case model::avarible::both_avarible:
						{
							// double live 2 (true side) : 30, double live 2 (false side) : 80, live 2 + dead 3 (true side) : 35 , live 2 + dead 3 (false side) : 85 
							vector<typeEval> tempEval = evaluateFn.twoAvailable(board, currentSide, side, 15, 10, 15, 10);
							resultTrueSide += tempEval[0];
							resultFalseSide += tempEval[1];
						}
							break;
						case model::avarible::none_avarible:
						{
							vector<typeEval> tempEval = evaluateFn.noneAvailable(board, currentSide);
							resultTrueSide += tempEval[0];
							resultFalseSide += tempEval[1];
						}
							break;
						case model::avarible::error:
							break;
						default:
							break;
						}
						
					}
					else // the next is False
					{
						switch (available)
						{
						case model::avarible::before_avarible:
						{
							vector<typeEval> tempEval = evaluateFn.oneAvailable(board, currentSide, 10, 25);
							resultTrueSide += tempEval[0];
							resultFalseSide += tempEval[1];
						}
							break;
						case model::avarible::after_avarible:
						{
							vector<typeEval> tempEval = evaluateFn.oneAvailable(board, currentSide, 10, 25);
							resultTrueSide += tempEval[0];
							resultFalseSide += tempEval[1];
						}
							break;
						case model::avarible::both_avarible:
						{
							vector<typeEval> tempEval = evaluateFn.twoAvailable(board, currentSide, side, 10, 25, 10, 25);
							resultTrueSide += tempEval[0];
							resultFalseSide += tempEval[1];
						}
							break;
						case model::avarible::none_avarible:
						{
							vector<typeEval> tempEval = evaluateFn.noneAvailable(board, currentSide);
							resultTrueSide += tempEval[0];
							resultFalseSide += tempEval[1];
						}
							break;
						case model::avarible::error:
							break;
						default:
							break;
						}
					}
				}
			}
		}
		//cout << "Side is " << side << endl;
		//double live 2
		//double dead 3
		//dead 3 + live 2
		//live 3
		//return resultTrueSide - resultFalseSide;
		return resultTrueSide;
	}

	unordered_map<Coordinater, shared_ptr<action::Action>, model::Coordinater::KeyHasher> EvaluationWeight::generateActions(shared_ptr<model::State> s, bool side)
	{
		unordered_map<Coordinater, shared_ptr<action::Action>, model::Coordinater::KeyHasher> possibleActions;
		shared_ptr<ChessBoard> board = static_pointer_cast<ChessBoard>(s);
		shared_ptr<ChessMen> chesses = board->getPieces();

		bool empty_board = true;

		for (int i = 1; i <= board->getSize(); i++)
		{
			for (int j = 1; j <= board->getSize(); j++)
			{
				Coordinater checkPosition(i, j);
				if (chesses->count(checkPosition) > 0)
				{
					empty_board = false;

					Coordinater top(i, j + 1);
					Coordinater bottom(i, j - 1);
					Coordinater left(i - 1, j);
					Coordinater right(i + 1, j);

					if (board->InsideBoundary(top) && chesses->count(top) <= 0)
					{
						possibleActions[top] = shared_ptr<Action>(new MoveTo(top, side));
					}
					
					if (board->InsideBoundary(bottom) && chesses->count(bottom) <= 0)
					{
						possibleActions[bottom] = shared_ptr<Action>(new MoveTo(bottom, side));
					}

					if (board->InsideBoundary(left) && chesses->count(left) <= 0)
					{
						possibleActions[left] = shared_ptr<Action>(new MoveTo(left, side));
					}

					if (board->InsideBoundary(right) && chesses->count(right) <= 0)
					{
						possibleActions[right] = shared_ptr<Action>(new MoveTo(right, side));
					}
				}

			}
		}

		if (possibleActions.size() == 0 && empty_board)
		{
			Coordinater center(board->getSize() / 2, board->getSize() / 2);
			possibleActions[center] = shared_ptr<Action>(new MoveTo(center, side));
		}

		return possibleActions;
	}

}