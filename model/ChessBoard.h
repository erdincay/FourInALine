#pragma once

#include "State.h"
#include "ChessMen.h"
#include <boost/logic/tribool.hpp>

namespace model
{
	enum class avarible
	{
		before_avarible,
		after_avarible,
		both_avarible,
		none_avarible,
		error
	};

	class ChessBoard : public State
	{
	public:
		ChessBoard(int size, int goalSize);
		ChessBoard(const ChessBoard & oth);
		virtual ~ChessBoard();

		bool IsTerminal();

		bool NewChess(Coordinater coord, bool side);

		std::shared_ptr<ChessMen> getPieces();

		avarible getLinearAvailable(std::shared_ptr<ChessLinear> linear);
		bool InsideBoundary(Coordinater coord);
		boost::logic::tribool getLocationType(Coordinater coord);
		int getSize();

		std::string toString();

	private:
		int size_;
		int goalSize_;
		std::shared_ptr<ChessMen> pieces_;
	};
}