#include <stdio.h>
#include<stdlib.h>
#define MaxVNodeNum 501
#define INFINITY 100000
int Gsent=INFINITY;//定义最优的sent的初始值，不影响后续判断
int Gback=INFINITY;
typedef struct AdjVNode *edge;//声明边
typedef int Vertex;
//Vnode为图上的结点，量均可以表现结点的性质
typedef struct Vnode{
    int number;//为Vnode结点上车的数量
    int known;//用于djk算法的已知判断
    int dist;//djk算法的距离判断
    int path[MaxVNodeNum];//指向它的结点
    int pathIndex;//存在多条最短路径指向它时，利用pathIndex进行分辨
   // int count;//并无卵用
    edge FirstEdge;//它的第一条边
}*AdjList;
//声明与边相关的结构
struct AdjVNode{
    Vertex AdjV;//此为当前边所指的结点的边号
    int weighted;//此为经过当前边的所用时间
    edge Next;//结点的下一条边
};


typedef struct GNode *PtrToGNode;//声明图
struct GNode{
    int Nv;//图中的结点数
    int Ne;//图中的边数
    int Cmax;//最大车容量数，因为是整个图的性质，故放此处
    AdjList G;
};

typedef PtrToGNode LGraph;
LGraph create(int *Sp);//同时创建图和向用户获得有缺陷的自行车站点
void ShortestDist( LGraph graph );//利用djk算法获取图的最短路径
void Print(LGraph graph);
void Dfs(LGraph graph,int Gpath[],int path[],int sent ,int back,int id);//深度优先算法遍历每一条最优路径
int main() {
    int Sp;//为有缺陷的站点的编号
    LGraph graph=create(&Sp);//创建图
    ShortestDist(graph);//获取图的最短路径
    int Gpath[MaxVNodeNum];//定义考虑了sent、back的最优路径
    int path[MaxVNodeNum];//深度优先搜索遍历时的当前路径
    for(int i=0;i<graph->Nv+1;i++)//将路径上的位置都置为-1，以作区分，因为真正的站点编号均大于等于0
	{
		Gpath[i]=-1;
        path[i]=-1;
	}
	Dfs(graph,Gpath,path,0,0,Sp) ;//深度优先搜索计算获取最优路径和最优sent和back，初始状态不需要sent，back，所以sent=back=0
    int i;
	for(i=0;Gpath[i]!=-1;i++);//因为结点路径储存的都是上一个节点，所以需要先找到路径中最后位置的结点
    printf("%d ",Gsent);//打印最优sent
    printf("0");//此为初始节点，单独列出
    for(i--;i>=0;i--)
    	printf("->%d",Gpath[i]);//打印除了初始节点以外的其余结点
    printf(" %d",Gback);//打印最优back
   //Print(graph);
    return 0;
}
//创建图的函数
LGraph create(int *Sp)
{
    LGraph  graph;
    graph=(LGraph)malloc(sizeof(struct GNode));//利用动态分配内存给图的第一层结构分配空间
    scanf("%d%d%d%d",&graph->Cmax,&graph->Nv,Sp,&graph->Ne);
    graph->G=(AdjList)malloc((graph->Nv+1)*sizeof(struct Vnode));//利用动态分配内存给图的结点数组分配空间
    int i;
    //-------------初始化动态分配的结点----------------
    graph->G[0].FirstEdge=NULL;//单独初始化第一个结点，因为第一个节点没有从缓存区获取信息
    graph->G[0].number=INFINITY;
    graph->G[0].known=0;
    graph->G[0].dist=0;//让第一个节点的dist为0
    for(int j=0;j<graph->Nv+1;j++)graph->G[0].path[j]=-1;

    for(i=1;i<=graph->Nv;i++)//初始化后续结点
    {
        scanf("%d",&graph->G[i].number);//从缓存区获取该节点当前的车辆数
        graph->G[i].FirstEdge=NULL;
        graph->G[i].known=0;
        graph->G[i].dist=INFINITY;//令后续的结点的dist为无限
       // graph->G[i].count=0;
        for(int j=0;j<graph->Nv+1;j++)graph->G[i].path[j]=-1;
    }
    //-----------处理每一个结点的邻接信息------------
    for(i=1;i<=graph->Ne;i++)//对结点进行遍历
    {
        edge temp;
        int Si,Sj,Tij;//Si为源结点，Sj为目标结点，Tij为两者之前路线所用时间
        scanf("%d%d%d",&Si,&Sj,&Tij);
        temp=(edge)malloc(sizeof(struct AdjVNode));//使用动态分配内存先将边的信息储存在临时变量中，因为表示边的变量并不唯一
        temp->Next=NULL;//获取此边时下一条边还没有
        temp->AdjV=Sj;
        temp->weighted=Tij;
        if(graph->G[Si].FirstEdge==NULL)//如果还没有第一条边，则temp为第一条边
        {
            graph->G[Si].FirstEdge=temp;
        }else                           //如果已经存在第一条边，获取最新的没有存在的边
        {
            edge t=graph->G[Si].FirstEdge;//先将第一条边用临时变量储存起来以待遍历
            while(t->Next)t=t->Next;//保留t->Next是为了避免将边赋给一个无效的变量
            t->Next=temp;
        }
        temp=(edge)malloc(sizeof(struct AdjVNode));//因为I、J两个站点是互相联通的，同样需要为j赋值
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
void ShortestDist( LGraph graph)//利用算法获取最优边
{
    int i;
    //int count[MaxVNodeNum];
    while (1) {
        int MinDist = INFINITY - 1;//初始化最优的距离为初始dist-1
        int index = 0;
        int flag = 0;//用以判断是否还存在结点没有确定下来
        for (i = 0; i < graph->Nv+1; i++)//找到没有确定下来的结点中距离最小的一个
        {
            //count[i]=0;
            if (graph->G[i].dist < MinDist && graph->G[i].known == 0) {
                MinDist = graph->G[i].dist;
                index = i;
                flag = 1;
            }
        }
        if (flag == 0)break;//如果所有联通节点都已确定下来，退出循环

        graph->G[index].known = 1;//表示该结点已经被确定下来
        edge temp = graph->G[index].FirstEdge;
        for (; temp; temp = temp->Next)//遍历该节点的每一条边
        {
            if (!(graph->G[temp->AdjV].known))//如果该边所对的结点未被确定，继续操作
            {
                if (graph->G[index].dist + temp->weighted <
                    graph->G[temp->AdjV].dist)//如果通过该结点，该边对应的结点距离可以变小，则使用这个距离作为那个结点的最新距离
                {
                    graph->G[temp->AdjV].dist = graph->G[index].dist + temp->weighted;
                    graph->G[temp->AdjV].pathIndex = 0;//如果已经重新确定了最新距离，则它的最短路径应该重新规划
                    for (int j = 0; j < graph->Nv+1; j++)graph->G[temp->AdjV].path[j] = -1;//重新规划最短路径
                    //graph->G[temp->AdjV].count=graph->G[index].count;
                    //count[temp->AdjV]=count[index];
                    graph->G[temp->AdjV].path[graph->G[temp->AdjV].pathIndex] = index;//填入最短路径
                } else if (graph->G[index].dist + temp->weighted == graph->G[temp->AdjV].dist)
                {
                    graph->G[temp->AdjV].pathIndex++;//如果有多条相同的最短路径，则需要填入另外的空间中
                    // graph->G[temp->AdjV].count+=graph->G[index].count;
                    //count[temp->AdjV]+=count[index];
                    graph->G[temp->AdjV].path[graph->G[temp->AdjV].pathIndex] = index;//填入最短路径
                }


        }
    }
}
   // return count[Sp];
}
void Dfs(LGraph graph,int *Gpath,int *path,int sent,int back,int id)//dfs算法，传入变量为已经处理好最短路径的图，最优路径、当前路径，当前路径的sent和back，以及当前节点的编号
{
	static int even=graph->Cmax/2;//获取perfect值
	static int PathIndex=0;//管理路径数组的index
    static int visited[MaxVNodeNum]={0};//判断是否已经经过当前节点
	if(id!=0&&visited[id]!=1)//如果该节点还没有被经过且不是头节点，则证明需要向该节点遍历
	{
        visited[id]=1;//现在经过了该节点，标记它
		path[PathIndex++]=id;//将该节点添加进路径
		if(graph->G[id].number<=even)//如果该节点的车比平均值小的话，应该添加给sent，表示需要sent跟多的车
		{
			sent=sent+even-graph->G[id].number;
		}else
		{
			back=back+graph->G[id].number-even;//如果比平均值大，则应该考虑运回去
			if(sent > 0)//在sent不为0的情况下，back可以先将自己的车运到需要车的站点去
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

		for(int i=0;visited[graph->G[id].path[i]]==0&&graph->G[id].path[i]!=-1;i++)//依次遍历该节点所对应的所有路径
		{
			Dfs(graph,Gpath,path,sent,back,graph->G[id].path[i]);//深度优先算法，继续下一个位置的节点
		}
        visited[id]=0;//递归回来后，需要重置当前经历的状态，以保证其他路径不会错过此节点
        PathIndex--;//往回走一个节点，路径的index也应该减小1
        path[PathIndex]=-1;//重置当前路径
	}else if(id==0)//当遇到头节点时
	{
		if(sent<Gsent){//如果此路的sent优于最优sent，则将此路作为最优路径
			for(int i=0;path[i]!=-1;i++)Gpath[i]=path[i];
			Gsent=sent;
			Gback=back;
		}else if(sent==Gsent&&back<Gback)//如果此路sent与最优sent相同且back优于最优back，则此路为最优
		{
			for(int i=0;path[i]!=-1;i++)Gpath[i]=path[i];
			Gsent=sent;
			Gback=back;
		}
	}
}
