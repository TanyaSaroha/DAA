#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
typedef struct node
{
	int vno,lower,*rcm,level;
	struct node *parent;
}node;

typedef struct qnode
{
	node *addr;
	struct qnode *next;
}qnode;
void printmat(int *graph,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(graph[i*n+j]!=INT_MAX)
			{
				printf("%d ",graph[i*n+j]);
			}
			else
			{
				printf("~ ");
			}
		}
		printf("\n");
	}
}

void printlist(qnode *head)
{
	qnode *temp=head;
	while(temp->next!=NULL)
	{
		printf("%d->",temp->addr->lower);
		temp=temp->next;
	}
	if(temp!=NULL)
	{
		printf("%d",temp->addr->lower);
	}
	printf("\n");
}
void printnode(node *nd,int n,int cost)
{
	printf("Vertex Number - %d\n",nd->vno+1);
	printf("Level         - %d\n",nd->level);
	if(nd->parent==NULL)
	{
		printf("Lower         - enode->lower + enode->rcm[enode->vno*n+i] + lower\n");
		printf("              - %d + %d + %d\n",0,0,cost);
		printf("              - %d\n",nd->lower);
	}
	else
	{
		printf("Lower         - enode->lower + enode->rcm[enode->vno*n+i] + lower\n");
		printf("              - %d + %d + %d\n",nd->parent->lower,nd->parent->rcm[nd->parent->vno*n+nd->vno],cost);
		printf("              - %d\n",nd->lower);	
	}
	printf("RCM\n");
	printmat(nd->rcm,n);
	printf("\n");
}

void path(node *ans,int n)
{
	int x[n+1];
	int i=0;
	while(ans->parent!=NULL)
	{
		x[i++]=ans->vno+1;
		ans=ans->parent;
	}
	x[i]=ans->vno+1;
	for(;i>=0;i--)
	{
		printf("%d->",x[i]);
	}
	printf("%d\n",1);
}
void input(int *graph,int n)
{
	int src,dest,ch,wt;
	int i,j;

	printf("Do you want to enter an edge?\nPress 1 for yes 2 for no\n");
	scanf("%d",&ch);
	while(ch==1)
	{
		printf("Enter the source vertex - ");
		scanf("%d",&src);
		if(src>0 && src<=n)
		{
			printf("Enter the destination vertex - ");
			scanf("%d",&dest);
			if(dest>0 && dest<=n)
			{
				if(graph[(src-1)*n+dest-1]!=INT_MAX)
				{
					printf("Error!!! Duplicate Edge...\n");
				}
				else
				{
					printf("Enter the weight of the edge - ");
					scanf("%d",&wt);
					if(wt>=0)
					{
						graph[(src-1)*n+dest-1]=wt;	
					}
					else
					{
						printf("Error!!! Invalid Edge...\n");
					}	
				}
			}
			else
			{
				printf("Error!!! Invalid Destination Vertex...\n");
			}
		}
		else
		{
			printf("Error!!! Invalid Source Vertex...\n");
		}
		printf("Do you want to enter an edge?\nPress 1 for yes 2 for no\n");
		scanf("%d",&ch);
	}
}

void enqueue(qnode **head,node *newnode)
{
	qnode *newqnode=(qnode *)malloc(sizeof(qnode));
	newqnode->addr=newnode;
	newqnode->next=NULL;
	if(*head==NULL)	
	{
		*head=newqnode;	
	}
	else
	{
		qnode *temp;
		temp=*head;
		if(newnode->lower<temp->addr->lower)
		{
			newqnode->next=temp;
			temp=newqnode;
			*head=temp;
		}
		else
		{
			while(temp->next!=NULL && temp->next->addr->lower<=newnode->lower)	
			{
				temp=temp->next;	
			}
			newqnode->next=temp->next;
			temp->next=newqnode;
		}
	}
}

void enqueuedead(qnode **head,node *newnode)
{
	qnode *newqnode=(qnode *)malloc(sizeof(qnode));
	newqnode->addr=newnode;
	newqnode->next=*head;
	*head=newqnode;
}

node *dequeue(qnode **head)
{
	node *newnode;
	newnode=(*head)->addr;
	qnode *temp;
	temp=*head;
	*head=(*head)->next;
	free(temp);
	return newnode;
}
void copy(int *out,int *in,int n)
{
	int i,j;
	for(i=0;i<n;i++)	
	{
		for(j=0;j<n;j++)
		{
			in[i*n+j]=out[i*n+j];
		}
	}
}
int rcm(int *g,int n)
{
	int min,c=0,i,j;
	
	for(i=0;i<n;i++)
	{
		min=INT_MAX;
		for(j=0;j<n;j++)
		{
			if(g[i*n+j]!=INT_MAX && g[i*n+j]<min)	
			{
				min=g[i*n+j];
			}
		}
		if(min!=INT_MAX && min!=0)
		{
			c+=min;
			for(j=0;j<n;j++)
			{
				if(g[i*n+j]!=INT_MAX)
				{
					g[i*n+j]-=min;
				}
			}
		}
	}
	
	for(i=0;i<n;i++)
	{
		min=INT_MAX;
		for(j=0;j<n;j++)
		{
			if(g[j*n+i]!=INT_MAX && g[j*n+i]<min)	
			{
				min=g[j*n+i];
			}
		}
		if(min!=INT_MAX && min!=0)
		{
			c+=min;
			for(j=0;j<n;j++)
			{
				if(g[j*n+i]!=INT_MAX)
				{
					g[j*n+i]-=min;
				}
			}
		}
	}
	return c;
}

int empty(qnode *head)
{
	if(head==NULL)
	{
		return 1;
	}

	return 0;	
}
void tsp(int *g,int n)
{
	int upper=INT_MAX,i,j;
	qnode *livenode=NULL,*deadnode=NULL;
	
	node *newnode,*enode,*ansn=NULL;
	newnode=(node *)malloc(sizeof(node));
	
	newnode->level=1;
	newnode->parent=NULL;
	newnode->vno=0;
	
	int *r=malloc(n*n*sizeof(int));
	copy(g,r,n);
	int cost=rcm(r,n);
	newnode->lower=cost;
	newnode->rcm=r;
	
	enqueue(&livenode,newnode);
	printnode(newnode,n,cost);
	
	while(!empty(livenode))
	{
		printf("List of Live nodes\n");
		printlist(livenode);
		enode=dequeue(&livenode);
		if(enode->lower<=upper)
		{
			for(i=0;i<n;i++)	
			{
				if(enode->rcm[enode->vno*n+i]!=INT_MAX)
				{
					newnode=(node *)malloc(sizeof(node));
					r=(int *)malloc(n*n*sizeof(int));
					copy(enode->rcm,r,n);
					for(j=0;j<n;j++)
					{
						r[enode->vno*n+j]=INT_MAX;
						r[j*n+i]=INT_MAX;
					}
					r[i*n]=INT_MAX;
					cost=rcm(r,n);
					newnode->parent=enode;
					newnode->level=enode->level+1;
					newnode->lower=enode->lower+enode->rcm[enode->vno*n+i]+cost;
					newnode->rcm=r;
					newnode->vno=i;
					
					printnode(newnode,n,cost);
					if(newnode->level==n)
					{
						if(newnode->lower<upper && g[newnode->vno*n]!=INT_MAX)
						{
							if(ansn!=NULL)
							{
								free(ansn->rcm);
								free(ansn);
							}
							printf("Upper changed from %d to %d\n",upper,newnode->lower);
							upper=newnode->lower;
							ansn=newnode;
						}
						else
						{
							free(newnode->rcm);
							free(newnode);
						}
					}
					else
					{
						enqueue(&livenode,newnode);
					}
				}
			}
			enqueuedead(&deadnode,enode);
		}
	}
	if(ansn!=NULL)
	{
		printf("Path\n");
		path(ansn,n);
		free(ansn->rcm);
		free(ansn);
	}
	else
	{
		printf("No Solution Exist\n");
	}
	
	printf("Deadnodes are\n");
	while(!empty(deadnode))
	{
		newnode=dequeue(&deadnode);
		printf("%d ",newnode->lower);
		free(newnode);
	}
	printf("\n");
}
int main()
{
	int ch,i,n,j;
	int *graph=NULL;
	do
	{
		printf("Press\n1 for input graph\n2 for TSP solution by LCBB\n3 for exit\n");
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1:
				printf("Enter no. of vertices - ");
				scanf("%d",&n);
				if(graph!=NULL)
				{
					free(graph);
				}
				graph=malloc(n*n*sizeof(int));
				for(i=0;i<n;i++)
				{
					for(j=0;j<n;j++)
					{
						graph[i*n+j]=INT_MAX;
					}
				}
				input(graph,n);
				printmat(graph,n);
				break;
				
			case 2:
				tsp(graph,n);
				break;
				
		}
	}while(ch!=3);
}
