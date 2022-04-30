#pragma once
#include "WeightedGraph.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Program
{
private:
	string m_i_InputFileName;
	string m_i_OutputFileName;
	WeightedGraph* m_io_ListsGraph;
	pair<int, int>* m_deleteEdge;
	int m_numOfVertices;
	int m_numOfEdges;
public:
	Program(string inputFileName, string outputFileName);
	~Program();
	void readGraphFromFile();
	void executeProgram();
	void readEdgesFromFile(std::ifstream& i_Data);
};
