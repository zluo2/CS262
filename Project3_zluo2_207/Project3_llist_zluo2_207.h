#ifndef PROJECT3_LLIST_ZLUO2_207_H
#define PROJECT3_LLIST_ZLUO2_207_H

typedef struct _passenger
{
	int ID; //using in order 
	char lastName[25];
	char firstName[25];
	double balance;
	char location;
}Passenger;

typedef struct _node
{
	Passenger passenger;
	struct _node * next;
}Node;

void insertList(Node *head, Node *newNode);
Node * searchList(Node *head, int ID);
void printList(Node *head);
void deleteList(Node *head);
Node * removedNode(Node * head, int ID);
int lengthofList(Node * head);
void printNode(Node * node);


#endif 