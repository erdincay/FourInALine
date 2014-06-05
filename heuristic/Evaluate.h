#pragma once
#include "..\model\Coordinater.h"
#include "..\heuristic\Heuristic.h"

namespace model
{
	class ChessBoard;
	class ChessLinear;
}

namespace heuristic
{

	const int ONE_CHESSMAN = 1;
	const int TWO_CHESSMAN_ONE_AVAILABLE = 3;
	const int TWO_CHESSMAN_BOTH_AVAILABLE = 5;
	const int THREE_CHESSMAN_ONE_AVAILABLE = 7;
	const int THREE_CHESEMAN_BOTH_AVAILABLE = 90;
	const int EXTRA_PLUS = 100;


	class Evaluate 
	{
	public:
		Evaluate();
		Evaluate(std::shared_ptr<model::ChessLinear> linear);
		~Evaluate();

		/* evaluate */
		std::vector<typeEval> oneAvailable(std::shared_ptr<model::ChessBoard> board, bool currentSide, int DD3True, int DD3False);
		std::vector<typeEval> twoAvailable(std::shared_ptr<model::ChessBoard> board, bool nextSide, bool currentSide, int DL2True, int DL2False, int L2D3True, int L2D3False);
		std::vector<typeEval> noneAvailable(std::shared_ptr<model::ChessBoard> board, bool currentSide);


		/* evaluate double live 2 and live 2 + dead 3*/
		typeEval evalLinearRow(std::shared_ptr<model::ChessBoard> board, std::string colType, model::Coordinater coord, int doubleLive2, int live2Dead3);
		typeEval evalLinearCol(std::shared_ptr<model::ChessBoard> board, std::string rowType, model::Coordinater coord, int doubleLive2, int live2Dead3);
		/* evaluate double dead 3*/
		typeEval evalLinearDD3Row(std::shared_ptr<model::ChessBoard> board, std::string colType, model::Coordinater coord, int doubleDead3);
		typeEval evalLinearDD3Col(std::shared_ptr<model::ChessBoard> board, std::string rowType, model::Coordinater coord, int doubleDead3);
		


	private:
		std::shared_ptr<model::ChessLinear> linear_;
	};
}


