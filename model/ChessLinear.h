#pragma once

#include <memory>
#include "ChessMan.h"

namespace model
{
	enum class avarible
	{
		left_avarible,
		right_avarible,
		both_avarible,
		none_avarible
	};

	class ChessLinear
	{
	public:
		ChessLinear(std::shared_ptr<ChessMan> chess);
		ChessLinear(const ChessLinear & oth);
		ChessLinear(std::shared_ptr<ChessMan> start, std::shared_ptr<ChessMan> end);
		~ChessLinear();

		bool CheckAdjacent(std::shared_ptr<ChessMan> chess, adjacent reqDirection);
		std::shared_ptr<ChessLinear> AddAdjacent(std::shared_ptr<ChessMan> chess, adjacent reqDirection);

		bool CheckAdjacent(std::shared_ptr<ChessLinear> linear, adjacent reqDirection);
		std::shared_ptr<ChessLinear> AddAdjacent(std::shared_ptr<ChessLinear> linear, adjacent reqDirection);

		adjacent getDirection();
		std::shared_ptr<ChessMan> getStart();
		std::shared_ptr<ChessMan> getEnd();

		int size();

	private:
		std::shared_ptr<ChessMan> start_;
		std::shared_ptr<ChessMan> end_;
	};

}

