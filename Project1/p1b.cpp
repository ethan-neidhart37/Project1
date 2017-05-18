// Code to read graph instances from a file.  Uses the Boost Graph Library (BGL).

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <fstream>
#include <time.h>

#include <boost/graph/adjacency_list.hpp>

#define LargeValue 99999999

using namespace std;
using namespace boost;

int const NONE = -1;  // Used to represent a node that does not exist

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
	pair<int, int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred;
	bool visited;
	bool marked;
	int weight;
	int color;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};

void initializeGraph(Graph &g, ifstream &fin)
// Initialize g using data from fin.
{
	int n, e;
	int j, k;

	fin >> n >> e;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < n; i++)
		v = add_vertex(g);

	for (int i = 0; i < e; i++)
	{
		fin >> j >> k;
		add_edge(j, k, g);  // Assumes vertex list is type vecS
	}
}

void setNodeWeights(Graph &g, int w)
// Set all node weights to w.
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);

	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		g[*vItr].weight = w;
	}
}

void setNodeColors(Graph &g, int c)
// Set all node colors to c (integer representation of a color).
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);

	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		g[*vItr].color = c;
	}
}

int checkConflicts(Graph &g)
// Return the number of nodes in conflict in a graph.
// For each edge with two nodes of the same color, there is one node in conflict.
{
	int numConflicts = 0;
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
	for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
	{
		Graph::vertex_descriptor t = target(*eItr, g);
		Graph::vertex_descriptor s = source(*eItr, g);
		if (g[t].color == g[s].color)
			numConflicts++;
	}
	return numConflicts;
}

void increment(Graph &g, Graph::vertex_iterator vItr, int numColors, Graph::vertex_iterator vEnd)
// Used to cycle through all the different permutations of graph coloring, one at a time.
// With all vertices stored in a linear array, and all colors represented by integers,
// the graph functions in a remarkably similar way to a counter.
{
	g[*vItr].color++;
	if (g[*vItr].color == numColors)
	{
		g[*vItr].color = 0;
		increment(g, vItr + 1, numColors, vEnd);
	}
}

int exhaustiveColoring(Graph &g, int numColors, int t)
// Increment through all permutations of the graph using the increment() function.
// Check number of conflicts, and store lowest number that has been checked.
// Return number of conflicts when done, or when time t has passed.
{
	clock_t startTime = clock();

	setNodeColors(g, 0);
	int numConflicts = checkConflicts(g);
	int tempNumConflicts = numConflicts;

	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);

	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		for (int color = 1; color < numColors; color++) {
			increment(g, vItrRange.first, numColors, vItrRange.second);
			tempNumConflicts = checkConflicts(g);

			if (tempNumConflicts < numConflicts) {
				numConflicts = tempNumConflicts;
			}

			// Check if time is expired and return
			if ((clock() - startTime) / CLOCKS_PER_SEC >= t)
			{
				return numConflicts;
			}
		}
	}
}

void printSolution(Graph &g, int numConflicts, string filename)
// Print the solution found.
{
	ofstream myfile;
	myfile.open((filename + ".output").c_str());

	myfile << "Total Conflicts: " << numConflicts << endl;
	for (int counter = 0; counter < num_vertices(g); ++counter)
	{
		myfile << counter << ": " << g[counter].color << endl;
	}
	myfile.close();
}

int main()
{
	char x;
	ifstream fin;
	string fileName;

	// Read the name of the graph from the keyboard or
	// hard code it here for testing.

	string fileFolder = "C:\\Users\\Ethan\\Documents\\GitHub\\Algorithms\\Project1\\Project1\\colors\\";
	fileName = "color12-3";

	//   cout << "Enter filename" << endl;
	//   cin >> fileName;

	fileName = fileFolder + fileName;

	fin.open((fileName + ".input").c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		cout << "Reading graph" << endl;
		Graph g;
		int numColors;
		int numConflicts = -1;
		fin >> numColors;
		initializeGraph(g, fin);

		cout << "Num nodes: " << num_vertices(g) << endl;
		cout << "Num edges: " << num_edges(g) << endl;
		cout << endl;

		// cout << g;

		numConflicts = exhaustiveColoring(g, numColors, 600);
		printSolution(g, numConflicts, fileName);

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

