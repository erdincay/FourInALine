#pragma once
#include "../model/Coordinater.h"
#include "Minimax.h"

namespace solution
{
	class UI
	{
	public:
		UI();
		~UI();

		void Start();
		
	private:
		size_t GetTimeDuration();
		bool FirstHand();
		model::Coordinater OppositeMove();

		void Continue(model::Coordinater coord = model::Coordinater(0, 0));
		void MyCalculation();

	private:
		std::shared_ptr<Minimax> sln_;
		
	};

}

