#include "AdjacentList.h"

AdjacentList::~AdjacentList()
{
	this->freeList();
}

ListNode* AdjacentList::makeNewNode(int i_Vertex, float i_Weight, ListNode* io_Next)
{
	ListNode* newNode = new ListNode;

	newNode->vertex = i_Vertex;
	newNode->weight = i_Weight;
	newNode->next = io_Next;
	newNode->prev = nullptr;

	return newNode;
}

void AdjacentList::ToHead(int i_Vertex, float i_Weight)
{
	ListNode* newHead = this->makeNewNode(i_Vertex, i_Weight, m_Head);

	if (this->IsEmpty())
	{
		m_Head = m_Tail = newHead;
	}
	else
	{
		m_Head->prev = newHead;
		m_Head = newHead;
	}

	m_Size++;
}

void AdjacentList::ToTail(int i_Vertex, float i_Weight)
{
	ListNode* newTail = this->makeNewNode(i_Vertex, i_Weight);

	newTail->prev = m_Tail;
	if (this->IsEmpty())
	{
		m_Head = m_Tail = newTail;
	}
	else
	{
		m_Tail->next = newTail;
		m_Tail = newTail;
	}

	m_Size++;
}
void AdjacentList::DeleteFromHead()
{
	if (this->IsEmpty())
	{
		//throw ERROR_EMPTY_LIST;
	}

	if (m_Size == 1)
	{
		delete m_Head;
		m_Head = m_Tail = nullptr;
	}
	else
	{
		ListNode* lastHead = m_Head;

		m_Head = lastHead->next;
		m_Head->prev = nullptr;
		delete lastHead;
	}

	m_Size--;
}
void AdjacentList::DeleteFromTail()
{
	if (this->IsEmpty())
	{
		//throw ERROR_EMPTY_LIST;
	}

	if (m_Size == 1)
	{
		delete m_Head;
		m_Head = m_Tail = nullptr;
	}
	else
	{
		ListNode* lastTail = m_Tail;

		m_Tail = lastTail->prev;
		m_Tail->next = nullptr;
		delete lastTail;
	}

	m_Size--;
}
AdjacentList::AdjacentList(const AdjacentList& org)
{
	m_Size = 0;
	m_Head = m_Tail = nullptr;

	this->AppendList(org);
}
const AdjacentList& AdjacentList::operator=(const AdjacentList& org)
{
	if (this != &org)
	{
		this->freeList();
		this->AppendList(org);
	}

	return *this;
}
const ListNode* AdjacentList::Find(int i_U)
{
	ListNode* currentNode = m_Head;

	while (currentNode != nullptr)
	{
		if (currentNode->vertex == i_U)
		{
			break;
		}
	}

	return currentNode;
}
void AdjacentList::DeleteVertex(int i_Vertex)
{
	ListNode* currentNode = m_Head;

	while (currentNode != nullptr && currentNode->vertex != i_Vertex)
	{
		currentNode = currentNode->next;
	}

	if (currentNode == m_Head)
	{
		this->DeleteFromHead();
	}
	else if (currentNode == m_Tail)
	{
		this->DeleteFromTail();
	}
	else if (currentNode != nullptr)
	{
		currentNode->prev->next = currentNode->next;
		currentNode->next->prev = currentNode->prev;
		delete currentNode;
		m_Size--;
	}
}

ListNode* AdjacentList::findByIndex(int i_VertexIndex) const
{
	if (i_VertexIndex < m_Size)
	{
		//throw std::out_of_range(ERROR_OUT_OF_RANGE_VERTEX_INDEX);
	}

	ListNode* currentNode = m_Head;

	for (int i = 0; i < i_VertexIndex; i++)
	{
		currentNode = currentNode->next;
	}

	return currentNode;
}

void AdjacentList::freeList()
{
	ListNode* currentNode = m_Head;

	while (currentNode != nullptr)
	{
		ListNode* tempNode = currentNode;

		currentNode = currentNode->next;
		delete tempNode;
	}
}
void AdjacentList::AppendList(const AdjacentList& i_List)
{
	ListNode* currentNode = i_List.m_Head;
	while (currentNode != nullptr)
	{
		this->ToTail(currentNode->vertex, currentNode->weight);
		currentNode = currentNode->next;
	}
}