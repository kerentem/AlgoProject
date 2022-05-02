#include "PriorityQueue.h"

int PriorityQueue::getParent(int i_Size) const
{
	return (i_Size - 1) / 2;
}
int PriorityQueue::getLeft(int i_Size) const
{
	return (i_Size * 2) + 1;
}
int PriorityQueue::getRight(int i_Size) const
{
	return (i_Size * 2) + 2;
}
void PriorityQueue::swapPairs(int i_First, int i_Second)
{
	pair<int, int> temp = m_Arr[i_First];

	m_Arr[i_First] = m_Arr[i_Second];
	m_Arr[i_Second] = temp;
}
void PriorityQueue::swapIndexs(int i_First, int i_Second)
{
	int temp = m_VerticesMap[i_First];

	m_VerticesMap[i_First] = m_VerticesMap[i_Second];
	m_VerticesMap[i_Second] = temp;
}
void PriorityQueue::swap(int i_First, int i_Second)
{
	swapIndexs(i_First - 1, i_Second - 1);
	swapPairs(m_VerticesMap[i_First - 1], m_VerticesMap[i_Second - 1]);
}
void PriorityQueue::heapify(int i_Root)
{
	int left = getLeft(i_Root), right = getRight(i_Root), min = i_Root;

	if (isValidVertex(left) && m_Arr[left].second < m_Arr[i_Root].second)
	{
		min = left;
	}

	if (isValidVertex(right) && m_Arr[right].second < m_Arr[min].second)
	{
		min = right;
	}

	if (min != i_Root)
	{
		swap(m_Arr[i_Root].first, m_Arr[min].first);
		heapify(min);
	}
}
void PriorityQueue::fixUp(int i_I)
{
	int i = i_I == 0 ? m_Size - 1 : i_I;

	while (i > 0)
	{
		int parent = getParent(i);

		if (m_Arr[i].second < m_Arr[parent].second)
		{
			swap(m_Arr[i].first, m_Arr[parent].first);
			i = parent;
		}
		else
		{
			break;
		}
	}
}
bool PriorityQueue::isValidVertex(int i_Vertex) const
{
	return i_Vertex > 0 && i_Vertex < m_Size;
}

void PriorityQueue::Build(vector<int> min)
	{
		for (int i = 0; i < min.size(); i++)
		{
			m_Arr.push_back(make_pair(i + 1, min[i]));
		}
		m_Size = min.size();

		// floyd algorithm
		for (int i = (m_Size / 2) - 1; i >= 0; i--)
		{
			heapify(i);
		}

		m_VerticesMap.resize(m_Size);
		for (int i = 0; i < m_Size; i++)
		{
			int currVertex = m_Arr[i].first;
			m_VerticesMap[currVertex - 1] = i;
		}
	}
bool PriorityQueue::IsEmpty() const
	{
		return m_Size == 0;
	}
int PriorityQueue::DeleteMin()
	{
		if (IsEmpty())
		{
			throw std::out_of_range(ERROR_EMPTY_HEAP);
		}

		int res = m_Arr[0].first;

		m_Size--;
		swap(m_Arr[0].first, m_Arr[m_Size].first);
		m_Arr.pop_back();
		heapify();

		return res;
	}
void PriorityQueue::DecreaseKey(int i_Vertex, int i_NewKey)
	{
		if (!(i_Vertex > 0 && i_Vertex <= m_VerticesMap.size()))
		{
			throw std::invalid_argument(ERROR_INVALID_KEY);
		}

		int index = m_VerticesMap[i_Vertex - 1];

		m_Arr[index].second = i_NewKey;
		fixUp(index);
	}