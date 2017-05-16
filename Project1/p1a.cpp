// Project 1a: Solving knapsack using exhaustive search
//

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <time.h>

using namespace std;

#include "d_except.h"
#include "d_matrix.h"
#include <boost/graph/adjacency_list.hpp>
#include "knapsack.h"

void exhaustiveKnapsack(knapsack &sack, int seconds);

int main()
{
   char x;
   ifstream fin;
   stack <int> moves;
   string fileName;
   
   // Read the name of the graph from the keyboard or
   // hard code it here for testing.
   
   // fileName = "knapsack16.input";

   vector<std::string> s;
   s.push_back("knapsack/knapsack8.input");
   s.push_back("knapsack/knapsack12.input");
   s.push_back("knapsack/knapsack16.input");
   s.push_back("knapsack/knapsack20.input");
   s.push_back("knapsack/knapsack28.input");
   s.push_back("knapsack/knapsack32.input");
   s.push_back("knapsack/knapsack48.input");
   s.push_back("knapsack/knapsack64.input");
   s.push_back("knapsack/knapsack128.input");
   s.push_back("knapsack/knapsack256.input");
   s.push_back("knapsack/knapsack512.input");
   s.push_back("knapsack/knapsack1024.input");

   for (int i = 0; i < s.size(); i++)
   {
	   cout << "Enter filename" << endl;
	   cin >> fileName;
	   //fileName = s[i];
	   fin.open(fileName.c_str());
	   if (!fin)
	   {
		   cerr << "Cannot open " << fileName << endl;
		   exit(1);
	   }

   try
   {
      cout << "Reading knapsack instance" << endl;
      knapsack k(fin);

      exhaustiveKnapsack(k, 600);

      cout << endl << "Best solution" << endl;
      k.printSolution();
      
   }    

   catch (indexRangeError &ex) 
   { 
      cout << ex.what() << endl; exit(1);
   }
   catch (rangeError &ex)
   {
      cout << ex.what() << endl; exit(1);
   }
}

void exhaustiveKnapsack(knapsack & sack, int seconds)
{}
