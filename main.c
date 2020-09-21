#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct _node{
	int val;
	struct _node *next;
	struct _node *pre;
}node;

node *head1;
node *head=NULL;
void push_s(int value)
{

	if(NULL==head)
	{
		head=calloc(0,sizeof(node));
		head1 = head;
		head->val = value;
		printf("addr1 %lx\n",head);
	}
	else
	{
		head->next=calloc(0,sizeof(node));
		head->next->val = value;
		head->next->pre = head;
		head = head->next;
		printf("addr2 %lx\n",head);
	}
}

void pop_s(){
	
	if(head != NULL)
	{
		printf("pop %d",head->val);
		if( head->pre!=NULL)
		{
			head = head->pre;
			free(head->next);
			printf("Normal FREE\n");
		}
		else if(head->pre == NULL)
		{
			free(head);
			head = NULL;
			printf("Final FREE\n");
		}
	}
	else 
		printf("NULL DATA");
}

void print_s(void){
	
	while(head1 != NULL)
	{
		printf("%d->",head1->val);
		head1 = head1->next;
	}
	printf("\n");
}

int main(){
	char s[20];
	int value;

	while(1)
	{
	scanf("%s",s);
	if(0==strcmp(s,"push"))
		{
		printf("please push to stack\n");
		scanf("%d",&value);
		printf("%s %d\n",s,value);
		push_s(value);	
		}
	if(0==strcmp(s,"pop"))
                {
                printf("please pop to stack dd\n");
		//print_s();
		pop_s();
                }
	}

}
