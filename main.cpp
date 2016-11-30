#include <stdio.h>
#include<stdlib.h>
typedef struct AdjVNode *edge;
typedef int Vertex;
struct AdjVNode{
    Vertex AdjV;
    int weighted;
    edge Next;
};

typedef struct Vnode{
    int number;
    edge FirstEdge;
}*AdjList;
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;
    int Ne;
    int Cmax;
    AdjList G;
};
typedef PtrToGNode LGraph;
LGraph create(int *Sp);
edge findLastedge(edge a);
int main() {
    int Sp;
    LGraph graph=create(&Sp);
    printf("%d%d",graph->Nv,Sp);
    return 0;
}
LGraph create(int *Sp)
{
    LGraph  graph;
    graph=(LGraph)malloc(sizeof(struct GNode));
    graph->G=(AdjList)malloc((graph->Nv+1)*sizeof(struct Vnode));
    scanf("%d%d%d%d",&graph->Cmax,&graph->Nv,Sp,&graph->Ne);
    int i;
    for(i=1;i<=graph->Nv;i++)
    {
        scanf("%d",&graph->G[i].number);
        graph->G[i].FirstEdge=NULL;
    }
    for(i=0;i<graph->Ne;i++)
    {
        edge temp;
        int Si,Sj,Tij;
        scanf("%d%d%d",&Si,&Sj,&Tij);
        if(graph->G[Si].FirstEdge==NULL)
        {
            graph->G[Si].FirstEdge=(edge)malloc(sizeof(struct AdjVNode));
            graph->G[Si].FirstEdge->Next=NULL;
            temp=graph->G[Si].FirstEdge;
        }else
        {
            temp=findLastedge(graph->G[Si].FirstEdge);
        }

        temp->AdjV=Sj;
        temp->weighted=Tij;
        temp->Next=graph->G[Sj].FirstEdge;
    }
    return graph;
}
edge findLastedge(edge a)
{
    while(a->Next)a=a->Next;
    return a;
}