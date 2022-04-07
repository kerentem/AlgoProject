#pragma once
#include <iostream>

class MinHeap
{
public:
	struct Node
	{
		int data;
		int key;
		bool isInfinity;

		bool operator<(const Node& other) const
		{
			bool case1 = isInfinity == false && other.isInfinity == true;
			bool case2 = isInfinity == false && other.isInfinity == false && key < other.key;

			return case1 || case2;
		}
	};

private:
	const std::string ERROR_FULL_HEAP = "Heap is full";
	const std::string ERROR_EMPTY_HEAP = "Heap is empty";
	const std::string ERROR_INVALID_KEY = "Invalid key";
	int m_Capacity, m_Size;
	Node* m_Arr;
	int* m_VerticesMap;
	bool m_NeedToDeAllocate;

	int getParent(int i_Size) const
	{
		return (i_Size - 1) / 2;
	}

	int getLeft(int i_Size) const
	{
		return (i_Size * 2) + 1;
	}

	int getRight(int i_Size) const
	{
		return (i_Size * 2) + 2;
	}

	void swapNodes(int i_First, int i_Second)
	{
		Node temp = m_Arr[i_First];

		m_Arr[i_First] = m_Arr[i_Second];
		m_Arr[i_Second] = temp;
	}

	void swapIndexs(int i_First, int i_Second)
	{
		int temp = m_VerticesMap[i_First];

		m_VerticesMap[i_First] = m_VerticesMap[i_Second];
		m_VerticesMap[i_Second] = temp;
	}

	void swap(int i_First, int i_Second)
	{
		swapIndexs(i_First, i_Second);
		swapNodes(m_VerticesMap[i_First], m_VerticesMap[i_Second]);
	}

	void heapify(int i_Root = 0)
	{
		int left = getLeft(i_Root), right = getRight(i_Root), min = i_Root;

		if (isValidVertex(left) && m_Arr[left] < m_Arr[i_Root])
		{
			min = left;
		}

		if (isValidVertex(right) && m_Arr[right] < m_Arr[min])
		{
			min = right;
		}

		if (min != i_Root)
		{
			swap(m_Arr[i_Root].data, m_Arr[min].data);
			heapify(min);
		}
	}

	void fixUp(int i_I = 0)
	{
		int i = i_I == 0 ? m_Size - 1 : i_I;

		while (i > 0)
		{
			int parent = getParent(i);

			if (m_Arr[i] < m_Arr[parent])
			{
				swap(m_Arr[i].data, m_Arr[parent].data);
				i = parent;
			}
			else
			{
				break;
			}
		}
	}

	bool isValidVertex(int i_Vertex) const
	{
		return i_Vertex > 0 && i_Vertex < m_Size;
	}

public:
	MinHeap() = delete;
	MinHeap(const MinHeap& org) = default;
	MinHeap& operator=(const MinHeap& org) = default;

	~MinHeap()
	{
		if (m_NeedToDeAllocate)
		{
			delete[] m_Arr;
		}

		delete[] m_VerticesMap;
	}

	MinHeap(int i_Size)
	{
		m_Capacity = i_Size;
		m_Size = 0;
		m_Arr = new Node[m_Capacity];
		m_VerticesMap = new int[m_Capacity + 1];
		m_NeedToDeAllocate = true;

		for (int i = 0; i < m_Capacity; i++)
		{
			m_Arr[i].isInfinity = true;
		}
	}

	MinHeap(Node* io_Arr, int i_Size)
	{
		m_Size = m_Capacity = i_Size;
		m_Arr = io_Arr;
		m_NeedToDeAllocate = false;
		m_VerticesMap = new int[m_Capacity + 1];

		// floyd algorithm
		for (int i = (m_Size / 2) - 1; i >= 0; i--)
		{
			heapify(i);
		}

		for (int i = 1; i <= m_Capacity; i++)
		{
			int currVertex = m_Arr[i].data;

			m_VerticesMap[currVertex] = i;
		}
	}

	static MinHeap Build(int i_Size)
	{
		return MinHeap(i_Size);
	}

	static MinHeap Build(Node* io_Arr, int i_Size)
	{
		return MinHeap(io_Arr, i_Size);
	}

	bool IsEmpty() const
	{
		return m_Size == 0;
	}

	int DeleteMin()
	{
		if (IsEmpty())
		{
			throw std::out_of_range(ERROR_EMPTY_HEAP);
		}

		int res = m_Arr[0].data;
		m_Arr[0].isInfinity = true;

		m_Size--;
		swap(m_Arr[0].data, m_Arr[m_Size].data);
		heapify();

		return res;
	}

	void DecreaseKey(int i_Vertex, int i_NewKey)
	{
		if (!(i_Vertex > 0 && i_Vertex <= m_Capacity))
		{
			throw std::invalid_argument(ERROR_INVALID_KEY);
		}

		int index = m_VerticesMap[i_Vertex];

		m_Arr[index].key = i_NewKey;
		m_Arr[index].isInfinity = false;
		fixUp(index);
	}

	int GetSize() const
	{
		return m_Size;
	}

	void Insert(const Node& i_NewNode)
	{
		if (m_Size == m_Capacity)
		{
			throw std::out_of_range(ERROR_FULL_HEAP);
		}

		m_Arr[m_Size].data = i_NewNode.data;
		m_Arr[m_Size].key = i_NewNode.key;
		m_Arr[m_Size].isInfinity = i_NewNode.isInfinity;
		m_VerticesMap[i_NewNode.data] = m_Size;
		m_Size++;
		fixUp();
	}
};