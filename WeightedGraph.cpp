#include "WeightedGraph.h"


WeightedGraph::WeightedGraph(int i_Size)
{
	if (i_Size <= 0)
	{
		throw std::invalid_argument(Error::CONSTRUCTOR_INPUT_NON_POSITIVE);
	}

	m_Size = i_Size;
	m_Vertices = new AdjacentList[m_Size];
}
WeightedGraph::~WeightedGraph()
{
	delete[] m_Vertices;
}
WeightedGraph WeightedGraph::MakeEmptyGraph(int i_Size)
{
	return WeightedGraph(i_Size);
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

void WeightedGraph::AddEdge(int i_U, int i_V, float i_Weight)
{
	if (!this->isValidVertex(i_U) || !this->isValidVertex(i_V))
	{
		throw std::out_of_range(Error::OUT_OF_RANGE_VERTEX_INDEX);
	}

	m_Vertices[i_U - 1].ToTail(i_V, i_Weight);
}

void WeightedGraph::RemoveEdge(int i_U, int i_V)
{
	if (!this->isValidVertex(i_U) || !this->isValidVertex(i_V))
	{
		throw std::out_of_range(Error::OUT_OF_RANGE_VERTEX_INDEX);
	}

	m_Vertices[i_U - 1].DeleteVertex(i_V);
}

int WeightedGraph::Kruskal()
{

}