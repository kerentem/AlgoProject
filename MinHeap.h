#pragma once
#include <iostream>

typedef struct
{
	int key;
	int data;
	bool isInfinity;
}Pair;

class MinHeap
{
private:
	Pair* m_Arr;
	int m_Capacity;
	int m_Size;
	int m_Allocated;
	static int Left(int node);
	static int Right(int node);
	static int Parent(int node);
	void fixHeap(int node);
	void swap(int node1, int node2);
public:
	MinHeap(int max);
	MinHeap(int A[], int n);
	~MinHeap();
	bool IsEmpty() const
	{
		return m_Size == 0;
	}
	Pair Min();
	Pair DeleteMin();
	void Insert(Pair item);
	static MinHeap Build(int A[], int n) { return MinHeap(A, n); }
	void DecreaseKey(int Place, int NewKey);
};