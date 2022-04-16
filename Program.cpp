#include "Program.h"
void executeProgram(const std::string& i_InputFileName, const std::string& i_OutputFileName)
{
	WeightedGraph* listedGraph;
	readGraphFromFile(i_InputFileName , listedGraph);
	cout << "Kruskal " << listedGraph->Kruskal() << endl;
	cout << "Prim " << listedGraph->Prim() << endl;
}

void readGraphFromFile(const std::string& i_InputFileName, WeightedGraph*& io_ListedGraph)
{
	ifstream data(i_InputFileName);
	int numOfVertices,numOfEdges;

	try
	{
		data >> numOfVertices >> numOfEdges;
	}
	catch (std::exception& error)
	{
		data.close();
		throw std::invalid_argument(Error::INVALID_INPUT);
	}

	//not a valid graph
	if (numOfEdges < 0 || numOfVertices < 1)
	{
		data.close();
		throw std::invalid_argument(Error::INVALID_INPUT);
	}
	//not a connected graph
	if(numOfEdges < numOfVertices - 1)
	{
		data.close();
		throw std::invalid_argument(Error::NO_MST);
	}

	io_ListedGraph = new WeightedGraph(numOfVertices);

	try
	{
		readEdgesFromFile(data, io_ListedGraph);
	}
	catch (std::exception& error)
	{
		delete io_ListedGraph;
		data.close();
		throw std::invalid_argument(Error::INVALID_INPUT);
	}

	data.close();
}
void readEdgesFromFile(std::ifstream& i_Data, WeightedGraph*& io_ListedGraph)
{
	while (i_Data.eof() == false)
	{
		int u, v, weight;
		try
		{
			i_Data >> u >> v >> weight;
		}
		catch (std::exception& error)
		{
			throw std::invalid_argument(Error::INVALID_INPUT);
		}

		if((u > io_ListedGraph->GetSize() || v > io_ListedGraph->GetSize()) || u < 1 || v < 1 || weight < 0)
			throw std::invalid_argument(Error::INVALID_INPUT);

		io_ListedGraph->AddEdge(u, v, weight);
	}
}