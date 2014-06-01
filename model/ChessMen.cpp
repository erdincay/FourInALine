#include "ChessMen.h"
#include "ChessMan.h"

namespace model
{
	using namespace std;

	ChessMen::ChessMen()
	{
	}

	ChessMen::ChessMen(const ChessMen & oth) {
		for (const auto & elem : oth)
		{
			this->at(elem.first) = shared_ptr<ChessMan>(new ChessMan(*elem.second));
		}
	}

	ChessMen::~ChessMen()
	{
	}

	bool ChessMen::AddChessMan(Coordinater destination, bool side)
	{
		typeChessMap::const_iterator got = this->find(destination);

		if (got == this->end())
		{
			this->at(destination) = shared_ptr<ChessMan>(new ChessMan(destination, side));
			return true;
		}

		return false;
	}
}