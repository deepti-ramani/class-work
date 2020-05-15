/*
list.c
by Deepti Ramani
05/12/2020
This class will be used to create a linked list

gcc -O -Wall -Wextra -ansi -pedantic main.c list.c -o list.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void add_front(struct Node **list, int value)
{
	/* create a new node containing value */
	struct Node *new = (struct Node*)malloc(sizeof(struct Node));
	new->number = value;
	
	/* attach the new node to the curr head of list */
	new->next = *list;
	
	/* make the new node our new head */
	*list = new;
}

void add_back(struct Node **list, int value)
{
	/* create a new node containing value */
	struct Node *new = (struct Node*)malloc(sizeof(struct Node));
	struct Node *temp = *list;
	
	new->number = value;
	new->next = NULL;
	
	/* if the list is empty, we automatically add the new node as the first element */
	if(*list == NULL)
	{
		*list = new;
		return;
	}
	
	/* otherwise, keep going thorugh the list until we get to the last node */
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	
	/* attach the last node to our new node */
	temp->next = new;
}

void free_list(struct Node *list)
{
	struct Node *temp;
	
	/* keep going until we have no more nodes to check */
	while(list != NULL)
	{
		/* remove the current node and set the next node as the head */
		temp = list;
		list = list->next;
		free(temp);
	}
}

void print_list(const struct Node *list)
{
	/* go through the nodes until there are no more nodes */
	while(list != NULL)
	{
		/* print each node */
		printf("%3d", list->number);
		list = list->next;
	}
	printf("\n");
}

void remove_item(struct Node **list, int value)
{
	/* hold the current and previous nodes */
	struct Node *prev = *list;
	struct Node *temp = *list;
	
	/* if the first node contains value, remove it and make the next node the head */
	if(temp != NULL && temp->number == value)
	{	
		*list = temp->next;
		free(temp);
		return;
	}
	
	/* otherwise, keep searching through the list until we find a node that contains value */
	while(temp != NULL)
	{
		/* if we find one, connect the prev node to the next node and remove the middle (curr) node containing value */
		if(temp->number == value)
		{
			prev->next = temp->next;
			free(temp);
			return;
		}
		/* if we can't find a node with value, keep searching until there are no nodes left to search */
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
}

int size_list(const struct Node *list)
{
	/* store the number of nodes */
	int numNodes = 0;
	
	/* iterate thorugh the list until no more nodes remain */
	while(list != NULL)
	{
		numNodes++;
		list = list->next;
	}
	
	return numNodes;
}

int sum_list(const struct Node *list)
{
	/* store the sum of the values in the nodes */
	int sum = 0;
	
	/* iterate through the list until no more nodes remain */
	while(list != NULL)
	{
		sum += list->number;
		list = list->next;
	}
	
	return sum;
}