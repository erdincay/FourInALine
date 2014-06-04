#include "ChessLinear.h"

namespace model
{
	using namespace std;

	ChessLinear::ChessLinear(shared_ptr<ChessMan> chess)
		:start_(chess),
		end_(chess)
	{
	}

	ChessLinear::ChessLinear(shared_ptr<ChessMan> start, shared_ptr<ChessMan> end)
		:start_(start),
		end_(end)
	{

	}

	ChessLinear::ChessLinear(const ChessLinear & oth)
		:start_(shared_ptr<ChessMan>(new ChessMan(*oth.start_))),
		end_(shared_ptr<ChessMan>(new ChessMan(*oth.end_)))
	{

	}

	ChessLinear::~ChessLinear()
	{
	}

	int ChessLinear::size()
	{
		if (!start_ || !end_)
		{
			return 0;
		}
		else if (start_ == end_)
		{
			return 1;
		}
		else
		{
			if (adjacent::col_adjacent == getDirection())
			{
				return end_->getCoord().getY() - start_->getCoord().getY();
			}
			else if (adjacent::row_adjacent == getDirection())
			{
				return end_->getCoord().getX() - start_->getCoord().getX();
			}
		}

		return 0;
	}

	shared_ptr<ChessMan> ChessLinear::getStart()
	{
		return start_;
	}

	shared_ptr<ChessMan> ChessLinear::getEnd()
	{
		return end_;
	}

	adjacent ChessLinear::getDirection()
	{
		if (!start_ || !end_ || start_ == end_)
		{
			return adjacent::none_adjacent;
		}
		else if (end_->getCoord().getX() == start_->getCoord().getX())
		{
			return adjacent::col_adjacent;
		}
		else if (end_->getCoord().getY() == start_->getCoord().getY())
		{
			return adjacent::row_adjacent;
		}

		return adjacent::none_adjacent;
	}

	bool ChessLinear::CheckAdjacent(shared_ptr<ChessMan> chess, adjacent reqDirection)
	{
		if (size() <= 0 || adjacent::none_adjacent == reqDirection)
		{
			return false;
		}
		else if (size() == 1 || start_ == end_)
		{
			return start_->Adjacent(chess).first == reqDirection;
		}
		else
		{
			if (getDirection() == reqDirection)
			{
				auto startRet = start_->Adjacent(chess);
				auto endRet = end_->Adjacent(chess);

				return (startRet.first == reqDirection && startRet.second) || (endRet.first == reqDirection && !endRet.second);
			}
		}

		return false;
	}

	shared_ptr<ChessLinear> ChessLinear::AddAdjacent(shared_ptr<ChessMan> chess, adjacent reqDirection)
	{
		if (size() <= 0 || adjacent::none_adjacent == reqDirection)
		{
			return shared_ptr<ChessLinear>(NULL);
		}

		if (size() == 1 || start_ == end_)
		{
			auto ret = start_->Adjacent(chess);
			if (ret.first == reqDirection)
			{
				if (ret.second)
				{
					return shared_ptr<ChessLinear>(new ChessLinear(start_, chess));
				}
				else
				{
					return shared_ptr<ChessLinear>(new ChessLinear(chess, end_));
				}
			}
		}
		else
		{
			if (getDirection() == reqDirection)
			{
				auto startRet = start_->Adjacent(chess);
				auto endRet = end_->Adjacent(chess);

				if (startRet.first == reqDirection && !startRet.second)
				{
					return shared_ptr<ChessLinear>(new ChessLinear(chess, end_));
				}
				else if (endRet.first == reqDirection && endRet.second)
				{
					return shared_ptr<ChessLinear>(new ChessLinear(start_, chess));
				}
			}
		}

		return shared_ptr<ChessLinear>(NULL);
	}

	bool ChessLinear::CheckAdjacent(shared_ptr<ChessLinear> linear, adjacent reqDirection)
	{
		if (size() <= 0 || linear->size() <= 0 || adjacent::none_adjacent == reqDirection)
		{
			return false;
		}
		else if (size() == 1 || start_ == end_)
		{
			return linear->CheckAdjacent(start_, reqDirection);
		}
		else if (linear->size() == 1)
		{
			return CheckAdjacent(linear->getStart(), reqDirection);
		}
		else if (getDirection() == reqDirection && linear->getDirection() == reqDirection)
		{
			auto startRet = start_->Adjacent(linear->getEnd());
			auto endRet = end_->Adjacent(linear->getStart());

			return (startRet.first == reqDirection && !startRet.second) || (endRet.first == reqDirection && endRet.second);
		}

		return false;
	}

	shared_ptr<ChessLinear> ChessLinear::AddAdjacent(shared_ptr<ChessLinear> linear, adjacent reqDirection)
	{
		if (size() <= 0 || linear->size() <= 0 || adjacent::none_adjacent == reqDirection)
		{
			return shared_ptr<ChessLinear>(NULL);
		}
		else if (size() == 1 || start_ == end_)
		{
			return linear->AddAdjacent(start_, reqDirection);
		}
		else if (linear->size() == 1)
		{
			return AddAdjacent(linear->getStart(), reqDirection);
		}
		else if (getDirection() == reqDirection && linear->getDirection() == reqDirection)
		{
			auto startRet = start_->Adjacent(linear->getEnd());
			auto endRet = end_->Adjacent(linear->getStart());

			if (startRet.first == reqDirection && !startRet.second)
			{
				return shared_ptr<ChessLinear>(new ChessLinear(linear->getStart(), end_));
			}
			else if (endRet.first == reqDirection && endRet.second)
			{
				return shared_ptr<ChessLinear>(new ChessLinear(start_, end_));
			}
		}

		return shared_ptr<ChessLinear>(NULL);
	}

}