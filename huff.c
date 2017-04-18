#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct client
{
	char id;
	int freq;
}client;

typedef struct hufftree
{
	client data;
	struct hufftree *left,*right;
}hufftree;

typedef struct list
{
	int flag;
	union option
	{
		client data;
		hufftree *address;
	}op;
	struct list *next; 
}list;

typedef struct hashmap
{
	char *code;
}hashmap;

void swap(client *a,client *b)
{
	client temp; 
	temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(client ar[],int n ,int i)
{
	int large = i , lc = 2*i+1,rc = 2*i+2;
	if(lc < n && ar[lc].freq > ar[large].freq)
		large = lc;
	if(rc < n && ar[rc].freq > ar[large].freq)
		large = rc;
	if(large != i)
	{
		swap(&ar[i],&ar[large]);
		heapify(ar,n,large);
	}
}

void build_heap(client ar[],int n)
{
	int i;
	for(i = n/2 -1 ; i >= 0 ; i--)
		heapify(ar,n,i);
}

void heap_sort(client ar[],int n)
{
	build_heap(ar,n);
	int i ;
	for(i = n-1 ; i >=0 ; i--)
	{
		swap(&ar[0],&ar[i]);
		heapify(ar,i,0);
	}
}

list *create()
{
	list *node = (list*)malloc(sizeof(list));
	node->flag = 0;
	return node;
}

void display(list *head)
{
	list *temp = head;
	while(temp != NULL)
	{
		printf("\nthe id is = %c and frequency is = %d",temp->op.data.id,temp->op.data.freq);
		temp = temp->next;
	}
	printf("\n");
}

list *push(list *head,client val)
{
	list *temp = create();
	temp->op.data = val;
	temp->next = head;
	head = temp;
	return head;
}

list *input(client ar[],int n,list *head)
{
	int i;
	char g;
	for(i = 0 ; i < n ; i++)
	{
		printf("\nEnter the id = ");
		scanf("%c",&ar[i].id);
		printf("Enter the frequency = ");
		scanf("%d",&ar[i].freq);
		scanf("%c",&g);
	}
	heap_sort(ar,n);
	head = create();
	head->op.data = ar[n-1];
	head->next = NULL;
	for(i = n -2 ; i >= 0 ; i--)
		head = push(head,ar[i]);
	display(head);
	return head;	
}

hufftree *hcreate()
{
	hufftree *node = (hufftree*)malloc(sizeof(hufftree));
	node->left = node->right = NULL;
	return node;
}

hufftree *build_tree(list *head)
{
	hufftree *lc = NULL;
	while(1)
	{
		hufftree *rc,*prt;
		list *temp = head;
		if(!temp->flag)
		{
			lc = hcreate();
			lc->data = temp->op.data;
		}
		else
			lc = temp->op.address;
		head = head->next;
		free(temp);
		if(head == NULL)
			return lc;
		temp = head;
		if(!temp->flag)
		{
			rc = hcreate();
			rc->data = temp->op.data;
		}
		else
			rc = temp->op.address;
		head = head->next;
		prt = hcreate();
		prt->data.freq = lc->data.freq + rc->data.freq;
		prt->left = lc; prt->right = rc;
		temp->flag = 1;
		temp->op.address = prt;
		int par = prt->data.freq;
		if(head == NULL || (head->flag == 0 && head->op.data.freq >= par) || (head->flag == 1 && head->op.address->data.freq >= par))
		{
			temp->next = head;
			head = temp;
		}
		else
		{
			list *curr = head,*prev;
			while(curr != NULL && ((curr->flag == 0 && curr->op.data.freq < par) || (curr->flag == 1 && curr->op.address->data.freq < par) ))
			{
				prev = curr;
				curr = curr->next;
			}
			temp->next = prev->next;
			prev->next = temp;
		}
	}
	return lc;
}

void inorder(hufftree *root,char bin[],hashmap map[],int index)
{
	if(root != NULL)
	{
		if(root->left == NULL)
		{
			map[root->data.id - 'a'].code = (char*)malloc(sizeof(char)*index);
			bin[index] = '\0';
			strcpy(map[root->data.id -'a'].code,bin);
		}
		bin[index] = '1';
		inorder(root->left,bin,map,index+1);
		printf("\n The Frequency of node is %d ",root->data.freq);
		bin[index] = '0';
		inorder(root->right,bin,map,index+1);
	}
}

int main()
{
	int i,j,n,sw,check[26];
	hashmap map[26];
	list *head = NULL;
	hufftree *root = NULL;
	client *ar;
	char string[20],bin[30],g;
	do
	{
		printf("\n\n\n Press 1 for input\n Press 2 for Build Tree\n Press 3 for Encoding\n Press 4 for Decoding\n Press 5 to exit\n Enter your Choice = ");
		scanf("%d",&sw);
		switch(sw)
		{
			case 1 : printf("\nEnter the no of element = ");
				 scanf("%d",&n);
				 scanf("%c",&g);
				 ar = (client*)malloc(n*sizeof(client));
				 head = input(ar,n,head);
				 break;	
			case 2 : if(head != NULL)
				 {
				 	root = NULL;
				 	root = build_tree(head);
				 	inorder(root,bin,map,0);
				 }
				 else
				 	printf("\nError please enter the input\n");
				 break;	
			case 3 : if(root != NULL)
				 {
				 	printf("\nEnter the String : ");
				 	scanf("%s",bin);
				 	for(i = 0 ; bin[i] != '\0' ; i++)
				 		printf("%s",map[bin[i]-'a'].code);
				 }
				 else
				 	printf("\nError tree not build properly\n");
				 break;	
		    	case 4 : if(root != NULL)
				 {
				 	printf("\nEnter the String : ");
				 	scanf("%s",bin);
				 	hufftree *temp = root; i = 0;
				 	while(bin[i] != '\0')
				 	{
				 		if(temp->left == NULL)
				 		{
				 			printf("%c",temp->data.id);
				 			temp = root;
				 		}
				 		else if(bin[i] == '1')
				 		{
				 			temp = temp->left;
				 			i++;
				 		}
				 		else if(bin[i] == '0')
				 		{
				 			temp = temp->right;
				 			i++;
				 		}
				 	}
				 	if(temp->left == NULL)
				 		printf("%c",temp->data.id);
				 	
				 }
				 else
				 	printf("\nError tree not build properly\n");
				 break;	
		}
	}while(sw != 5);
	return 0;
}
