#include "ChessMen.h"

namespace model
{
	using namespace std;

	ChessMen::ChessMen()
		:linear_statistics_(shared_ptr<typeStatistics>(new typeStatistics()))
	{
		
	}

	ChessMen::ChessMen(const ChessMen & oth) 
		: linear_statistics_(shared_ptr<typeStatistics>(new typeStatistics()))
	{
		for (const auto & elem : oth)
		{
			(*this)[elem.first] = shared_ptr<ChessMan>(new ChessMan(*elem.second));
		}

		for (auto statistic : *(oth.linear_statistics_))
		{
			auto newStatistic = shared_ptr<typeStatistic>(new typeStatistic);
			for (auto linears : *(statistic.second))
			{
				auto newLinears = shared_ptr<typeChessLinears>(new typeChessLinears());
				for (auto linear : *(linears.second))
				{
					auto newLinear = shared_ptr<ChessLinear>(new ChessLinear(*linear));
					newLinears->push_back(newLinear);
				}
				(*newStatistic)[linears.first] = newLinears;
			}
			(*linear_statistics_)[statistic.first] = newStatistic;
		}
	}

	ChessMen::~ChessMen()
	{
	}

	std::shared_ptr<typeStatistics> ChessMen::getStatistics()
	{
		return linear_statistics_;
	}

	bool ChessMen::AddChessMan(Coordinater coord, bool side)
	{
		typeChessMap::const_iterator got = this->find(coord);

		if (got == this->end())
		{
			auto chess = shared_ptr<ChessMan>(new ChessMan(coord, side));
			(*this)[coord] = chess;

			Statistic(chess);

			return true;
		}

		return false;
	}

	bool ChessMen::IsTerminal(int goalSize)
	{
		for (auto statistic : *linear_statistics_)
		{
			for (auto linears : *(statistic.second))
			{
				for (auto linear : *(linears.second))
				{
					if (linear->size() >= goalSize)
					{
						return true;
					}
				}
			}
		}

		return false;
	}

	shared_ptr<typeChessLinears> ChessMen::RefactoryLinears(shared_ptr<ChessLinear> combinedLinear, shared_ptr<typeChessLinears> linears, adjacent reqDirection)
	{
		auto newLinears = shared_ptr<typeChessLinears>(new typeChessLinears());
		bool bCombined = false;
		for (auto linear : *linears)
		{
			if (linear != combinedLinear)
			{
				auto ret_ptr = linear->AddAdjacent(combinedLinear, reqDirection);
				if (ret_ptr)
				{
					newLinears->push_back(ret_ptr);
				}
				else
				{
					newLinears->push_back(linear);
				}
			}
		}

		if (!bCombined)
		{
			newLinears->push_back(combinedLinear);
		}

		return newLinears;
	}

	void ChessMen::StatisticChess(std::shared_ptr<ChessMan> chess, string typeTag, adjacent reqDirection)
	{
		int linearTag = -1;
		if (adjacent::col_adjacent == reqDirection)
		{
			linearTag = chess->getCoord().getX();
		}
		else if (adjacent::row_adjacent == reqDirection)
		{
			linearTag = chess->getCoord().getY();
		}
		else
		{
			return;
		}

		auto myStatistics = linear_statistics_->find(typeTag);
		if (myStatistics == linear_statistics_->end())
		{
			shared_ptr<ChessLinear> linear = shared_ptr<ChessLinear>(new ChessLinear(chess));

			shared_ptr<typeChessLinears> linears = shared_ptr<typeChessLinears>(new typeChessLinears());
			linears->push_back(linear);

			shared_ptr<typeStatistic> statistic = shared_ptr<typeStatistic>(new typeStatistic());
			(*statistic)[linearTag] = linears;

			(*linear_statistics_)[typeTag] = statistic;
		}
		else
		{
			shared_ptr<typeStatistic> statistic = (*myStatistics).second;
			auto linears_ret = statistic->find(linearTag);
			if (linears_ret == statistic->end())
			{
				shared_ptr<ChessLinear> linear = shared_ptr<ChessLinear>(new ChessLinear(chess));

				shared_ptr<typeChessLinears> linears = shared_ptr<typeChessLinears>(new typeChessLinears());
				linears->push_back(linear);

				(*statistic)[linearTag] = linears;
			}
			else
			{
				shared_ptr<typeChessLinears> linears = (*linears_ret).second;
				bool bCombineChess = false;
				for (size_t i = 0; i < linears->size(); i++)
				{
					auto ret_ptr = linears->at(i)->AddAdjacent(chess, reqDirection);
					if (ret_ptr)
					{
						bCombineChess = true;
						(*linears)[i] = ret_ptr;

						(*linears_ret).second = RefactoryLinears(linears->at(i), linears, reqDirection);
						break;
					}
				}

				if (!bCombineChess)
				{
					linears->push_back(shared_ptr<ChessLinear>(new ChessLinear(chess)));
				}
			}
		}
	}

	void ChessMen::Statistic(shared_ptr<ChessMan> newChess)
	{
		if (newChess->getSide())
		{
			StatisticChess(newChess, strMyRow, adjacent::row_adjacent);
			StatisticChess(newChess, strMyCol, adjacent::col_adjacent);
		}
		else
		{
			StatisticChess(newChess, strOppositeRow, adjacent::row_adjacent);
			StatisticChess(newChess, strOppositeCol, adjacent::col_adjacent);
		}
	}
}