#include<iostream>
#include<string.h>
using namespace std;

#define MVNum 100//矩阵范围最值 
#define INFINITE 32767//无穷大 
#define OK 1
#define ERROR 0

typedef string VerTexType;
typedef int ArcType;
typedef int Status;

bool visited[MVNum];//////////////

//   邻接矩阵
typedef struct
{
	VerTexType vexs[MVNum];
	ArcType arcs[MVNum][MVNum];
	int vexnum;//顶点 
	int arcnum;//边 
}AMGraph;
//最小生成树
struct closedge
{
	VerTexType adjext;
	ArcType lowcost;
}closedge[MVNum]; 

Status CreateUDN(AMGraph &G);
void DFS(AMGraph G,int v);
void DFSTraverse(AMGraph G);
void BFS(AMGraph G,int v);
void BFSTraverse(AMGraph G);
Status LocateVex(AMGraph G,VerTexType u);
void MinnSpanTree_Prim(AMGraph G,VerTexType u,int &Sumcost);

 
Status CreateUDN(AMGraph &G)
{
	int i,j,k,w;
	cout<<"输入顶点个数:";
	cin>>G.vexnum;
	cout<<"输入边的个数:";
	cin>>G.arcnum;
	cout<<"输入顶点信息:";
	for(i=0;i<G.vexnum;i++)
		cin>>G.vexs[i];
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
			G.arcs[i][j]=INFINITE;
	cout<<"依据邻接矩阵依次输入位置i,j和权重w:"<<endl;
	for(k=0;k<G.arcnum;k++)
	{
		cin>>i>>j>>w;
		G.arcs[i][j]=w;
		G.arcs[j][i]=w;
	}
	return OK;
}

void DFS(AMGraph G,int v)//深度优先搜索 
{
	cout<<G.vexs[v]<<" ";
	visited[v]=true;
	for(int w=0;w<G.vexnum;w++)
	{
		if(G.arcs[v][w]!=INFINITE&&visited[w]!=true)
			DFS(G,w);
	}
}

void DFSTraverse(AMGraph G)
{
	for(int v=0;v<G.vexnum;v++)
		visited[v]=false;
	for(int v=0;v<G.vexnum;v++)
		if(!visited[v])
			DFS(G,v);
	cout<<endl;
}
//队列------------------------------------------------------------------ 
typedef string QElemType;

typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;                  //结点

typedef struct
{
	QueuePtr front;  //指针 
	QueuePtr rear;
}LinkQueue;  

Status InitQueue(LinkQueue &Q);
bool QueueEmpty(LinkQueue Q);
Status EnQueue (LinkQueue&Q, QElemType e);
Status DeQueue (LinkQueue &Q, QElemType &e);

Status InitQueue(LinkQueue &Q)
{
	//初始化一个只有头结点的空队
	Q.front=Q.rear=new QNode;
	if(!Q.front)
	{
		cout<<"初始化失败"<<endl;
		return ERROR;
	}
	//设置front和rear
	Q.front->next=NULL;
	return OK;
}

bool QueueEmpty(LinkQueue Q)
{
	if(Q.front==Q.rear)
		return true;
	return false;
}

Status EnQueue (LinkQueue&Q, QElemType e)
{
	//生成新结点s
	QNode *s=new QNode;
	//将s插入到Q.rear后
	s->data=e;
	s->next=NULL;
	Q.rear->next=s;
	//修改Q.rear
	Q.rear=s;
	return OK;
}
//出队
Status DeQueue (LinkQueue &Q, QElemType &e)
{
	// 判断链队是否为空
	if(Q.rear==Q.front)
		return ERROR; 
	//删除链队中的首元结点p
	QNode *p=Q.front->next;
	Q.front->next=p->next;
	e=p->data; 
	//如果删除后变成一个空队(p==Q.rear)，还需要修改Q.rear
	if(Q.rear==p)
		Q.rear=Q.front;
	delete p;
	return OK;
}
//队列 ------------------------------------------------------------------- 

void BFS(AMGraph G,int v)
{
	cout<<G.vexs[v]<<" ";
	visited[v]=true;
	QElemType e;
	LinkQueue Q;
	InitQueue(Q);
	EnQueue(Q,G.vexs[v]);
	while(!QueueEmpty(Q))
	{
		DeQueue(Q,e);
		for(int w=0;w<G.vexnum;w++)
			if(G.arcs[v][w]!=INFINITE&&visited[w]==false)
			{
				cout<<G.vexs[w]<<" ";
				visited[w]=true;
				EnQueue(Q,G.vexs[w]);
			}
	}
}

void BFSTraverse(AMGraph G)
{
	for(int v=0;v<G.vexnum;v++)
		visited[v]=false;
	for(int v=0;v<G.vexnum;v++)
		if(!visited[v])
			BFS(G,v);
	cout<<endl;
}

Status LocateVex(AMGraph G,VerTexType u)
{
	for(int v=0;v<G.vexnum;v++)
		if(G.vexs[v]==u)
			return v;	
	return 	-1;
}

void MinnSpanTree_Prim(AMGraph G,VerTexType u,int &Sumcost,VerTexType z)
{
	int mincost;//最小权
	int index;//最小权下标索引
	int k;//搜索最小权元素下标
	VerTexType elem;//输出元素
	cout<<u<<" ";
	k=LocateVex(G,u);
	closedge[k].lowcost=0;
	for(int i=0;i<G.vexnum;i++)//具体作用看书中Prim算法原理 
		if(i!=k)
		{
			closedge[i].adjext=u;
			closedge[i].lowcost=G.arcs[k][i];
		}
	for(int i=1;i<G.vexnum;i++)
	{
		mincost=INFINITE;
		for(int j=0;j<G.vexnum;j++)//寻找最小权 
		{
			if(closedge[j].lowcost!=0&&closedge[j].lowcost<mincost)
			{
				index=j;
				mincost=closedge[j].lowcost;
			}
		}
		elem=G.vexs[index];
		cout<<elem<<" ";
		if(elem==z)
			return ;
		Sumcost+=mincost;
		closedge[index].lowcost=0;//注意归0 
		for(int j=0;j<G.vexnum;j++)
		{
			if(G.arcs[index][j]<closedge[j].lowcost)
			{
				closedge[j].lowcost=G.arcs[index][j];
				closedge[j].adjext=G.vexs[j];
			}
		}
	}
	cout<<endl;
}

int main()
{
	AMGraph G;
	VerTexType u;
	VerTexType z;
	int Sumcost;
	CreateUDN(G);
	cout<<"创建完毕!"<<endl;
	cout<<"DFS优先搜索结果:";
	DFSTraverse(G);
	cout<<"BFS优先搜索结果:";
	BFSTraverse(G);
	cout<<"Prim最小生成树:";
	cout<<"输入起点:";
	cin>>u;
	cout<<"输入终点:";
	cin>>z;
	MinnSpanTree_Prim(G,u,Sumcost,z);
	cout<<"权重最小和:"<<Sumcost<<endl;
	return 0;
	
} 
/*           邻接表！！！ 
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	OtherInfo info;
}ArcNode;

typedef struct VNode
{
	VerTexType data;
	ArcNode *firstarc;
}VNode,AdjList[MVNum];

typedef struct
{
	AdjList vertices;
	int vexnum;
	int arcnum;
}ALGraph;
*/
/*
0 1 10
0 2 20
0 3 25
1 4 15
1 5 45
1 6 30
2 5 40
2 6 50
3 6 35
4 5 35
5 6 10
*/
 
