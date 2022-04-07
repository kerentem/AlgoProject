#include "DisjointSets.h"
DisjointSets::DisjointSets(int n)
{
    this->m_NumOfSets = n;
    m_Parent = new int[n + 1];
    m_Size = new int[n + 1];

    for (int i = 0; i <= n; i++)
    {
        m_Size[i] = 0;
        m_Parent[i] = -1;
    }
}
int DisjointSets::Find(int u)
{
    if (u != m_Parent[u])
        m_Parent[u] = DisjointSets::Find(m_Parent[u]);
    return m_Parent[u];
}
void DisjointSets::MakeSet(int x)
{
    m_Parent[x] = x;
    m_Size[x] = 1;
}
void DisjointSets::Union(int i_repX, int i_repY)
{

    if (m_Size[i_repX] > m_Size[i_repY])
    {
        m_Parent[i_repY] = i_repX;
        m_Size[i_repX] += m_Size[i_repY];
    }
    else
    {
        m_Parent[i_repX] = i_repY;
        m_Size[i_repY] += m_Size[i_repX];
    }
}
