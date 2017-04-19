#include <stdio.h>
#include <stdlib.h>

void input(int adj[],int n)
{
	int i ,j ,k,src,des;
	while(1)
	{
		printf("\n Enter the Edges if not press 0 to exit else enter 1 = ");
		scanf("%d",&k);
		if(k == 0)
			break;
		printf("\nEnter the Source = ");
		scanf("%d",&src);
		printf("\nEnter the Destination = ");
		scanf("%d",&des);
		if((src < 1 || src > n) || (des < 1 || des > n) )
			printf("\nInvalid Connection\n");
		else
		{
			if( adj[ (src-1)*n + des- 1 ] == 1 )
				printf("\nAlready Exist\n");
			else
				adj[ (src-1)*n + des- 1 ] = 1;
 		}
	}
}

void display(int adj[],int n)
{
	int i ,j ;
	for(i = 0 ; i < n ; i++)
	{
		for(j = 0 ; j < n ; j++)
		{
			printf("%d ",adj[i*n + j]);
		}
		printf("\n");
	}
}

/*void nextval(int adj[],int x[],int k,int n)
{
	int i;
	while(1)
	{
		x[k]++;
		if(x[k] == n)
		{
			x[k] = -1;
			return;
		}
		if(adj[x[k-1]*n + x[k]])
		{
			for(i = 1 ; i < k ; i++)
				if(x[i] == x[k]) 
					break;
			if(i == k)
			{
				if((k < n-1) || ( (k == n-1) && adj[ x[k]*n + x[0] ]) )
					return;
			}
		}
	}
}*/

void nextval(int *adj,int *x,int k,int n)
{
	int i;
	while(1)
	{
		x[k]++;
		if(x[k]==n)
		{
			return;
		}
		if(adj[x[k-1]*n+x[k]]==1)
		{
			for(i=0;i<k;i++)
			{
				if(x[i]==x[k])
					break;
			}
			if(i==k)
			{
				if( (k < n-1) || ((k == n-1) && adj[ x[k]*n + x[0] ] == 1 ))
					return;
			}
		}
	}
}

int req_ham(int adj[],int x[],int k,int n,int flag,int *count)
{
	int i;
	while(1)
	{
		if(flag==-1)
			return flag;
		nextval(adj,x,k,n);
		if(x[k]==n)
		{	x[k]=-1;
			return flag;
		}
		if(k==n-1)
		{
			*count=*count+1;
			printf("\nsolution %d is\n",*count);
			for(i=0;i<n;i++)
				printf("%d->",x[i]+1);
			printf("%d",1);
			printf("\n");
			if(flag==0)
				return -1;
		}
		else
		{
			flag = req_ham(adj,x,k+1,n,flag,count);
		}
	}
	return flag;
}
/*
int req_ham(int adj[],int x[],int k,int n,int flag,int *count)
{
	int i;
	while(1)
	{
		if(flag == -1)
			return flag;
		nextval(adj,x,k,n);
		if(x[k] == n)
			return flag;
		if(k == n-1)
		{
			printf("\n Solution %d\n", *count++);
			for (int i = 0; i < n; ++i)
				printf("%d ->",x[i]+1);
			printf("1\n");
			if(!flag)
				return -1;
		}
		else
			flag = req_ham(adj,x,k+1,n,flag,count);
	}
	return flag;
}
*/

int itr_ham(int adj[],int x[],int n,int flag)
{
	int k = 1,count = 0;
	while(k > 0)
	{
		printf("while\n");	
		nextval(adj,x,k,n);
		if(x[k] == n)
		{
			x[k] = -1;
			k--;
		}
		else
		{
			if(k == n-1)
			{
				printf("\n Solution %d\n", count++);
				for (int i = 0; i < n;i++)
					printf("%d ->",x[i]+1);
				printf("1\n");
				if(!flag)
					return 1;	
			}
			else
				k++;
		}
	}
	return count;
}

int main()
{
	int i,j,k,count;
	int sw,n;
	int *adj,*x;	
	do
	{
		printf("\nPress 1 for Input Graph\nPress 2 For Recursive\nPress 3 for Iterative\nPress 4 for Exit\nEnter your Choice = ");
		scanf("%d",&sw);
		switch(sw)
		{
			case 1:	printf("\nEnter the no. of edges = ");
					scanf("%d",&n);
					adj = (int*)calloc(n*n,sizeof(int));
					input(adj,n);
					display(adj,n);
					break;
			case 2:	do
					{
						printf("\nPress 1 for One solution\nPress 2 For All solution\nPress 3 for Exit\nEnter your Choice = ");
						scanf("%d",&k);
						x = (int*)calloc(n,sizeof(int));
						x[0] = 0;
						for(int i = 1 ; i < n ; i++)
							x[i] = -1;
						switch(k)
						{
							case 1:	count = 0;
									req_ham(adj,x,1,n,0,&count);
									break;
							case 2: count = 0;
									req_ham(adj,x,1,n,1,&count);
									break;
						}
					}while(k != 3);
					free(x);
					break;
			case 3:	do
					{
						printf("\nPress 1 for One solution\nPress 2 For All solution\nPress 3 for Exit\nEnter your Choice = ");
						scanf("%d",&k);
						x = (int*)calloc(n,sizeof(int));
						x[0] = 0;
						for(int i = 1 ; i < n ; i++)
						{
							x[i] = -1;
						}
						switch(k)
						{
							case 1:	itr_ham(adj,x,n,0);
									break;
							case 2: printf("%d soltutions found\n",itr_ham(adj,x,n,1));
									break;
						}
					}while(k!=3);
					free(x);
					break;
		}
	}while(sw != 4);
	return 0;
}