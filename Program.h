#pragma once
#include "WeightedGraph.h"

void readGraphFromFile(const std::string& i_InputFileName,WeightedGraph*& io_ListsGraph);
void executeProgram(const std::string& i_InputFileName, const std::string& i_OutputFileName);
void readEdgesFromFile(std::ifstream& i_Data, WeightedGraph*& o_ListsGraph);



