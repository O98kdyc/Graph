#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <iostream>
#include "linkqueue.h"
#include "DisjointSet.h"
#include "priorityQueue.h"
using namespace std;

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph
{
    public:
        adjListGraph(int vSize, const TypeOfVer d[]);
	    void insert(TypeOfVer x, TypeOfVer y,TypeOfEdge w);
	    void remove(TypeOfVer x, TypeOfVer y);
	    bool exist(TypeOfVer x, TypeOfVer y) const;
	    ~adjListGraph();
	    void dfs() const;
	    void bfs() const;
	    void kruskal() const;
	    bool dfs(TypeOfVer s,TypeOfVer e);
	    bool bfs(TypeOfVer s,TypeOfVer e);
	    void prim(TypeOfEdge noEdge) const;
	    void dijkstra(TypeOfVer start, TypeOfEdge noEdge) const;
	    void printPath(int start,int end,int prev[]) const;
    private:
        int Vers,Edges;
        struct edgeNode
        {                   //邻接表中存储边的结点类
		int end;                          //终点编号
		TypeOfEdge weight;                //边的权值
		edgeNode *next;
		edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL)
			{ end = e; weight = w; next = n;}
	    };
	   struct verNode{                     //保存顶点的数据元素类型
		  TypeOfVer ver;                   //顶点值
		  edgeNode *head;                 //对应的单链表的头指针
		 verNode( edgeNode *h = NULL) { head = h;}
	  };
	  verNode *verList;
      int find(TypeOfVer v) const
      {
          for(int i=0;i<Vers;++i)
            if(verList[i].ver==v) return i;
      }
      void dfs(int start, bool visited[]) const;
      void dfs1(int start,bool visited[]);
      struct edge
      {
          int beg,end;
          TypeOfEdge w;
          bool operator<(const edge &rp) const{return w<rp.w;}
      };
};

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[])
{
    Vers = vSize; Edges = 0;
    verList = new verNode[vSize];
    for (int i = 0; i < Vers; ++i) verList[i].ver = d[i];
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{    int i;
      edgeNode *p;
     for (i = 0; i < Vers; ++i)
	 while ((p = verList[i].head) != NULL) {
		   verList[i].head = p->next;
		   delete p;
	 }
     delete [] verList;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w)
{
    int u = find(x), v = find(y);
    verList[u].head = new edgeNode(v, w, verList[u].head );
    ++Edges;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::remove(TypeOfVer x,TypeOfVer y)
{     int u = find(x), v = find(y);
	edgeNode *p = verList[u].head, *q;
     if (p == NULL) return;  //结点u没有相连的边 
     if (p->end == v) {       //单链表中的第一个结点就是被删除的边
        verList[u].head = p->next;
        delete p; --Edges;
        return;
     }
     while (p->next !=NULL && p->next->end != v) p = p->next;//查找被删除的边
     if (p->next != NULL) {               //删除
         q = p->next;          p->next = q->next;          delete q;        --Edges;    }
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const
{
	   int u = find(x), v = find(y);
       edgeNode *p = verList[u].head;
       while (p !=NULL && p->end != v) p = p->next;
       if (p == NULL) return false; else  return true;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs() const
{bool *visited = new bool[Vers];

 for (int i=0; i < Vers; ++i) visited[i] = false;
 cout << "dfs" << endl;
 for (int i = 0; i < Vers; ++i) {
	 if (visited[i] == true) continue;
	 dfs(i, visited);
	 cout << endl;
     }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const
{ edgeNode *p = verList[start].head;
  cout << verList[start].ver << '\t';
  visited[start] = true;
  while (p != NULL){
	  if (visited[p->end] == false) dfs(p->end, visited);
	  p = p->next;
  }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs1(int start,bool visited[])
{
    edgeNode *p = verList[start].head;
    visited[start] = true;
    while (p != NULL)
    {
	  if (visited[p->end] == false) dfs1(p->end, visited);
      p = p->next;
    }
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::dfs(TypeOfVer s,TypeOfVer e)
{
    int m=find(e);
    int n=find(s);
    bool *visited = new bool[Vers];
    for (int i=0; i < Vers; ++i) visited[i] = false;
    dfs1(n,visited);
    return visited[m];
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs() const
{ bool *visited = new bool[Vers];
   int currentNode;
   linkQueue<int> q;
   edgeNode *p;
   for (int i=0; i < Vers; ++i) visited[i] = false;
   cout << "bfs" << endl;
for (int i = 0; i < Vers; ++i) {
	 if (visited[i] == true) continue;
	 q.enQueue(i);
      while (!q.isEmpty()) {
		 currentNode = q.deQueue();
		 if (visited[currentNode] == true) continue;
		 cout << verList[currentNode].ver << '\t';
		 visited[currentNode] = true;
		 p = verList[currentNode].head;
		 while (p != NULL){
	                if (visited[p->end] == false) q.enQueue(p->end);
	                p = p->next;
		     }      }
	 cout << endl;
   }
  }

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::bfs(TypeOfVer s,TypeOfVer e)
{  bool *visited = new bool[Vers];
   int currentNode;
   linkQueue<int> q;
   edgeNode *p;
   for (int i=0; i < Vers; ++i) visited[i] = false;
   int m=find(s),n=find(e);
	 q.enQueue(m);
      while (!q.isEmpty()) {
		 currentNode = q.deQueue();
		 if (visited[currentNode] == true) continue;

		 visited[currentNode] = true;
		 p = verList[currentNode].head;
		 while (p != NULL){
	                if (visited[p->end] == false) q.enQueue(p->end);
	                p = p->next;
		     }      }
    return visited[n];
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::kruskal( ) const
{ int edgesAccepted = 0,u,v;
   edgeNode *p;
   edge  e;
   DisjointSet ds( Vers );
   priorityQueue<edge> pq;

   //生成优先级队列
   for (int i = 0; i< Vers; ++i) {
	for (p = verList[i].head; p != NULL; p = p->next)
		if (i < p->end) { e.beg = i;
			            e.end = p->end;
			            e.w = p->weight;
			            pq.enQueue(e); }
	}
	//开始归并
    while( edgesAccepted < Vers - 1 )
    {  e = pq.deQueue();
        u = ds.Find(e.beg);
	    v = ds.Find(e.end);
        if( u != v )
          {  edgesAccepted++;
              ds.Union( u, v );
		  cout << '(' << verList[e.beg].ver << ','
                      << verList[e.end].ver  << ")\t";
        }
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::prim(TypeOfEdge noEdge) const
{ bool *flag = new bool[Vers];
  TypeOfEdge *lowCost = new TypeOfEdge[Vers];
  int *startNode = new int[Vers];
  edgeNode *p;
  TypeOfEdge min;
  int start, i, j;

  for (i = 0; i < Vers; ++i) {
	  flag[i] = false;
	  lowCost[i] = noEdge;  }
  start = 0;
  for ( i= 1; i < Vers; ++i) {
	  for (p = verList[start].head; p != NULL; p = p->next)
  	        if (!flag[p->end] && lowCost[p->end] > p->weight) {
		     lowCost[p->end] = p->weight;
	              startNode[p->end] = start;  }
	  flag[start] = true;
	  min = noEdge;
	  for (j = 0; j < Vers; ++j)
		  if (lowCost[j] < min) {min = lowCost[j]; start = j;}
	  cout << '(' << verList[startNode[start]].ver <<","<< verList[start].ver << ")\t";
	  lowCost[start] = noEdge;
      }
  delete [] flag;
  delete [] startNode;
  delete [] lowCost;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dijkstra(TypeOfVer start, TypeOfEdge noEdge) const
{ TypeOfEdge *distance = new TypeOfEdge[Vers];
  int *prev = new int [Vers];
  bool *known = new bool[Vers];
  int u,sNo,i,j;
  edgeNode *p;
  TypeOfEdge min;
  for (i = 0; i< Vers; ++i)
    {                             //初始化
    known[i] = false;
    distance[i] = noEdge;
   }
  sNo = find(start);
  distance[sNo]=0;
  prev[sNo]=sNo;
  for (i = 1; i < Vers; ++i) {
	  min = noEdge;
	  for (j = 0; j < Vers; ++j)
	        if (!known[j] && distance[j] < min) { min = distance[j]; u = j;}
         known[u] = true; //将u放入S
 	   for (p = verList[u].head; p != NULL; p = p->next)
	         if (!known[p->end] && distance[p->end] > min + p->weight) {
                       distance[p->end] = min + p->weight;
                       prev[p->end] = u;   }
    }
   for (i = 0; i < Vers; ++i) { //输出所有的路径信息
	  cout << "from" << start << "to" << verList[i].ver << "path" << endl;
	  printPath(sNo, i, prev);
	  cout << " distance" << distance[i] << endl;
   }
 }

 template <class TypeOfVer, class TypeOfEdge>
 void adjListGraph<TypeOfVer, TypeOfEdge>::printPath(int start,int end,int prev[]) const
 {
     if(start==end)
     {
         cout<<verList[start].ver;
         return;
     }
     printPath(start,prev[end],prev);
     cout<<"-"<<verList[end].ver;
 }

#endif // GRAPH_H_INCLUDED
