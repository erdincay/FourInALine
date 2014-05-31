#pragma once

#include <unordered_map>
#include "Coordinater.h"
#include "ChessMan.h"

namespace model
{
	class ChessMen : public std::unordered_map<Coordinater, ChessMan, KeyHasher>
	{
	public:
		ChessMen();
		virtual ~ChessMen();
	};

}

