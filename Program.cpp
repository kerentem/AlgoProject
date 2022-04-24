#include "Program.h"
void Program::executeProgram()
{
	readGraphFromFile();

	if (m_io_ListsGraph->isConnected() == true) { // is the graph connected?
		cout << "Kruskal " << m_io_ListsGraph->Kruskal(false) << endl;
		cout << "Prim " << m_io_ListsGraph->Prim() << endl;
		
		// delete edge and check 

		// check if the edge is a bridge
	
		if (m_io_ListsGraph->isBridge(m_deleteEdge))
			cout << "No MST" << endl;
		else {
			m_io_ListsGraph->RemoveEdge(m_deleteEdge->first, m_deleteEdge->second);
			cout << "Kruskal " << m_io_ListsGraph->Kruskal(true) << endl;
		}
	}
	else {
		//////////////////////////////////////////////////////////////throw
		cout << "The graph isn't connected !! "<< endl;
	}
	// remove edge and check!!!!!!!!!!!!!!!!!!!
}
Program::Program(string inputFileName, string outputFileName)
{
	m_i_InputFileName = inputFileName;
	m_i_OutputFileName = outputFileName;
	WeightedGraph* io_ListsGraph = nullptr;
	pair<int, int>* deleteEdge = nullptr;
}
Program::~Program() {
	  delete m_io_ListsGraph;
	  delete m_deleteEdge;
}
void Program::readGraphFromFile()
{
	ifstream data(m_i_InputFileName);

	try
	{
		data >> m_numOfVertices >> m_numOfEdges;
	}
	catch (std::exception& error)
	{
		data.close();
		throw std::invalid_argument(Error::INVALID_INPUT);
	}

	//not a valid graph
	if (m_numOfEdges < 0 || m_numOfVertices < 1)
	{
		data.close();
		throw std::invalid_argument(Error::INVALID_INPUT);
	}
	//not a connected graph
	if(m_numOfEdges < m_numOfVertices - 1)
	{
		data.close();
		throw std::invalid_argument(Error::NO_MST);
	}

	m_io_ListsGraph = new WeightedGraph(m_numOfVertices);

	try
	{
		pair<int, int>* deleteEdge = nullptr;
		readEdgesFromFile(data);
	}
	catch (std::exception& error)
	{
		delete m_io_ListsGraph;
		data.close();
		throw std::invalid_argument(Error::INVALID_INPUT);
	}

	data.close();
}
void Program::readEdgesFromFile(std::ifstream& i_Data)
{
	int count = 1;
	while (i_Data.eof() == false)
	{			
		int u, v, weight;
		for (int i = 0; i < m_numOfEdges; i++)
		{
			try
			{
				i_Data >> u >> v >> weight;
			}
			catch (std::exception& error)
			{
				throw std::invalid_argument(Error::INVALID_INPUT);
			}

			if ((u > m_io_ListsGraph->GetSize() || v > m_io_ListsGraph->GetSize()) || u < 1 || v < 1 || weight < 0)
				throw std::invalid_argument(Error::INVALID_INPUT);

			m_io_ListsGraph->AddEdge(u, v, weight);
		}

		try
		{

			i_Data >> u >> v;
		}
		catch (std::exception& error)
		{
			throw std::invalid_argument(Error::INVALID_INPUT);
		}

		if ((u > m_io_ListsGraph->GetSize() || v > m_io_ListsGraph->GetSize()) || u < 1 || v < 1)
			throw std::invalid_argument(Error::INVALID_INPUT);

		m_deleteEdge = new pair<int, int>;
		m_deleteEdge->first = u;
		m_deleteEdge->second = v;
		}
}
