#include "EvaluationWeight.h"
#include "../model/ChessBoard.h"
#include "../model/Coordinater.h"
namespace heuristic
{
	using namespace std;
	using namespace model;
	EvaluationWeight::EvaluationWeight()
	{
	}


	EvaluationWeight::~EvaluationWeight()
	{
	}

	typeEval EvaluationWeight::eval(shared_ptr<model::State> s, bool side)
	{
		shared_ptr<ChessBoard> newS = shared_ptr<ChessBoard>(new ChessBoard(*static_pointer_cast<ChessBoard>(s)));
		shared_ptr<ChessMen> chesses = newS->getPieces();
		typeEval result;
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

					switch (direction)
					{
					case adjacent::row_adjacent:
						if (direction == adjacent::row_adjacent)
						{
							Coordinater left(start.getX() - 1, start.getY());
							Coordinater right(end.getX() + 1, end.getY());

							auto find_ret = chesses->find(left);

							if (find_ret == chesses->end()) // not found
							{

							}
							else
							{
								auto coord = (*find_ret).first;
								auto chess = (*find_ret).second;
							}

							if (end.getX() - start.getX())
							{

							}

						}
						break;
					case adjacent::col_adjacent:
						break;
					case adjacent::none_adjacent:
						break;
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

	vector<shared_ptr<action::Action>> EvaluationWeight::generateActions(shared_ptr<model::State> s, bool side)
	{
		return vector<shared_ptr<action::Action>>();
	}
}