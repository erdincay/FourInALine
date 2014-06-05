#include <iostream>
#include <boost/algorithm/string/case_conv.hpp>
#include "UI.h"

int main(int argc, char *argv[])
{
	using namespace std;

	solution::UI user_interface;

	user_interface.Start();

	string ret = "";

	while (!("y" == ret || "yes" == ret))
	{
		cout << "are your sure to quit ? " << endl;
		cin >> ret;
		boost::to_lower(ret);
	}

	return 0;
}