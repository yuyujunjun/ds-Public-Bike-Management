#include <stdio.h>
#include<stdlib.h>
#define MaxVNodeNum 500
#define INFINITY 100000
typedef struct AdjVNode *edge;
typedef int Vertex;
struct MinPath{
    int sent;
    int back;
    int path[MaxVNodeNum];
};
typedef struct Vnode{
    int number;
    int known;
    int dist;
    int path[MaxVNodeNum];
    int pathIndex;
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
void ShortestDist( LGraph graph );
void Print(LGraph graph);
int main() {
    int Sp;
    LGraph graph=create(&Sp);
    ShortestDist(graph);
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
    graph->G[0].dist=0;
    for(i=1;i<=graph->Nv;i++)
    {
        scanf("%d",&graph->G[i].number);
        graph->G[i].FirstEdge=NULL;
        graph->G[i].known=0;
        graph->G[i].dist=INFINITY;
        for(int j=0;j<graph->Nv;j++)graph->G[i].path[j]=-1;
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
void ShortestDist( LGraph graph )
{
    int i;
    while(1)
    {
        int MinDist=INFINITY-1;
        int index;
        int flag=0;
        for(i=0;i<graph->Nv;i++)
        {
            if(graph->G[i].dist<MinDist&&graph->G[i].known==0)
            {
                MinDist=graph->G[i].dist;
                index=i;
                flag=1;
            }
        }
        if(flag==0)break;
        graph->G[index].known=1;
        edge temp=graph->G[index].FirstEdge;
        for(;temp;temp=temp->Next)
        {
            if(!(graph->G[temp->AdjV].known))
            {
                if(graph->G[index].dist+temp->weighted<graph->G[temp->AdjV].dist)
                {
                    graph->G[temp->AdjV].dist=graph->G[index].dist+temp->weighted;
                    graph->G[temp->AdjV].pathIndex=0;
                }else if(graph->G[index].dist+temp->weighted==graph->G[temp->AdjV].dist)
                {
                    graph->G[temp->AdjV].pathIndex++;

                }
                graph->G[temp->AdjV].path[graph->G[temp->AdjV].pathIndex]=index;
            }
        }
    }
}