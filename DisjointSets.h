#pragma once
class DisjointSets
{
private:
	int* m_Parent;
	int* m_Size;
	int m_NumOfSets;

public:
	DisjointSets(int n);
	void MakeSet(int x);
	int Find(int u);
	void Union(int repX, int repY);
};

