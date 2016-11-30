#include <stdio.h>
#include<stdlib.h>
typedef struct AdjVNode *edge;
typedef int Vertex;
typedef struct Vnode{
    int number;
    int known;
    edge FirstEdge;
}*AdjList;
struct AdjVNode{
    Vertex AdjV;
    int weighted;
    edge Next;
};


typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;
    int Ne;
    int Cmax;
    AdjList G;
};
typedef PtrToGNode LGraph;
LGraph create(int *Sp);
void Print(LGraph graph);
int main() {
    int Sp;
    LGraph graph=create(&Sp);
    Print(graph);
    return 0;
}
LGraph create(int *Sp)
{
    LGraph  graph;
    graph=(LGraph)malloc(sizeof(struct GNode));

    scanf("%d%d%d%d",&graph->Cmax,&graph->Nv,Sp,&graph->Ne);
    graph->G=(AdjList)malloc((graph->Nv+1)*sizeof(struct Vnode));
    int i;
    graph->G[0].FirstEdge=NULL;
    graph->G[0].number=1000;
    graph->G[0].known=0;
    for(i=1;i<=graph->Nv;i++)
    {
        scanf("%d",&graph->G[i].number);
        graph->G[i].FirstEdge=NULL;
        graph->G[i].known=0;
    }
    for(i=0;i<graph->Ne;i++)
    {
        edge temp;
        int Si,Sj,Tij;
        scanf("%d%d%d",&Si,&Sj,&Tij);
        temp=(edge)malloc(sizeof(struct AdjVNode));
        temp->Next=NULL;
        temp->AdjV=Sj;
        temp->weighted=Tij;
        if(graph->G[Si].FirstEdge==NULL)
        {
            graph->G[Si].FirstEdge=temp;
        }else
        {
            edge t=graph->G[Si].FirstEdge;
            while(t->Next)t=t->Next;
            t->Next=temp;
        }
        temp=(edge)malloc(sizeof(struct AdjVNode));
        temp->Next=NULL;
        temp->AdjV=Si;
        temp->weighted=Tij;
        if(graph->G[Sj].FirstEdge==NULL)
        {
            graph->G[Sj].FirstEdge=temp;
        }else
        {
            edge t=graph->G[Sj].FirstEdge;
            while(t->Next)t=t->Next;
            t->Next=temp;
        }

    }
    return graph;
}

void Print(LGraph graph)
{

    int i;
    for(i=0;i<=graph->Nv;i++)
    {
        edge temp=graph->G[i].FirstEdge;
        printf("numberof bike:%d\n",graph->G[i].number);
        while(temp)
        {
            printf("next edge:%d,time:%d \n",temp->AdjV,temp->weighted);
            temp=temp->Next;
        }
    }
}