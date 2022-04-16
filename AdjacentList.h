#pragma once
#include <iostream>
#include <string>

struct ListNode
{
	int vertex;
	int weight;
	ListNode* next, * prev;
};

class AdjacentList
{
private:
	//const std::string ERROR_OUT_OF_RANGE_VERTEX_INDEX = "Invalid vertex index";
	//const std::string ERROR_EMPTY_LIST = "List is empty";
	int m_Size;
	ListNode* m_Head, * m_Tail;
	ListNode* makeNewNode(int i_Vertex, int i_Weight, ListNode* io_Next = nullptr);
	ListNode* findByIndex(int i_VertexIndex) const;
	void freeList();

public:
	AdjacentList() : m_Size(0), m_Head(nullptr), m_Tail(nullptr) {};
	AdjacentList(const AdjacentList& org);
	~AdjacentList();
	const AdjacentList& operator=(const AdjacentList& org);
	//
	// Methods
	void ToHead(int i_Vertex, int i_Weight);
	void ToTail(int i_Vertex, int i_Weight);
	void DeleteFromHead();
	void DeleteFromTail();
	void DeleteVertex(int i_Vertex);
	void AppendList(const AdjacentList& i_List);
	bool IsEmpty() { return m_Size == 0; }

	ListNode* Find(int i_U);

	const ListNode* operator[](int i_Index) const { return this->findByIndex(i_Index); }

	ListNode* operator[](int i_Index) { return this->findByIndex(i_Index); }

	const ListNode* getHeadNode() const { return m_Head; }
	int getSize() const { return m_Size; }
};
