#include "EvaluationWeight.h"
#include "../model/ChessBoard.h"
#include "../model/Coordinater.h"
#include "../action/MoveTo.h"
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
		typeEval resultTrueSide;
		typeEval resultFalseSide;
		auto linear_statistics = chesses->getStatistics();
		for (auto statistic : *linear_statistics)
		{
			for (auto linears : *(statistic.second))
			{
				for (auto linear : *(linears.second))
				{
					auto size = linear->size();
					auto direction = linear->getDirection();
					auto start = linear->getStart()->getCoord();
					auto end = linear->getEnd()->getCoord();
					auto currentSide = linear->getStart()->getSide();
					auto available = board->getLinearAvailable(linear);
					// True side
					if (side == true)
					{
						switch (available)
						{
						case model::avarible::before_avarible:
							if (currentSide == true) // evaluation self
							{
								if (size == 2)
								{
									resultTrueSide = resultTrueSide + 2;

								}
								else if (size == 3)
								{
									resultTrueSide = resultTrueSide + 5;
									// check double dead 3 
									if (direction == adjacent::row_adjacent)
									{
										resultTrueSide = EvaluationWeight::evalLinearRow(board, strMyRow, start);
									}
									else if (direction == adjacent::col_adjacent)
									{
										resultTrueSide = EvaluationWeight::evalLinearCol(board, strMyRow, start);
									}
								}
							}
							else // evaluation opponent
							{

							}
							break;
						case model::avarible::after_avarible:
							if (currentSide == true) // evaluation self
							{
								if (size == 2)
								{
									resultTrueSide = resultTrueSide + 2;
								}
								else if (size == 3)
								{
									resultTrueSide = resultTrueSide + 5;
								}
							}
							else // evaluation opponent
							{

							}
							break;
						case model::avarible::both_avarible:
							if (currentSide == true) // evaluation self
							{
								if (size == 2)
								{
									resultTrueSide = resultTrueSide + 3;
									// check double live 2 and dead 3 + live 2
									if (direction == adjacent::row_adjacent)
									{
										resultTrueSide = EvaluationWeight::evalLinearRow(board, strMyRow, start);
									}
									else if (direction == adjacent::col_adjacent)
									{
										resultTrueSide = EvaluationWeight::evalLinearCol(board, strMyRow, start);
									}
								}
								else if (size == 3)
								{
									resultTrueSide = resultTrueSide + 30;
								}
							}
							else // evaluation opponent
							{

							}
							break;
						case model::avarible::none_avarible:
							break;
						case model::avarible::error:
							if (currentSide == true) // evaluation self
							{
								if (size == 1)
								{
									if (chesses->count(Coordinater(start.getX() - 1, start.getY())) <= 0)
										resultTrueSide = resultTrueSide + 1;
									if (chesses->count(Coordinater(start.getX() + 1, start.getY())) <= 0)
										resultTrueSide = resultTrueSide + 1;
									if (chesses->count(Coordinater(start.getX(), start.getY() - 1)) <= 0)
										resultTrueSide = resultTrueSide + 1;
									if (chesses->count(Coordinater(start.getX(), start.getY() + 1)) <= 0)
										resultTrueSide = resultTrueSide + 1;
								}
							}
							else // evaluation opponent
							{

							}
							break;
						default:
							break;
						}
						//switch (direction)
						//{
						//case adjacent::row_adjacent:
						//	if (direction == adjacent::row_adjacent)
						//	{
						//		
						//		//Coordinater left(start.getX() - 1, start.getY());
						//		//Coordinater right(end.getX() + 1, end.getY());
						//		//auto find_ret = chesses->find(left);
						//		//if (find_ret == chesses->end()) // not found
						//		//{
						//		//}
						//		//else
						//		//{
						//		//	auto coord = (*find_ret).first;
						//		//	auto chess = (*find_ret).second;
						//		//}
						//		//if (end.getX() - start.getX())
						//		//{
						//		//}
						//	}
						//	break;
						//case adjacent::col_adjacent:
						//	break;
						//case adjacent::none_adjacent:
						//	break;
						//}
					}
					else // False side
					{
						// evaluation self
						// evaluation opponent
					}
					
				}
			}
		}

		//double live 2
		//double dead 3
		//dead 3 + live 2
		//live 3
		return 0;
	}

	unordered_map<Coordinater, shared_ptr<action::Action>, model::Coordinater::KeyHasher> EvaluationWeight::generateActions(shared_ptr<model::State> s, bool side)
	{
		unordered_map<Coordinater, shared_ptr<action::Action>, model::Coordinater::KeyHasher> possibleActions;
		shared_ptr<ChessBoard> newS = static_pointer_cast<ChessBoard>(s);
		shared_ptr<ChessMen> chesses = newS->getPieces();
		for (int i = 1; newS->getSize(); i++)
		{
			for (int j = 1; newS->getSize(); j++)
			{
				Coordinater checkPosition(i, j);
				if (chesses->count(checkPosition) > 0)
				{
					Coordinater top(i, j + 1);
					Coordinater bottom(i, j - 1);
					Coordinater left(i - 1, j);
					Coordinater right(i + 1, j);

					if (newS->InsideBoundary(top) && chesses->count(top) <= 0)
					{
						possibleActions[top] = shared_ptr<Action>(new MoveTo(top, side));
					}
					
					if (newS->InsideBoundary(bottom) && chesses->count(bottom) <= 0)
					{
						possibleActions[bottom] = shared_ptr<Action>(new MoveTo(bottom, side));
					}

					if (newS->InsideBoundary(left) && chesses->count(left) <= 0)
					{
						possibleActions[left] = shared_ptr<Action>(new MoveTo(left, side));
					}

					if (newS->InsideBoundary(right) && chesses->count(right) <= 0)
					{
						possibleActions[right] = shared_ptr<Action>(new MoveTo(right, side));
					}
				}

			}
		}

		return possibleActions;
	}

	typeEval EvaluationWeight::evalLinearRow(std::shared_ptr<model::ChessBoard> board, std::string key, model::Coordinater coord)
	{
		typeEval result;
		//auto find_linears = linear_statistics->find("MyCol")->second->find(start.getX())->second;
		auto linear_statistics = board->getPieces()->getStatistics();
		auto find_types = linear_statistics->find(key);
		if (find_types != linear_statistics->end())
		{
			auto find_linears = find_types->second;
			auto find_linear = find_linears->find(coord.getX());
			if (find_linear != find_linears->end())
			{
				for (auto it : *find_linear->second)
				{
					if (board->getLinearAvailable(it) == model::avarible::both_avarible && (it)->size() == 2 && (it)->getStart()->getCoord().getY() < coord.getY() && coord.getY() < (it)->getEnd()->getCoord().getY())
					{
						result = result + 10; // Yes!!!!!! double live 2
					}
					else if ((it)->size() == 3)
					{
						if (board->getLinearAvailable(it) == model::avarible::before_avarible || board->getLinearAvailable(it) == model::avarible::after_avarible)
						{
							if ((it)->getStart()->getCoord().getY() < coord.getY() && coord.getY() < (it)->getEnd()->getCoord().getY())
							{
								result = result + 10; // Yes!!!!!! dead 3 + live 2
							}
						}
					}
				}
			}
		}
		return result;
	}

	typeEval evalLinearCol(std::shared_ptr<model::ChessBoard> board, std::string key, model::Coordinater coord)
	{
		typeEval result;
		auto linear_statistics = board->getPieces()->getStatistics();
		auto find_types = linear_statistics->find(key);
		if (find_types != linear_statistics->end())
		{
			auto find_linears = find_types->second;
			auto find_linear = find_linears->find(coord.getY());
			if (find_linear != find_linears->end())
			{
				for (auto it : *find_linear->second)
				{
					if (board->getLinearAvailable(it) == model::avarible::both_avarible && (it)->size() == 2 && (it)->getStart()->getCoord().getX() < coord.getX() && coord.getX() < (it)->getEnd()->getCoord().getX())
					{
						result = result + 10; // Yes!!!!!! double live 2
					}
					else if ((it)->size() == 3)
					{
						if (board->getLinearAvailable(it) == model::avarible::before_avarible || board->getLinearAvailable(it) == model::avarible::after_avarible)
						{
							if ((it)->getStart()->getCoord().getX() < coord.getX() && coord.getX() < (it)->getEnd()->getCoord().getX())
							{
								result = result + 10; // Yes!!!!!! dead 3 + live 2
							}
						}
					}
				}
			}
		}
		return result;
	}
}