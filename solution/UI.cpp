#include "UI.h"
#include <iostream>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/lexical_cast.hpp>
#include "../model/ChessBoard.h"
#include "../heuristic/EvaluationWeight.h"
#include "../action/MoveTo.h"

const int board_size = 8;
const int goal_size = 4;

namespace solution
{
	using namespace std;
	using namespace model;
	using namespace heuristic;

	using boost::lexical_cast;
	using boost::bad_lexical_cast;

	UI::UI()
	{
	}


	UI::~UI()
	{
	}

	size_t UI::GetTimeDuration()
	{
		cout << "Please input to set the time duration, unit = seconds" << endl;
		string ret;
		cin >> ret;

		try
		{
			return lexical_cast<size_t>(ret);
		}
		catch (const bad_lexical_cast &)
		{
			cout << "Invalid time duration, please input again!" << endl;
			return GetTimeDuration();
		}
		catch (...)
		{
			cout << "Invalid time duration, please input again!" << endl;
			return GetTimeDuration();
		}
	}

	bool UI::FirstHand()
	{
		using namespace boost;

		cout << "Do you want to go first?(Y/N)" << endl;
		string ret;
		cin >> ret;
		to_lower(ret);
		if ("y" == ret || "yes" == ret)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Coordinater UI::OppositeMove()
	{
		cout << "Input your move" << endl;
		string ret;
		cin >> ret;
		boost::to_lower(ret);

		if (ret.length() != 2)
		{
			cout << "Invalid move, please input again!" << endl;
			return OppositeMove();
		}

		char y = tolower(ret.front());
		char x = ret.back();

		try
		{
			return Coordinater(lexical_cast<int>(x), y - 'a' + 1);
		}
		catch (const bad_lexical_cast &)
		{
			cout << "Invalid move, please input again!" << endl;
			return OppositeMove();
		}
		catch (...)
		{
			cout << "Invalid move, please input again!" << endl;
			return OppositeMove();
		}
		
	}

	void UI::MyCalculation()
	{
		auto myAction = sln_->Run();
		if (myAction == NULL)
		{
			cout << "Game Over! " << endl;
		}
		else
		{
			Continue(myAction->getCoordinater());
		}
	}

	void UI::Continue(Coordinater coord)
	{
		string x = lexical_cast<string>(coord.getX());
		char y = 'A' + coord.getY() - 1;

		auto board = sln_->getCurState();
		
		cout << board->toString();
		cout << "my last move = " << y << x << endl;

		Coordinater oppCoord = OppositeMove();
		if (board->NewChess(oppCoord, false))
		{
			MyCalculation();
		}
		else
		{
			cout << "Invalid move, please input again!" << endl;
			Continue(coord);
		}
	}

	void UI::Start()
	{
		int time_duration = GetTimeDuration();
		sln_.reset(new Minimax(board_size, goal_size, shared_ptr<Heuristic>(new EvaluationWeight()), time_duration));

		if (FirstHand())
		{
			Continue();
		}
		else
		{
			MyCalculation();
		}
	}
}
