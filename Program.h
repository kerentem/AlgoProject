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
	int m_numOfVertices = -1;
	int m_numOfEdges = -1;
public:
	Program(string inputFileName, string outputFileName);
	~Program();
	void readGraphFromFile();
	void executeProgram();
	void writeToOutputFile(std::string st);
	void readEdgesFromFile(std::ifstream& i_Data);
};
