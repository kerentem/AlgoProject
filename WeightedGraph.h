#pragma once
#include "AdjacentList.h"
#include "ErrorsHandler.h"
#include "DisjointSets.h"
#include <vector>
#include "QuickSort.h"
#include "PriorityQueue.h"
using namespace std;
enum class Color { white, gray, black };
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
	void AddDirctedEdge(int i_U, int i_V);
	void RemoveEdge(int i_U, int i_V);
	void RemoveDirctedEdge(int i_U, int i_V);
	int GetSize() const { return m_Size; }
	int Kruskal(bool isSorted);
	int Prim();
	bool isConnected();
	   
	void VISIT(int u, AdjacentList* m_Vertices, int currentRoot, int* Root, Color* visited, vector<int>* endList, WeightedGraph* directedGraph);
	vector<int>* DFS(vector<int>* orderList, AdjacentList* m_Vertices, int* Root, vector<int>* endList, WeightedGraph* directedGraph);
	bool isBridge(pair<int,int>* edge);

	void reverseGraph(WeightedGraph* directedGraph);




};