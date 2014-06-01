#pragma once

#include <unordered_map>
#include "Coordinater.h"

namespace model
{
	class ChessMan;

	typedef std::unordered_map<Coordinater, std::shared_ptr<ChessMan>, Coordinater::KeyHasher> typeChessMap;

	class ChessMen : public typeChessMap
	{
	public:
		ChessMen();
		ChessMen(const ChessMen & oth);
		virtual ~ChessMen();

		bool AddChessMan(Coordinater destination, bool side);

	};

}

