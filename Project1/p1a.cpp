// File: p1a.cpp
// Authors: Kevin Do, Ethan Neidhart
// Project 1a: Solving knapsack using exhaustive search

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <time.h>

#include "d_except.h"
#include "d_matrix.h"
#include "knapsack.h"

using namespace std;

void exhaustiveKnapsack(knapsack &k, int t)
{
	clock_t startTime;
	clock_t currentTime;
	startTime = clock();
	float diff; //time difference
	float duration = 0;
	bool foundNode = false; //found a position
	bool endOfKnapsackSets = false;
	vector <bool> selectedObjs(k.getNumObjects(), false);
	int score = 0;
	int i;

	while (t > duration && !endOfKnapsackSets)
	{
		// Display
		//cout << "knapsack" << k.getNumObjects() << ".input - " << "duration: " << duration << "s" << endl;

		if (score < k.getValue() && k.getCost() <= k.getCostLimit())
		{
			score = k.getValue();
			selectedObjs = k.getSelected();
		}

		// Reset
		foundNode = false;
		i = 0;

		while (!foundNode)
		{
			if (k.isSelected(i))
			{
				k.unSelect(i);
				if (i == k.getNumObjects() - 1) { endOfKnapsackSets = true; }
				else { i++; }
			}
			else
			{
				k.select(i);
				foundNode = true;
			}
		}
		currentTime = clock();
		diff = (float)currentTime - (float)startTime;
		duration = diff / CLOCKS_PER_SEC;
	}

	for (int i = 0; i < selectedObjs.size(); i++)
	{
		if (selectedObjs[i]) { k.select(i); }
		else { k.unSelect(i); }
	}
}

void knapsackOutput(knapsack & k)
{
	string fileName = "knapsack/output/knapsack" + to_string(k.getNumObjects()) + ".output";

	ofstream myfile;
	myfile.open(fileName);

	myfile << "Number of Objects: " << k.getNumObjects() << endl;
	myfile << "Total value: " << k.getValue() << endl;
	myfile << "Total cost: " << k.getCost() << endl;

	// Print out objects in the solution
	for (int i = 0; i < k.getNumObjects(); i++)
	{
		if (k.isSelected(i))
		{
			// Some unnecessary formatting to make output file look nicer
			if (i < 10)
			{
				myfile << i << "   " << k.getValue(i) << " " << k.getCost(i) << endl;
			}
			else
			{
				myfile << i << "  " << k.getValue(i) << " " << k.getCost(i) << endl;
			}
		}
	}
	myfile << endl;
	myfile.close();
}

void knapsackRun()
{
	ifstream fin;
	string fileName;

	// Read the name of the graph from the keyboard or
	// hard code it here for testing.

	// fileName = "knapsack/input/knapsack16.input";

	vector<string> s;
	s.push_back("knapsack/input/knapsack8.input");
	s.push_back("knapsack/input/knapsack12.input");
	s.push_back("knapsack/input/knapsack16.input");
	s.push_back("knapsack/input/knapsack20.input");
	s.push_back("knapsack/input/knapsack28.input");
	s.push_back("knapsack/input/knapsack32.input");
	s.push_back("knapsack/input/knapsack48.input");
	s.push_back("knapsack/input/knapsack64.input");
	s.push_back("knapsack/input/knapsack128.input");
	s.push_back("knapsack/input/knapsack256.input");
	s.push_back("knapsack/input/knapsack512.input");
	s.push_back("knapsack/input/knapsack1024.input");

	for (int i = 0; i < s.size(); i++)
	{
		//cout << "Enter filename" << endl;
		//cin >> fileName;
		fileName = s[i];
		fin.open(fileName.c_str());
		if (!fin)
		{
			cerr << "Cannot open " << fileName << endl;
			exit(1);
		}

		try
		{
			cout << "Reading knapsack instance for " << s[i] << endl;

			knapsack k(fin);

			exhaustiveKnapsack(k, 600);

			// Write solution to output file
			knapsackOutput(k);

			cout << endl << "Best solution" << endl;
			k.printSolution();

			// Pause to view results
			//system("PAUSE");
		}

		catch (indexRangeError &ex)
		{
			cout << ex.what() << endl; exit(1);
		}
		catch (rangeError &ex)
		{
			cout << ex.what() << endl; exit(1);
		}

		fin.close();
	}
}
