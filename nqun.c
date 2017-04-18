#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_place(int ar[],int row,int col)
{
	for(int i = 0 ; i < row ; i++)
		if(abs(row - i) == abs(col - ar[i]) || col == ar[i])
			return 0;
	return 1;
}

void display(int ar[],int n)
{
	for(int i = 0 ; i < n ; i++)
	{
		for(int j = 0 ; j < n ; j++)
		{
			if(ar[i] == j)
				printf("| Q |");
			else
				printf("| - |");
		}
		printf("\n");
	}
}

int req_nq(int ar[],int n,int k,int flag ,int *count)
{
	for(int i  = 0 ; i < n ; i++)
	{
		if(flag == -1)
			return flag;
		if(is_place(ar,k,i))
		{
			ar[k] = i;
			if(k == n - 1)
			{
				(*count)++;
				printf("\n Solution %d\n",*count);
				display(ar,n);
				if(flag == 0)
					return -1;
			}
			else
				flag = req_nq(ar,n,k+1,flag,count);
		}
	}
	return flag;
}

int itr_nq(int ar[],int n,int flag)
{
	int row = 0,count = 0;
	while(row >= 0)
	{
		ar[row] = ar[row] + 1;
		if(ar[row] <= n-1)
		{
			if(is_place(ar,row,ar[row]))
			{
				if(row == n -1)
				{
					count++;
					printf("\n Solution %d\n",count);
					display(ar,n);
					if(flag == 0)
						return 1;
					}
				else
					row++;
			}
		}
		else
		{
			ar[row] = -1;
			row--;
		}
	}
	return count;
}


int main()
{
	int i,j,k,cnt;
	int sw,n;
	do
	{
		printf("\n\nPress 1 for Input\nPress 2 for Recursive\nPress 3 for Iterative\nPress 4 for Exit \nEnter Your Choice = ");
		scanf("%d",&sw);
		switch(sw)
		{
			case 1 : printf("\nEnter the no . of Queens = ");
					 scanf("%d",&n);
					 break;
			case 2 : do
					 {
					 	int *ar = (int*)malloc(n*sizeof(ar));
					 	printf("\n\nPress 1 for One Sol\nPress 2 for All sol\nPress 3 for Exit\nEnter Your Choice = ");
					 	scanf("%d",&k);
					 	switch(k)
					 	{
					 		case 1: cnt = 0;
					 				req_nq(ar,n,0,0,&cnt);
					 				break;
					 		case 2: cnt = 0;
					 				req_nq(ar,n,0,1,&cnt);
					 				printf("\nTotal no of Solution are %d\n",cnt);
					 				break;
					 	}
					 }while(k!=3);
			case 3 : do
					 {
					 	int *ar = (int*)malloc(n*sizeof(ar));
					 	printf("\n\nPress 1 for One Sol\nPress 2 for All sol\nPress 3 for Exit\nEnter Your Choice = ");
					 	scanf("%d",&k);
					 	for (int i = 0; i < n; ++i)
					 		ar[i] = -1;
					 	switch(k)
					 	{
					 		case 1: itr_nq(ar,n,0);
					 				break;
					 		case 2: printf("\nTotal no of Solution are %d\n",itr_nq(ar,n,1) );
					 				break;
					 	}
					 }while(k!=3);
		}
	}while(sw != 4);
	return 0;
}
