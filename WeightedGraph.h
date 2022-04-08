#pragma once
#include "AdjacentList.h"
#include "ErrorsHandler.h"
#include "DisjointSets.h"
#include <vector>
#include "QuickSort.h"
using namespace std;

class WeightedGraph
{
private:
	int m_Size;
	AdjacentList* m_Vertices;

	//array of all edges for kruskal
	vector< pair<int, edge> > m_allEdges;
	void MakeEmptyGraph(int i_Size);
	bool isValidVertex(int i_U) const { return i_U > 0 && i_U <= m_Size; }
public:
	WeightedGraph(int i_Size);
	WeightedGraph() = delete;
	WeightedGraph(const WeightedGraph& org);
	~WeightedGraph();
	const WeightedGraph& operator=(const WeightedGraph& org);

	bool IsAdjacent(int i_U, int i_V) const;
	AdjacentList GetAdjList(int i_U) const;
	void AddEdge(int i_U, int i_V, int i_Weight);
	void RemoveEdge(int i_U, int i_V);
	int GetSize() const { return m_Size; }
	int Kruskal();
	int Prim();
};