#include "WeightedGraph.h"

WeightedGraph::~WeightedGraph()
{delete[] m_Vertices;}

WeightedGraph::WeightedGraph(int i_Size)
{MakeEmptyGraph(i_Size);}

void WeightedGraph::MakeEmptyGraph(int i_Size)
{
	if (i_Size <= 0)
	{
		throw std::invalid_argument(Error::CONSTRUCTOR_INPUT_NON_POSITIVE);
	}

	this->m_Size = i_Size;
	this->m_Vertices = new AdjacentList[m_Size];
}
WeightedGraph::WeightedGraph(const WeightedGraph& org)
{

	m_Size = 0;
	*this = org;
}
const WeightedGraph& WeightedGraph::operator=(const WeightedGraph& org)
{
	if (this != &org)
	{
		// delete old data
		if (m_Size > 0)
		{
			delete[] m_Vertices;
		}

		// copy data
		m_Size = org.m_Size;
		m_Vertices = new AdjacentList[m_Size];

		for (int i = 0; i < m_Size; i++)
		{
			m_Vertices[i] = org.m_Vertices[i];
		}
	}

	return *this;
}
bool WeightedGraph::IsAdjacent(int i_U, int i_V) const
{
	if (!this->isValidVertex(i_U) || !this->isValidVertex(i_V))
	{
		throw std::out_of_range(Error::OUT_OF_RANGE_VERTEX_INDEX);
	}

	return m_Vertices[i_U - 1].Find(i_V) != nullptr;
}
AdjacentList WeightedGraph::GetAdjList(int i_U) const
{
	if (!this->isValidVertex(i_U))
	{
		throw std::out_of_range(Error::OUT_OF_RANGE_VERTEX_INDEX);
	}

	return m_Vertices[i_U - 1];
}
void WeightedGraph::AddEdge(int i_U, int i_V, int i_Weight)
{
	if (!this->isValidVertex(i_U) || !this->isValidVertex(i_V))
	{
		throw std::out_of_range(Error::OUT_OF_RANGE_VERTEX_INDEX);
	}

	m_Vertices[i_U - 1].ToTail(i_V, i_Weight);
	m_Vertices[i_V - 1].ToTail(i_U, i_Weight);

	pair<int, edge> newEdge{ i_Weight, { i_U,i_V } };
	m_allEdges.push_back(newEdge);
}
void WeightedGraph::AddDirctedEdge(int i_U, int i_V)
{
	if (!this->isValidVertex(i_U) || !this->isValidVertex(i_V))
	{
		throw std::out_of_range(Error::OUT_OF_RANGE_VERTEX_INDEX);
	}
	m_Vertices[i_U - 1].ToTail(i_V, 0);
}
void WeightedGraph::RemoveEdge(int i_U, int i_V)
{
	if (!this->isValidVertex(i_U) || !this->isValidVertex(i_V))
	{
		throw std::out_of_range(Error::OUT_OF_RANGE_VERTEX_INDEX);
	}

	m_Vertices[i_U - 1].DeleteVertex(i_V);
	m_Vertices[i_V - 1].DeleteVertex(i_U);

	int indexToRemove;
	for (int i = 0;i < m_allEdges.size();i++)
	{
		if (m_allEdges[i].second.first == i_V && m_allEdges[i].second.second == i_U ||
			m_allEdges[i].second.first == i_U && m_allEdges[i].second.second == i_V)
			indexToRemove = i;

	}
	m_allEdges.erase(m_allEdges.begin() + indexToRemove);
}
void WeightedGraph::RemoveDirctedEdge(int i_U, int i_V)
{
	if (!this->isValidVertex(i_U) || !this->isValidVertex(i_V))
		throw std::out_of_range(Error::OUT_OF_RANGE_VERTEX_INDEX);

	m_Vertices[i_U - 1].DeleteVertex(i_V);

}
int WeightedGraph::Kruskal(bool isSorted)
{
	int mstWeight = 0; 
	DisjointSets ds(m_Size);

	if (! isSorted)
		quickSort(m_allEdges, 0 , m_allEdges.size()-1);

	for (int i = 1;i <= m_Size;i++)
		ds.MakeSet(i);

	vector< pair<int, edge> >::iterator it;
	for (it = m_allEdges.begin(); it != m_allEdges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int repU = ds.Find(u);
		int repV = ds.Find(v);

		if (repU != repV)
		{
			mstWeight += it->first;
			ds.Union(repU, repV);
		}
	}

	return mstWeight;
}
int WeightedGraph::Prim()
{
	const int INFINIT = INT32_MAX;
	PriorityQueue pq;
	vector<bool> inT;
	vector<int> min;
	vector<int> parent;
	int MSTWeight = 0;


	//init
	for (int i = 0;i < m_Size;i++)
	{
		min.push_back(INFINIT);
		inT.push_back(false);
		parent.push_back(-1);
	}

	//choose random v
	min[0] = 0;
	inT[0] = true;

	pq.Build(min);

	while (!pq.IsEmpty())
	{
		int u = pq.DeleteMin();
		inT[u - 1] = true;
		AdjacentList uNeighbors = this->GetAdjList(u);
		for (int i = 0;i < uNeighbors.getSize();i++)
		{
			int v = uNeighbors[i]->vertex;
			int edgeWeight = uNeighbors[i]->weight;

			if (!inT[v - 1] && uNeighbors[i]->weight < min[v - 1])
			{
				min[v-1] = edgeWeight;
				parent[v - 1] = u-1;
				pq.DecreaseKey(v, min[v-1]);
			}
		}

	}
	//calculate MST weight
	for (int i = 1;i < parent.size();i++)
	{
		MSTWeight += GetAdjList(i+1).Find(parent[i]+1)->weight;
	}
	return MSTWeight;
}

bool WeightedGraph::isConnected() {
	vector<int>* orderList = new vector<int>;
	for (int i = 0; i < m_Size; i++)
		orderList->push_back(i+1);

	int* Root = new int[m_Size];
	vector<int>* countConnected = DFS(orderList, m_Vertices,Root,nullptr, nullptr);
	if (countConnected->size() == 1) // Given graph is connected
		return true;
	else //"Given graph is not connected
		return false;
}
vector<int>* WeightedGraph::DFS(vector<int>* orderList, AdjacentList* m_Vertices, int* Root, vector<int>* endList, WeightedGraph* directedGraph) {
	Color* visited = new Color[m_Size];
	int currentRoot;
	vector<int>* ConnectedList = new vector<int>;

	for (int i = 0; i < m_Size; i++)
		visited[i] = Color::white;

	for (int i = 0; i < m_Size; i++) {
		if (visited[orderList->at(i)-1] == Color::white) {
			currentRoot = orderList->at(i);
			VISIT(m_Vertices->findByIndex(currentRoot-1), m_Vertices, currentRoot, Root, visited, endList, directedGraph);
			ConnectedList->push_back(orderList->at(i));
		}
		return ConnectedList;
	}
}
void WeightedGraph::VISIT(const ListNode * u, AdjacentList * m_Vertices, int currentRoot, int* Root, Color * visited, vector<int>* endList, WeightedGraph* directedGraph)
{
	Root[u->vertex - 1] = currentRoot;
	visited[u->vertex - 1] = Color::gray;
	AdjacentList adjacentList = GetAdjList(u->vertex);
	const ListNode* node = adjacentList.getHeadNode();
	while (node != nullptr)
	{
		if (visited[node->vertex-1] == Color::white)
		{
			if (directedGraph != nullptr)
			{
				//cout << u->vertex<< " "<< node->vertex << endl;
				directedGraph->AddDirctedEdge(u->vertex, node->vertex);
			}
				
			VISIT(node, m_Vertices, currentRoot, Root, visited,endList,directedGraph);
		}
		node = node->next;
	}
	visited[u->vertex - 1] = Color::black;
	if (endList != nullptr)
		endList->push_back(u->vertex);
}

bool WeightedGraph::isBridge(pair<int, int>* edge)
{
	WeightedGraph* directedGraph = new WeightedGraph(m_Size);
	vector<int>* endList = new vector<int>;
	vector<int>* orderList = new vector<int>;
	for (int i = 0; i < m_Size; i++)
		orderList->push_back(i+1);
	int* Root = new int[m_Size];

	vector<int>* countConnected = DFS(orderList, m_Vertices, Root, endList, directedGraph);
	std::reverse(endList->begin(), endList->end());
	reverseGraph(directedGraph);
	countConnected = DFS(endList, m_Vertices, Root, endList, directedGraph);
	if (Root[edge->first - 1] == Root[edge->second - 1])
		return false;
	else
		return true;
}


void WeightedGraph::reverseGraph(WeightedGraph* directedGraph) {
	WeightedGraph* oppGraph = new WeightedGraph(directedGraph->GetSize());
	//cout  << "--- " <<endl;

	for (int i = 0; i < directedGraph->GetSize(); i++)
	{
		AdjacentList adjList = directedGraph->GetAdjList(i+1);
		const ListNode* node = adjList.getHeadNode();
		while (node != nullptr)
		{
			oppGraph->AddDirctedEdge(node->vertex , i+1);
			//cout << node->vertex << " " << i + 1 << endl;
			node = node->next;
		}
	}
}
