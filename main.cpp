#include <stdio.h>
#include<stdlib.h>
#define MaxVNodeNum 501
#define INFINITY 100000
int Gsent=INFINITY;
int Gback=INFINITY;
typedef struct AdjVNode *edge;
typedef int Vertex;
typedef struct Vnode{
    int number;
    int known;
    int dist;
    int path[MaxVNodeNum];
    int pathIndex;
    int count;
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
void ShortestDist( LGraph graph ,int Sp);
void Print(LGraph graph);
int *Dfs(LGraph graph,int Gpath[],int path[],int sent ,int back,int id);
int main() {
    int Sp;
    LGraph graph=create(&Sp);
    ShortestDist(graph,Sp);
    int Gpath[MaxVNodeNum];
    int path[MaxVNodeNum];
    for(int i=0;i<graph->Nv+1;i++)
	{
		Gpath[i]=-1;
        path[i]=-1;
	}
	Dfs(graph,Gpath,path,0,0,Sp) ;
    int i;
	for(i=0;Gpath[i]!=-1;i++);
    printf("%d ",Gsent);
    printf("0");
    for(i--;i>=0;i--)
	printf("->%d",Gpath[i]);
    printf(" %d",Gback);
   // Print(graph);
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
        graph->G[i].count=0;
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
void ShortestDist( LGraph graph ,int Sp)
{
    int i;
    //int count[MaxVNodeNum];
    while(1)
    {
        int MinDist=INFINITY-1;
        int index;
        int flag=0;
        for(i=0;i<graph->Nv;i++)
        {
            //count[i]=0;
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
                    graph->G[temp->AdjV].count=graph->G[index].count;
                    //count[temp->AdjV]=count[index];
                }else if(graph->G[index].dist+temp->weighted==graph->G[temp->AdjV].dist)
                {
                    graph->G[temp->AdjV].pathIndex++;
                    graph->G[temp->AdjV].count+=graph->G[index].count;
                    //count[temp->AdjV]+=count[index];
                }
                graph->G[temp->AdjV].path[graph->G[temp->AdjV].pathIndex]=index;
            }
        }
    }
   // return count[Sp];
}
int* Dfs(LGraph graph,int *Gpath,int *path,int sent,int back,int id)
{

	static int even=graph->Cmax/2;
	static int PathIndex=0;
    static int visited[MaxVNodeNum]={0};
	if(id!=0)
	{
        visited[id]=1;
		path[PathIndex++]=id;
		if(graph->G[id].number<=even)
		{
			sent=sent+even-graph->G[id].number;
		}else
		{
			back=back+graph->G[id].number-even;
			if(sent > 0)
			{
				if(back>sent)
				{
					back-=sent;
					sent=0;
				}else
				{
					sent-=back;
					back=0;
				}
			}
		}
		for(int i=0;visited[graph->G[id].path[i]]==0&&graph->G[id].path[i]!=-1;i++)
		{
			Dfs(graph,Gpath,path,sent,back,graph->G[id].path[i]);

		}
        visited[id]=0;
        PathIndex--;
        path[PathIndex]=-1;
	}else
	{
		if(sent<Gsent){
			for(int i=0;path[i]!=-1;i++)Gpath[i]=path[i];
			Gsent=sent;
			Gback=back;
		}else if(sent==Gsent&&back<Gback)
		{
			for(int i=0;path[i]!=-1;i++)Gpath[i]=path[i];
			Gsent=sent;
			Gback=back;
		}
	}
}
