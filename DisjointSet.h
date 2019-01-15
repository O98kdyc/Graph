#ifndef DISJOINTSET_H_INCLUDED
#define DISJOINTSET_H_INCLUDED

class DisjointSet
{
private:
    int Size;
    int *parent;
public:
    DisjointSet(int s);
    ~DisjointSet(){delete[] parent;}
    void Union(int root1, int root2);   //root1, root2Ϊ������
    int Find(int x);    //����x�ĸ��ڵ����ơ�
};

DisjointSet::DisjointSet(int s)
{
    Size = s;
    parent = new int [Size];
    for(int i=0; i<Size; ++i) parent[i] = -1;
}

void DisjointSet::Union(int root1, int root2)
{
//���������ӵġ�
    root1 = Find(root1);
    root2 = Find(root2);
//���������ӵġ�
    if(root1 == root2) return;
    if(parent[root1]>parent[root2])
    {
        parent[root2] += parent[root1];
        parent[root1] = root2;
    }
    else
    {
        parent[root1] += parent[root2];
        parent[root2] = root1;
    }
}

int DisjointSet::Find(int x)
{
    if(parent[x]<0) return x;
    return parent[x] = Find(parent[x]);
}


#endif // DISJOINTSET_H_INCLUDED
