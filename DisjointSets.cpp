#include "DisjointSets.h"
DisjointSets::DisjointSets(int n)
{
    this->m_NumOfSets = n;

    for (int i = 0; i < n; i++)
    {
        this->m_Size.push_back(0);
        this->m_Parent.push_back(-1);
    }
}
int DisjointSets::Find(int u)
{
    if (u != m_Parent[u-1])
        m_Parent[u-1] = DisjointSets::Find(m_Parent[u-1]);
    return m_Parent[u-1];
}
void DisjointSets::MakeSet(int x)
{
    m_Parent[x-1] = x;
    m_Size[x-1] = 1;
}
void DisjointSets::Union(int i_repX, int i_repY)
{

    if (m_Size[i_repX-1] > m_Size[i_repY-1])
    {
        m_Parent[i_repY-1] = i_repX;
        m_Size[i_repX-1] += m_Size[i_repY-1];
    }
    else
    {
        m_Parent[i_repX-1] = i_repY;
        m_Size[i_repY-1] += m_Size[i_repX-1];
    }
}
