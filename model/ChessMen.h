#pragma once

#include <unordered_map>
#include "Coordinater.h"
#include "ChessLinear.h"

namespace model
{
	typedef std::unordered_map<Coordinater, std::shared_ptr<ChessMan>, Coordinater::KeyHasher> typeChessMap;

	typedef std::vector<std::shared_ptr<ChessLinear>> typeChessLinears;
	typedef std::unordered_map<int, std::shared_ptr<typeChessLinears>> typeStatistic;
	typedef std::unordered_map<std::string, std::shared_ptr<typeStatistic>> typeStatistics;

	class ChessMen : public typeChessMap
	{
	public:
		ChessMen();
		ChessMen(const ChessMen & oth);
		virtual ~ChessMen();

		bool AddChessMan(Coordinater coord, bool side);
		bool IsTerminal(int goalSize);

		std::shared_ptr<typeStatistics> getStatistics();
	
	private:
		std::shared_ptr<typeChessLinears> RefactoryLinears(std::shared_ptr<ChessLinear> combinedLinear, std::shared_ptr<typeChessLinears> linears, adjacent reqDirection);
		void StatisticChess(std::shared_ptr<ChessMan> chess, std::string typeTag, adjacent reqDirection);
		void Statistic(std::shared_ptr<ChessMan> chess);

	private:
		std::shared_ptr<typeStatistics> statistics_;

	};

}

