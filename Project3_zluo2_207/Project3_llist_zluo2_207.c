#include <stdlib.h>
#include <stdio.h>

typedef struct _passenger
{
	int ID; //using in order 
	char lastName[25];
	char firstName[25];
	double balance;
	char location; //location 1 = onShip, 0 == offShip
}Passenger;

typedef struct _node
{
	Passenger passenger;
	struct _node * next;
}Node;

//ok !
void insertList(Node *head, Node *newNode)
{
	Node *temp = head;
	while ((temp ->next != NULL)&&(temp->next->passenger.ID<newNode->passenger.ID))
		temp = temp->next;
	newNode ->next = temp ->next;
	temp->next = newNode;
}

Node * searchList(Node *head, int ID)
{
	Node * temp = head;
	while ((temp!=NULL)&&(temp->passenger.ID!=ID))
		temp = temp -> next;
	return temp;
}

void printNode(Node * node)
{
	printf("%d\n",node->passenger.ID);
	printf("%s\n%s\n",node->passenger.firstName,node->passenger.lastName);
	printf("%lf\n", node->passenger.balance);
}

void printList(Node *head)
{	
	Node *temp = head->next;
	while (temp!=NULL)
	{	
		printNode(temp);
		temp = temp->next;
	}
	printf("\n");
}

int lengthofList(Node * head)
{
	int count = 0;

	Node *temp = head->next;
	while (temp!=NULL)
	{	
		count++;
		temp = temp->next;
	}

	return count;
}

Node * removedNode(Node * head, int ID)
{
	Node * removed = NULL;

	if ((head == NULL)||(head->next == NULL))
		removed = NULL;
	else if (head -> next ->passenger.ID == ID)
	{
		removed = head -> next;
		head->next = head->next->next;
		removed->next = NULL;
	}
	else if (head -> next ->passenger.ID != ID)
	{
		Node * temp = head;

		while ((temp->next!=NULL)&&(temp->next->passenger.ID!=ID))
			temp = temp -> next;

		if (temp->next!=NULL)
		{
			removed = temp->next;
			temp->next = removed ->next;
			removed -> next = NULL;
		}
	}

	return removed;
}

void deleteList(Node *head)
{
	while (head != NULL)
	{
		Node *temp = head;
		head = head->next;
		free(temp);
	}
}