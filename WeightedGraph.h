#pragma once
#include "AdjacentList.h"
#include "ErrorsHandler.h"
class WeightedGraph
{
private:
	int m_Size;
	AdjacentList* m_Vertices;
	bool isValidVertex(int i_U) const { return i_U > 0 && i_U <= m_Size; }

public:
	WeightedGraph(int i_Size);
	WeightedGraph() = delete;
	WeightedGraph(const WeightedGraph& org);
	~WeightedGraph();
	const WeightedGraph& operator=(const WeightedGraph& org);
	//
	// Methods
	static WeightedGraph MakeEmptyGraph(int i_Size);
	bool IsAdjacent(int i_U, int i_V) const;
	AdjacentList GetAdjList(int i_U) const;
	void AddEdge(int i_U, int i_V, float i_Weight);
	void RemoveEdge(int i_U, int i_V);
	int GetSize() const { return m_Size; }
	int Kruskal();
};