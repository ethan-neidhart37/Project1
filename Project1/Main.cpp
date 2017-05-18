#include <iostream>
#include "p1a.cpp"
#include "p1b.cpp"

int main() {
	// Run p1a.cpp and p1b.cpp
	
	int num;
	char select;
	bool loopEnd = false;

	while (loopEnd == false)
	{
		do
		{
			std::cout << "[1] p1a \n[2] p1b \n";
			std::cout << "Select which project problem to run: ";
			std::cin >> num;

			switch (num)
			{
			case 1: knapsackRun(); break;
			case 2: graphColoring(); break;
			default: std::cout << "Please select correct input. [1/2]"; break;
			}
		} while (num != 1 && num != 2);

		do
		{
			std::cout << "\nTry another project problem? [y/n]: ";
			std::cin >> select;

			switch (select)
			{
			case 'y': loopEnd = false; break;
			case 'n': loopEnd = true; break;
			default: std::cout << "Please select correct input '[y/n]"; break;
			}
			std::cout << "\n";
		} while (select != 'y' && select != 'n');		
	}

	std::cin.get();
	return 0;
}