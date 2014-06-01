#pragma once

namespace model
{
	class State
	{
	public:
		State();
		virtual ~State();

		virtual bool IsTerminal() = 0;
	};

}

