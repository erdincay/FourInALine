#pragma once
#include "..\heuristic\Heuristic.h"
#include "..\model\Coordinater.h"

namespace model
{
	class ChessBoard;
}


namespace heuristic
{
	class EvaluationWeight :
		public Heuristic
	{
	public:
		EvaluationWeight();
		virtual ~EvaluationWeight();
		typeEval eval(std::shared_ptr<model::State> s, bool side);
		std::unordered_map<model::Coordinater, std::shared_ptr<action::Action>, model::Coordinater::KeyHasher> generateActions(std::shared_ptr<model::State> s, bool side);
	private:
		typeEval evalLinearRow(std::shared_ptr<model::ChessBoard> board, std::string key, model::Coordinater coord);
		typeEval evalLinearCol(std::shared_ptr<model::ChessBoard> board, std::string key, model::Coordinater coord);
	};

}
