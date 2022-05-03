#include "Program.h"

Program::Program(string inputFileName, string outputFileName)
{
	m_i_InputFileName = inputFileName;
	m_i_OutputFileName = outputFileName;
	WeightedGraph* io_ListsGraph = nullptr;
	pair<int, int>* deleteEdge = nullptr;
}
Program::~Program() {
	if(!m_io_ListsGraph)
	  delete m_io_ListsGraph;
	if (!m_deleteEdge)
	  delete m_deleteEdge;
}
void Program::executeProgram()
{
	string Kruskal_first;
	string Kruskal_second;
	string Prim_str;
	readGraphFromFile();

	if (m_io_ListsGraph->isConnected() == true) { // is the graph connected?
		Kruskal_first = "Kruskal " + std::to_string(m_io_ListsGraph->Kruskal(false));
		cout << Kruskal_first << endl;

		Prim_str = "Prim " +std::to_string(m_io_ListsGraph->Prim());
		cout << Prim_str << endl;

		if (m_io_ListsGraph->isBridge(m_deleteEdge))
			throw std::exception("The graph isn't connected , there is not MST");


		else {
			m_io_ListsGraph->RemoveEdge(m_deleteEdge->first, m_deleteEdge->second);

			Kruskal_second = "Kruskal " + std::to_string(m_io_ListsGraph->Kruskal(false));
			cout << Kruskal_second << endl;
		}
		writeToOutputFile(Kruskal_first + "\n" + Prim_str + "\n" + Kruskal_second + "\n");
	}
	else {
		throw std::exception("The graph isn't connected !! ");
	}
}
void Program::readGraphFromFile()
{
	ifstream data(m_i_InputFileName);
	std::string str;
	istringstream iss,iss2;

	try
	{
		std::getline(data, str);
		iss.str(str);
		std::string str2="";
		iss >> m_numOfVertices >> str2;
		if (m_numOfVertices < 1 && str2=="")
			throw std::invalid_argument(Error::INVALID_INPUT);


		std::getline(data, str);
		iss2.str(str);
		iss2 >> m_numOfEdges >> str2;
		if (m_numOfEdges < 1 && str2 == "")
			throw std::invalid_argument(Error::INVALID_INPUT);
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
						
		std::string str;
		int u = -1;
		int v = -1;
		int weight = -1;

		std::getline(i_Data, str);


		for (int i = 0; i < m_numOfEdges; i++)
		{
			try
			{
				if (str =="")
					std::getline(i_Data, str);  //read data from file object and put it into string.
				istringstream iss(str);
				iss >> u >> v >> weight;
				if ((u < 1 || v < 1 || weight < 0) && str!="")
					throw std::invalid_argument(Error::INVALID_INPUT);
			}
			catch (std::exception& error)
			{
				throw std::invalid_argument(Error::INVALID_INPUT);
			}

			if ((u > m_io_ListsGraph->GetSize() || v > m_io_ListsGraph->GetSize()) || u < 1 || v < 1 || weight < 0)
				throw std::invalid_argument(Error::INVALID_INPUT);
			
			m_io_ListsGraph->AddEdge(u, v, weight);
			u = -1;
			v = -1;
			weight = -1;
			str = "";
		}

		try
		{
			std::getline(i_Data, str);
			istringstream iss(str);
			iss >> u >> v >> weight;
			if (u < 1 || v < 1 || weight != -1)
				throw std::invalid_argument(Error::INVALID_INPUT);
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
void Program::writeToOutputFile(std::string st) { 
	ofstream myfile;
	myfile.open(m_i_OutputFileName);
	myfile << st <<endl;
	myfile.close();
}