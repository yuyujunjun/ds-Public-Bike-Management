#include <stdio.h>
#include<stdlib.h>
typedef struct AdjVNode *edge;
typedef int Vertex;
struct AdjVNode{
    Vertex AdjV;
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
    }
    return graph;
}
