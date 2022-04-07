#include "MinHeap.h"

MinHeap::MinHeap(int max)
{
	m_Arr = new Pair[max];
	m_Capacity = max;
	m_Size = 0;
	m_Allocated = 1;
}

MinHeap::~MinHeap()
{
	if (m_Allocated)
	{
		delete[] m_Arr;
	}
	m_Arr = NULL;
}

int MinHeap::Parent(int node)
{
	return (node - 1) / 2;
}

int MinHeap::Left(int node)
{
	return (2 * node + 1);
}

int MinHeap::Right(int node)
{
	return (2 * node + 2);
}

void MinHeap::fixHeap(int node)
{
	int min;
	int left = Left(node);
	int right = Right(node);

	if (left < m_Size && m_Arr[left].key < m_Arr[node].key)
		min = right;
	else
		min = node;
	if (right < m_Size && m_Arr[right].key < m_Arr[min].key)
		min = right;

	if (min != node)
	{
		swap(node, min);
		fixHeap(min);
	}
}

Pair MinHeap::Min()
{
	return m_Arr[0];
}

Pair MinHeap::DeleteMin()
{
	if (m_Size < 1)
	{

	}
	Pair min = m_Arr[0];
	m_Size--;
	m_Arr[0] = m_Arr[m_Size];
	fixHeap(0);
	return min;
}

void MinHeap::Insert(Pair item)
{
	if (m_Size == m_Capacity)
	{

	}
	int i = m_Size;
	m_Size++;

	while (i > 0 && m_Arr[Parent(i)].key > item.key)
	{
		m_Arr[i] = m_Arr[Parent(i)];
		i = Parent(i);
	}
	m_Arr[i] = item;
}

void MinHeap::swap(int node1, int node2)
{
	Pair temp = m_Arr[node1];
	m_Arr[node1] = m_Arr[node2];
	m_Arr[node2] = temp;
}

void MinHeap::DecreaseKey(int i_Place, int i_NewKey)
{
	{
		if (!(i_Place > 0 && i_Place <= m_Capacity))
		{
			//throw
		}

		int index = ;

		m_Arr[index].key = i_NewKey;
		fixHeap(index);
	}
}