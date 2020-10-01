#include<iostream>
#include<string.h>
using namespace std;

#define MVNum 100//����Χ��ֵ 
#define INFINITE 32767//����� 
#define OK 1
#define ERROR 0

typedef string VerTexType;
typedef int ArcType;
typedef int Status;

bool visited[MVNum];//////////////

//   �ڽӾ���
typedef struct
{
	VerTexType vexs[MVNum];
	ArcType arcs[MVNum][MVNum];
	int vexnum;//���� 
	int arcnum;//�� 
}AMGraph;
//��С������
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
	cout<<"���붥�����:";
	cin>>G.vexnum;
	cout<<"����ߵĸ���:";
	cin>>G.arcnum;
	cout<<"���붥����Ϣ:";
	for(i=0;i<G.vexnum;i++)
		cin>>G.vexs[i];
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
			G.arcs[i][j]=INFINITE;
	cout<<"�����ڽӾ�����������λ��i,j��Ȩ��w:"<<endl;
	for(k=0;k<G.arcnum;k++)
	{
		cin>>i>>j>>w;
		G.arcs[i][j]=w;
		G.arcs[j][i]=w;
	}
	return OK;
}

void DFS(AMGraph G,int v)//����������� 
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
//����------------------------------------------------------------------ 
typedef string QElemType;

typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;                  //���

typedef struct
{
	QueuePtr front;  //ָ�� 
	QueuePtr rear;
}LinkQueue;  

Status InitQueue(LinkQueue &Q);
bool QueueEmpty(LinkQueue Q);
Status EnQueue (LinkQueue&Q, QElemType e);
Status DeQueue (LinkQueue &Q, QElemType &e);

Status InitQueue(LinkQueue &Q)
{
	//��ʼ��һ��ֻ��ͷ���Ŀն�
	Q.front=Q.rear=new QNode;
	if(!Q.front)
	{
		cout<<"��ʼ��ʧ��"<<endl;
		return ERROR;
	}
	//����front��rear
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
	//�����½��s
	QNode *s=new QNode;
	//��s���뵽Q.rear��
	s->data=e;
	s->next=NULL;
	Q.rear->next=s;
	//�޸�Q.rear
	Q.rear=s;
	return OK;
}
//����
Status DeQueue (LinkQueue &Q, QElemType &e)
{
	// �ж������Ƿ�Ϊ��
	if(Q.rear==Q.front)
		return ERROR; 
	//ɾ�������е���Ԫ���p
	QNode *p=Q.front->next;
	Q.front->next=p->next;
	e=p->data; 
	//���ɾ������һ���ն�(p==Q.rear)������Ҫ�޸�Q.rear
	if(Q.rear==p)
		Q.rear=Q.front;
	delete p;
	return OK;
}
//���� ------------------------------------------------------------------- 

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
	int mincost;//��СȨ
	int index;//��СȨ�±�����
	int k;//������СȨԪ���±�
	VerTexType elem;//���Ԫ��
	cout<<u<<" ";
	k=LocateVex(G,u);
	closedge[k].lowcost=0;
	for(int i=0;i<G.vexnum;i++)//�������ÿ�����Prim�㷨ԭ�� 
		if(i!=k)
		{
			closedge[i].adjext=u;
			closedge[i].lowcost=G.arcs[k][i];
		}
	for(int i=1;i<G.vexnum;i++)
	{
		mincost=INFINITE;
		for(int j=0;j<G.vexnum;j++)//Ѱ����СȨ 
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
		closedge[index].lowcost=0;//ע���0 
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
	cout<<"�������!"<<endl;
	cout<<"DFS�����������:";
	DFSTraverse(G);
	cout<<"BFS�����������:";
	BFSTraverse(G);
	cout<<"Prim��С������:";
	cout<<"�������:";
	cin>>u;
	cout<<"�����յ�:";
	cin>>z;
	MinnSpanTree_Prim(G,u,Sumcost,z);
	cout<<"Ȩ����С��:"<<Sumcost<<endl;
	return 0;
	
} 
/*           �ڽӱ����� 
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
 
