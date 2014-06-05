#include "ChessBoard.h"
#include "ChessMan.h"
#include <sstream>

namespace model
{
	using namespace std;
	using namespace boost::logic;

	const int startIndex = 1;

	ChessBoard::ChessBoard(int size, int goalSize)
		:size_(size),
		goalSize_(goalSize),
		pieces_(shared_ptr<ChessMen>(new ChessMen()))
	{

	}

	ChessBoard::ChessBoard(const ChessBoard & oth)
		:size_(oth.size_),
		goalSize_(oth.goalSize_),
		pieces_(shared_ptr<ChessMen>(new ChessMen(*oth.pieces_)))
	{

	}

	ChessBoard::~ChessBoard()
	{
	}

	bool ChessBoard::NewChess(Coordinater coord, bool side)
	{
		if (!(coord.getX() > 0 && coord.getX() <= size_ && coord.getY() > 0 && coord.getY() <= size_))
		{
			return false;
		}

		return pieces_->AddChessMan(coord, side);
	}

	bool ChessBoard::IsTerminal()
	{
		if (pieces_->size() >= size_*size_)
		{
			return true;
		}

		return pieces_->IsTerminal(goalSize_);
	}

	shared_ptr<ChessMen> ChessBoard::getPieces()
	{
		return pieces_;
	}

	bool ChessBoard::InsideBoundary(Coordinater coord)
	{
		if (coord.getX() >= startIndex && coord.getY() >= startIndex && coord.getX() < startIndex + size_ && coord.getY() < startIndex + size_)
		{
			return true;
		}

		return false;
	}

	tribool ChessBoard::getLocationType(Coordinater coord)
	{
		auto ret = pieces_->find(coord);
		if (ret == pieces_->end())
		{
			return indeterminate;
		}
		else
		{
			return (*ret).second->getSide();
		}
	}

	avarible ChessBoard::getLinearAvailable(std::shared_ptr<ChessLinear> linear)
	{
		auto sCoord = linear->getStart()->getCoord();
		auto eCoord = linear->getEnd()->getCoord();
		auto direction = linear->getDirection();

		Coordinater before(0, 0);
		Coordinater after(0, 0);

		if (direction == adjacent::row_adjacent)
		{
			before = Coordinater(sCoord.getX() - 1, sCoord.getY());
			after = Coordinater(eCoord.getX() + 1, eCoord.getY());
		}
		else if (direction == adjacent::col_adjacent)
		{
			before = Coordinater(sCoord.getX(), sCoord.getY() - 1);
			after = Coordinater(eCoord.getX(), eCoord.getY() + 1);
		}
		else
		{
			return avarible::error;
		}

		bool beforeAvailable = false;
		if (InsideBoundary(before))
		{
			auto ret = getLocationType(before);
			if (ret == indeterminate)
			{
				beforeAvailable = true;
			}
			else if (ret == linear->getStart()->getSide())
			{
				return avarible::error;
			}
		}

		bool afterAvailable = false;
		if (InsideBoundary(after))
		{
			auto ret = getLocationType(after);
			if (ret == indeterminate)
			{
				afterAvailable = true;
			}
			else if (ret == linear->getEnd()->getSide())
			{
				return avarible::error;
			}
		}

		if (beforeAvailable && afterAvailable)
		{
			return avarible::both_avarible;
		}
		else if (beforeAvailable && !afterAvailable)
		{
			return avarible::before_avarible;
		}
		else if (!beforeAvailable && afterAvailable)
		{
			return avarible::after_avarible;
		}
		else
		{
			return avarible::none_avarible;
		}
	}

	int ChessBoard::getSize()
	{
		return size_;
	}

	string ChessBoard::toString()
	{
		ostringstream ostr;
		for (int i = 0; i <= getSize(); i++)
		{
			if (i > 0)
			{
				ostr << i << " ";
			}
			else
			{
				ostr << "  ";
			}
		}
		ostr << endl;

		for (int i = 1; i <= getSize(); i++)
		{
			for (int j = 0; j <= getSize(); j++)
			{
				if (j == 0)
				{
					char row = 'A' - 1 + i;
					ostr << row << " ";
				}
				else
				{
					Coordinater coord(j, i);
					auto find_ret = pieces_->find(coord);
					if (find_ret == pieces_->end())
					{
						ostr << "- ";
					}
					else if (find_ret->second->getSide())
					{
						ostr << "X ";
					}
					else
					{
						ostr << "O ";
					}
				}
			}
			ostr << endl;
		}

		return ostr.str();
	}
}