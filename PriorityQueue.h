#pragma once
#include <iostream>
#include <vector>
using namespace std;
class PriorityQueue
{

private:
	const std::string ERROR_FULL_HEAP = "Heap is full";
	const std::string ERROR_EMPTY_HEAP = "Heap is empty";
	const std::string ERROR_INVALID_KEY = "Invalid key";
	int m_Size=0;
	vector<pair<int,int>> m_Arr;//(data,key)
	vector<int> m_VerticesMap;


	int getParent(int i_Size) const;
	int getLeft(int i_Size) const;
	int getRight(int i_Size) const;
	void swapPairs(int i_First, int i_Second);
	void swapIndexs(int i_First, int i_Second);
	void swap(int i_First, int i_Second);
	void heapify(int i_Root = 0);
	void fixUp(int i_I = 0);
	bool isValidVertex(int i_Vertex) const;
public:
	PriorityQueue() = default;
	PriorityQueue(const PriorityQueue& org) = default;
	PriorityQueue& operator=(const PriorityQueue& org) = default;

	void Build(vector<int> min);
	bool IsEmpty() const;
	int DeleteMin();
	void DecreaseKey(int i_Vertex, int i_NewKey);
};