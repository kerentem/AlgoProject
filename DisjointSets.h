#pragma once
#include <vector>
using namespace std;

class DisjointSets
{
private:
	vector<int> m_Parent;
	vector<int> m_Size;
	int m_NumOfSets;

public:
	DisjointSets(int n);
	void MakeSet(int x);
	int Find(int u);
	void Union(int repX, int repY);
};

