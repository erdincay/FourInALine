#include "Evaluate.h"
#include "../model/ChessBoard.h"

using namespace std;

namespace heuristic
{
	Evaluate::Evaluate()
	{
	
	}

	Evaluate::Evaluate(std::shared_ptr<model::ChessLinear> linear)
	{
		this->linear_ = linear;
	}


	Evaluate::~Evaluate()
	{
	}

	std::vector<typeEval> Evaluate::oneAvailable(std::shared_ptr<model::ChessBoard> board, bool currentSide, int DD3True, int DD3False)
	{
		vector<typeEval> result;
		typeEval resultTrueSide = 0;
		typeEval resultFalseSide = 0;
		auto direction = this->linear_->getDirection();
		auto start = this->linear_->getStart()->getCoord();
		auto size = this->linear_->size();
		if (currentSide == true) // evaluate True
		{
			if (size == 2)
			{
				resultTrueSide += TWO_CHESSMAN_ONE_AVAILABLE;
			}
			else if (size == 3)
			{
				resultTrueSide += THREE_CHESSMAN_ONE_AVAILABLE;
				// check double dead 3 
				if (direction == model::adjacent::row_adjacent)
				{
					resultTrueSide += evalLinearDD3Row(board, model::strMyCol, start, DD3True); // if it has double dead 3, add 10
				}
				else if (direction == model::adjacent::col_adjacent)
				{
					resultTrueSide += evalLinearDD3Col(board, model::strMyRow, start, DD3True); // if it has double dead 3, add 10
				}
			}
		}
		else // // evaluate False 
		{
			if (size == 2)
			{
				resultFalseSide += TWO_CHESSMAN_ONE_AVAILABLE;
			}
			else if (size == 3)
			{
				resultFalseSide += THREE_CHESSMAN_ONE_AVAILABLE;
				// check double dead 3 
				if (direction == model::adjacent::row_adjacent)
				{
					resultFalseSide += evalLinearDD3Row(board, model::strOppositeCol, start, DD3False); // if it has double dead 3, add 30
				}
				else if (direction == model::adjacent::col_adjacent)
				{
					resultFalseSide += evalLinearDD3Col(board, model::strOppositeRow, start, DD3False); // if it has double dead 3, add 30
				}
			}
			
		}

		result.push_back(resultTrueSide); // the first is true evaluation
		result.push_back(resultFalseSide); // the second is true evaluation
		return result;
	}

	std::vector<typeEval> Evaluate::twoAvailable(std::shared_ptr<model::ChessBoard> board, bool nextSide, bool currentSide, int DL2True, int DL2False, int L2D3True, int L2D3False)
	{
		vector<typeEval> result;
		typeEval resultTrueSide = 0;
		typeEval resultFalseSide = 0;
		auto direction = this->linear_->getDirection();
		auto start = this->linear_->getStart()->getCoord();
		auto size = this->linear_->size();
		if (currentSide == true) // evaluation self
		{
			if (size == 2)
			{
				if (nextSide == true)
				{
					resultTrueSide += (TWO_CHESSMAN_BOTH_AVAILABLE + EXTRA_PLUS);
				}
				else
				{
					resultTrueSide += TWO_CHESSMAN_BOTH_AVAILABLE;
				}
				
				// check double live 2 and dead 3 + live 2
				if (direction == model::adjacent::row_adjacent)
				{
					// if it has double live 2, add 30. If it has live 2 + dead 3, add 30
					resultTrueSide += evalLinearRow(board, model::strMyCol, start, DL2True, L2D3True);
				}
				else if (direction == model::adjacent::col_adjacent)
				{
					// if it has double live 2, add 30. If it has live 2 + dead 3, add 30
					resultTrueSide += evalLinearCol(board, model::strMyRow, start, DL2True, L2D3True);
				}
			}
			else if (size == 3)
			{
				if (nextSide == true)
				{
					resultTrueSide += (THREE_CHESEMAN_BOTH_AVAILABLE +EXTRA_PLUS);
				}
				else
				{
					resultTrueSide += THREE_CHESEMAN_BOTH_AVAILABLE;
				}
				
			}
		}
		else // evaluation opponent
		{
			if (size == 2)
			{
				if (nextSide == false)
				{
					resultFalseSide += (TWO_CHESSMAN_BOTH_AVAILABLE + EXTRA_PLUS);
				}
				else
				{
					resultFalseSide += TWO_CHESSMAN_BOTH_AVAILABLE;
				}
				// check double live 2 and dead 3 + live 2
				if (direction == model::adjacent::row_adjacent)
				{
					// if it has double live 2, add 30. If it has live 2 + dead 3, add 30
					resultFalseSide += evalLinearRow(board, model::strOppositeCol, start, DL2False, L2D3False);
				}
				else if (direction == model::adjacent::col_adjacent)
				{
					// if it has double live 2, add 30. If it has live 2 + dead 3, add 30
					resultFalseSide += evalLinearCol(board, model::strOppositeRow, start, DL2False, L2D3False);
				}
			}
			else if (size == 3)
			{
				if (nextSide == false)
				{
					resultFalseSide += (THREE_CHESEMAN_BOTH_AVAILABLE + EXTRA_PLUS);
				}
				else
				{
					resultFalseSide += THREE_CHESEMAN_BOTH_AVAILABLE;
				}
				
			}
		}
		result.push_back(resultTrueSide); // the first is true evaluation
		result.push_back(resultFalseSide); // the second is true evaluation
		return result;
	}

	std::vector<typeEval> Evaluate::noneAvailable(std::shared_ptr<model::ChessBoard> board, bool currentSide)
	{
		vector<typeEval> result;
		typeEval resultTrueSide = 0;
		typeEval resultFalseSide = 0;
		auto direction = this->linear_->getDirection();
		auto start = this->linear_->getStart()->getCoord();
		auto size = this->linear_->size();
		if (currentSide == true) // evaluation self
		{
			if (size == 1)
			{
				if (board->getPieces()->count(model::Coordinater(start.getX() - 1, start.getY())) <= 0)
					resultTrueSide += ONE_CHESSMAN;
				if (board->getPieces()->count(model::Coordinater(start.getX() + 1, start.getY())) <= 0)
					resultTrueSide += ONE_CHESSMAN;
				if (board->getPieces()->count(model::Coordinater(start.getX(), start.getY() - 1)) <= 0)
					resultTrueSide += ONE_CHESSMAN;
				if (board->getPieces()->count(model::Coordinater(start.getX(), start.getY() + 1)) <= 0)
					resultTrueSide += ONE_CHESSMAN;
			}
		}
		else // evaluation opponent
		{
			if (size == 1)
			{
				if (board->getPieces()->count(model::Coordinater(start.getX() - 1, start.getY())) <= 0)
					resultFalseSide += ONE_CHESSMAN;
				if (board->getPieces()->count(model::Coordinater(start.getX() + 1, start.getY())) <= 0)
					resultFalseSide += ONE_CHESSMAN;
				if (board->getPieces()->count(model::Coordinater(start.getX(), start.getY() - 1)) <= 0)
					resultFalseSide += ONE_CHESSMAN;
				if (board->getPieces()->count(model::Coordinater(start.getX(), start.getY() + 1)) <= 0)
					resultFalseSide += ONE_CHESSMAN;
			}
		}

		result.push_back(resultTrueSide); // the first is true evaluation
		result.push_back(resultFalseSide); // the second is true evaluation
		return result;
	}


	typeEval Evaluate::evalLinearRow(std::shared_ptr<model::ChessBoard> board, std::string colType, model::Coordinater coord, int doubleLive2, int live2Dead3)
	{
		typeEval result = 0;
		//auto find_linears = linear_statistics->find("MyCol")->second->find(start.getX())->second;
		auto linear_statistics = board->getPieces()->getStatistics();
		auto find_types = linear_statistics->find(colType);
		if (find_types != linear_statistics->end())
		{
			auto find_linears = find_types->second;
			auto find_linear = find_linears->find(coord.getX());
			if (find_linear != find_linears->end())
			{
				for (auto it : *find_linear->second)
				{
					if (board->getLinearAvailable(it) == model::avarible::both_avarible && (it)->size() == 2 && (it)->getStart()->getCoord().getY() <= coord.getY() && coord.getY() <= (it)->getEnd()->getCoord().getY())
					{
						result = result + doubleLive2; // Yes!!!!!! double live 2
					}
					else if ((it)->size() == 3)
					{
						if (board->getLinearAvailable(it) == model::avarible::before_avarible || board->getLinearAvailable(it) == model::avarible::after_avarible)
						{
							if ((it)->getStart()->getCoord().getY() <= coord.getY() && coord.getY() <= (it)->getEnd()->getCoord().getY())
							{
								result = result + live2Dead3; // Yes!!!!!! dead 3 + live 2
							}
						}
					}
				}
			}
		}
		return result;
	}

	typeEval Evaluate::evalLinearCol(std::shared_ptr<model::ChessBoard> board, std::string rowType, model::Coordinater coord, int doubleLive2, int live2Dead3)
	{
		typeEval result = 0;
		auto linear_statistics = board->getPieces()->getStatistics();
		auto find_types = linear_statistics->find(rowType);
		if (find_types != linear_statistics->end())
		{
			auto find_linears = find_types->second;
			auto find_linear = find_linears->find(coord.getY());
			if (find_linear != find_linears->end())
			{
				for (auto it : *find_linear->second)
				{
					if (board->getLinearAvailable(it) == model::avarible::both_avarible && (it)->size() == 2 && (it)->getStart()->getCoord().getX() <= coord.getX() && coord.getX() <= (it)->getEnd()->getCoord().getX())
					{
						result = result + 10; // Yes!!!!!! double live 2
					}
					else if ((it)->size() == doubleLive2)
					{
						if (board->getLinearAvailable(it) == model::avarible::before_avarible || board->getLinearAvailable(it) == model::avarible::after_avarible)
						{
							if ((it)->getStart()->getCoord().getX() <= coord.getX() && coord.getX() <= (it)->getEnd()->getCoord().getX())
							{
								result = result + live2Dead3; // Yes!!!!!! dead 3 + live 2
							}
						}
					}
				}
			}
		}
		return result;
	}

	

	typeEval Evaluate::evalLinearDD3Row(std::shared_ptr<model::ChessBoard> board, std::string colType, model::Coordinater coord, int doubleDead3)
	{
		typeEval result = 0;
		auto linear_statistics = board->getPieces()->getStatistics();
		auto find_types = linear_statistics->find(colType);
		if (find_types != linear_statistics->end())
		{
			auto find_linears = find_types->second;
			auto find_linear = find_linears->find(coord.getX());
			if (find_linear != find_linears->end())
			{
				for (auto it : *find_linear->second)
				{
					if ((it)->size() == 3)
					{
						if (board->getLinearAvailable(it) == model::avarible::before_avarible || board->getLinearAvailable(it) == model::avarible::after_avarible)
						{
							if ((it)->getStart()->getCoord().getY() <= coord.getY() && coord.getY() <= (it)->getEnd()->getCoord().getY())
							{
								result = result + doubleDead3; // Yes!!!!!! double dead 3
							}
						}
					}
				}
			}
		}
		return result;
	}

	typeEval Evaluate::evalLinearDD3Col(std::shared_ptr<model::ChessBoard> board, std::string rowType, model::Coordinater coord, int doubleDead3)
	{
		typeEval result = 0;
		auto linear_statistics = board->getPieces()->getStatistics();
		auto find_types = linear_statistics->find(rowType);
		if (find_types != linear_statistics->end())
		{
			auto find_linears = find_types->second;
			auto find_linear = find_linears->find(coord.getY());
			if (find_linear != find_linears->end())
			{
				for (auto it : *find_linear->second)
				{
					if ((it)->size() == 3)
					{
						if (board->getLinearAvailable(it) == model::avarible::before_avarible || board->getLinearAvailable(it) == model::avarible::after_avarible)
						{
							if ((it)->getStart()->getCoord().getX() <= coord.getX() && coord.getX() <= (it)->getEnd()->getCoord().getX())
							{
								result = result + doubleDead3; // Yes!!!!!! double dead 3
							}
						}
					}
				}
			}
		}
		return result;
	}
}

