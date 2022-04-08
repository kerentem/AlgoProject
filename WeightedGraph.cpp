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
int WeightedGraph::Kruskal()
{
	int mstWeight = 0; 
	DisjointSets ds(m_Size);

	quickSort(m_allEdges, 1 , m_allEdges.size()-1);

	for (int i = 1;i <= m_Size;i++)
	{
		ds.MakeSet(i);
	}

	vector< pair<int, edge> >::iterator it;
	for (it = m_allEdges.begin(); it != m_allEdges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int repU = ds.Find(u);
		int repV = ds.Find(v);

		if (repU != repV)
		{
			// Current edge will be in the MST
			// so print it
			cout << u << " - " << v << endl;

			mstWeight += it->first;
			ds.Union(repU, repV);
		}
	}

	return mstWeight;
}
int WeightedGraph::Prim()
{
	return 0;
}