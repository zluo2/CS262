//Zhiwen luo 00991813
//CS262 207
//Project3

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Project3_llist_zluo2_207.h"

#define lengthOfBuffer 100
#define lengthOfBuffer_passenger 35
#define lengthOfFirstName 25
#define lengthOfLastName 35

//three Menu
void mainMenu();
void passengerInformationMenu();
void printMenu();

//functions from the main Menu
int readPassengerManinfest(Node * head);
void embarkAllPassengers(Node * onShip, Node * offShip);
void debarkAllPassengers(Node * onShip, Node * offShip);

//Functions from the information menu
void embarkPassenger(Node * onShip, Node * offShip);
void debarkPassenger(Node * onShip, Node * offShip);
void passengerOnBoardPurchase(Node * onShip, Node * offShip);
void passengerOffBoardPurchase(Node * onShip, Node * offShip);
void synchronizePassengerlists(Node * onShip, Node * offShip);
void CheckOnShipPassengerlist(Node * onShip, Node * offShip);
void CheckOffShipPassengerlist(Node * onShip, Node * offShip);

//Functions from the print menu
void printAccountForSinglePassenger(Node *onShip, Node *offShip);
void printAllPassengerAccount(Node *onShip, Node *offShip);
void printAccountForOnShipPassenger(Node *onShip);
void printAccountForOffShipPassenger(Node *offShip);

int main()
{
	//two linked list, one for passenger on board, one for off ship
	Node * head_offShip = malloc(sizeof(Node));
	//check 
	if (head_offShip == NULL)
	{			
		printf("Error to creat the node\n");
		return 0;
	}
	head_offShip -> next = NULL;

	Node * head_onShip = malloc(sizeof(Node));
	//check 
	if (head_onShip == NULL)
	{			
		printf("Error to creat the node\n");
		return 0;
	}
	head_onShip -> next = NULL;

	int runThisProgram = 1;
	char choice = 0;

	while (runThisProgram)
	{
		mainMenu();
		//get the choice from the user
		choice = getchar();
		//eliminate "enter"
		getchar();

		if (choice == '1')
		{
			if (readPassengerManinfest(head_offShip) == 0)
				printf("Error in readPassengerManinfest\n");
		}
		else if(choice == '2')
		{	
			embarkAllPassengers(head_onShip, head_offShip);
		}
		else if(choice == '3')
		{
			
			while (runThisProgram)
			{
				//Display the Passenger Information Menu 
				passengerInformationMenu();
				char choice_passenger = 0;
				//get the choice
				choice_passenger = getchar();
				//eliminate "enter"
				getchar();
				if (choice_passenger == '1')
				{
					embarkPassenger(head_onShip, head_offShip);

				}
				else if (choice_passenger == '2')
				{
					debarkPassenger(head_onShip, head_offShip);

				}
				else if (choice_passenger == '3')
				{
					passengerOnBoardPurchase(head_onShip, head_offShip);

				}
				else if (choice_passenger == '4')
				{	
					passengerOffBoardPurchase(head_onShip, head_offShip);

				}
				else if (choice_passenger == '5')
				{

					synchronizePassengerlists(head_onShip, head_offShip);
				}
				else if (choice_passenger == '6')
				{
					break;
				}
				else 
				{
					printf("We don't have that choice\n");
				}
			}
			

		}
		else if (choice == '4')
		{
			
			//Display the Print Menu 
			while (runThisProgram)
			{
				//Display the Passenger Information Menu 
				printMenu();
				char choice_print = 0;
				//get the choice
				choice_print = getchar();
				//eliminate "enter"
				getchar();
				if (choice_print == '1')
				{
					printAccountForSinglePassenger(head_onShip, head_offShip);
				}
				else if (choice_print == '2')
				{
					printAllPassengerAccount(head_onShip, head_offShip);
				}
				else if (choice_print == '3')
				{
					printAccountForOnShipPassenger(head_onShip);
				}
				else if (choice_print == '4')
				{	
					printAccountForOffShipPassenger(head_offShip);
				}
				else if (choice_print == '5')
				{
					break;
				}
				else 
				{
					printf("We don't have that choice\n");
				}
			}
			
		}
		else if (choice == '5')
		{
			debarkAllPassengers(head_onShip,head_offShip);
		}
		else if (choice == '6')
		{
			//Remove all nodes from both the onShip 
			//and offShip lists and free the memory
			deleteList(head_offShip);
			deleteList(head_onShip);
			//exit
			break;
		}
		else 
		{
			printf("Please enter the correct choice from the menu!\n");
		}

	}

	return 0;
}

void mainMenu()
{
	printf("Read Passenger Maininfuest: Option is '1'\n");
	printf("Embark all passenger: Option is '2'\n");
	printf("Passenger Information: Option is '3'\n");
	printf("Print Menu: Option is '4'\n");
	printf("Debark all Passenger: Option is '5'\n");
	printf("Quit: Option is '6'\n");
}

void passengerInformationMenu()
{
	printf("Embark Passenger: Option is '1'\n");
	printf("Debark Passenger: Option is '2'\n");
	printf("Passenger OnBoard Purchase: Option is '3'\n");
	printf("Passenger OffBoard Purchase: Option is '4'\n");
	printf("Synchronize Passenger Lists: Option is '5'\n");
	printf("return to Main Menu: Option is '6'\n");
}

void printMenu()
{
	printf("Print Account for Single Passenger: Option is '1'\n");
	printf("Print All Passenger Accounts: Option is '2'\n");
	printf("Print Accounts for onShip Passengers: Option is '3'\n");
	printf("Print Accounts for offShip Passengers: Option is '4'\n");
	printf("Return to Main Menu: Option is '5'\n");
}


int readPassengerManinfest(Node * head)
{
	char buffer[lengthOfBuffer]={'\0'};
	char filename[lengthOfBuffer]={'\0'};

	//get the filename 
	printf("Please enter a filename conatining the Passenger Manifest\n");
	fgets(buffer, lengthOfBuffer, stdin);
	sscanf(buffer,"%s",filename);

	FILE * inFile;
	inFile = fopen (filename, "r");
	//check
	if (inFile == NULL)
	{
		printf("Error opening infile, please try again\n");
		printf("\n");
		return 0;
	}

	//read the information from the file, 
	char buffer_passenger[lengthOfBuffer_passenger]={'\0'};
	while (fgets(buffer_passenger, lengthOfBuffer_passenger, inFile)!=NULL)
	{
		int temp_ID = 0;
		char temp_FirstName[lengthOfFirstName]={'\0'};
		char temp_LastName[lengthOfLastName]={'\0'};

		sscanf(buffer_passenger,"%d",&temp_ID);
		memset(buffer_passenger,0,lengthOfBuffer_passenger);

		if (fgets(buffer_passenger, lengthOfBuffer_passenger, inFile)!=NULL){
			sscanf(buffer_passenger,"%s",temp_FirstName);
			memset(buffer_passenger,0,lengthOfBuffer_passenger);
		}

		if (fgets(buffer_passenger, lengthOfBuffer_passenger, inFile)!=NULL){
			sscanf(buffer_passenger,"%s",temp_LastName);
			memset(buffer_passenger,0,lengthOfBuffer_passenger);
		}

		//creating Passengers and adding them to the offShip list
		Node * newNode = malloc(sizeof(Node));
		//check 
		if (newNode == NULL)
		{			
			printf("Error to creat the node\n");
			return 0;
		}
		newNode -> next = NULL;

		newNode->passenger.ID = temp_ID;
		strcpy(newNode->passenger.lastName,temp_LastName);
		strcpy(newNode->passenger.firstName,temp_FirstName);
		newNode->passenger.balance = 0.0;
		newNode->passenger.location = 0;

		insertList(head,newNode);
	}

	//close the file 
	fclose (inFile);
	return 1;
}


void embarkAllPassengers(Node * onShip, Node * offShip)
{
	//Move all passengers from the offShip list to the onShip list
	Node * temp = offShip->next;
	while (temp!=NULL)
	{	
		int ID = temp -> passenger.ID;
		temp -> passenger.location = 1;
		temp = temp->next;
		insertList(onShip,removedNode(offShip, ID));
		
	}
}

void debarkAllPassengers(Node * onShip, Node * offShip)
{
	//Move all passengers from the onShip list to the offShip list
	double total = 0.0;
	int count = 0;

	Node * temp  = onShip->next;
	while (temp!=NULL)
	{	
		int ID = temp -> passenger.ID;
		temp->passenger.location = 0;
		//Calculate and display total amount of money spent
		total += temp->passenger.balance;
		count++;
		//
		temp = temp -> next;
		insertList(offShip,removedNode(onShip,ID));
		
	}

	//calculate the average 
	double average = 0.0;
	if (count == 0) 
		average = 0;
	else 
		average = total/count;

	printf("total amout of moeny = %lf\n",total);
	//and the average amount spent per passenger
	printf("average amout spent per passenger = %lf\n", average);
}



void embarkPassenger(Node * onShip, Node * offShip)
{
	printf("Please enter the passenger ID: \n");
	char buffer[lengthOfBuffer] = {'\0'};
	int passenger_ID = 0;

	fgets(buffer,lengthOfBuffer,stdin);
	sscanf(buffer, "%d", &passenger_ID);

	Node * node_findOffShip = searchList(offShip,passenger_ID);
	Node * node_findOnShip = searchList(onShip,passenger_ID);

	if (node_findOffShip != NULL && node_findOnShip == NULL)
	{
		Node * temp = removedNode(offShip, passenger_ID);
		temp->passenger.location = 1;
		insertList(onShip, temp);
	}
	else if (node_findOffShip == NULL && node_findOnShip != NULL)
	{	
		//If the passenger is found in the onShip list, a message stating so is written to the console
		printf("The passenger has on ship\n");
	}
	else 
	{
		printf("ID is incorrect\n");
	}
}


void debarkPassenger(Node * onShip, Node * offShip)
{
	printf("Please enter the passenger ID: \n");
	char buffer[lengthOfBuffer] = {'\0'};
	int passenger_ID = 0;

	fgets(buffer,lengthOfBuffer,stdin);
	sscanf(buffer, "%d", &passenger_ID);

	Node * node_findOffShip = searchList(offShip,passenger_ID);
	Node * node_findOnShip = searchList(onShip,passenger_ID);

	if (node_findOffShip == NULL && node_findOnShip != NULL)
	{
		Node * temp = removedNode(onShip, passenger_ID);
		temp->passenger.location = 0;
		insertList(offShip, temp);
	}
	else if (node_findOffShip != NULL && node_findOnShip == NULL)
	{	
		//If the passenger is found in the onShip list, a message stating so is written to the console
		printf("The passenger has off ship\n");
	}
	else 
	{
		printf("ID is incorrect\n");
	}
}


void passengerOnBoardPurchase(Node * onShip, Node * offShip)
{	
	//get the ID
	printf("Please enter the passenger ID: \n");
	char buffer[lengthOfBuffer] = {'\0'};
	int passenger_ID = 0;
	double money = 0.0;

	fgets(buffer,lengthOfBuffer,stdin);
	sscanf(buffer, "%d", &passenger_ID);

	//erase the buffer
	memset(buffer, 0, lengthOfBuffer);

	printf("Please enter the the amount of purchase: \n");
	//get the money 
	fgets(buffer,lengthOfBuffer,stdin);
	sscanf(buffer, "%lf", &money);

	Node * node_findOffShip = searchList(offShip,passenger_ID);
	Node * node_findOnShip = searchList(onShip,passenger_ID);

	//check the passenger
	if (node_findOnShip!=NULL)
	{
		node_findOnShip->passenger.balance += money;
	}
	else
	{
		if (node_findOffShip != NULL){
			node_findOffShip -> passenger.balance += money;
			node_findOffShip->passenger.location = 1;
		}
		else 
		{
			printf("ID is incorrect\n");
		}
	}

}

void passengerOffBoardPurchase(Node * onShip, Node * offShip)
{
	//get the ID
	printf("Please enter the passenger ID: \n");
	char buffer[lengthOfBuffer] = {'\0'};
	int passenger_ID = 0;
	double money = 0.0;

	fgets(buffer,lengthOfBuffer,stdin);
	sscanf(buffer, "%d", &passenger_ID);

	//erase the buffer
	memset(buffer, 0, lengthOfBuffer);

	printf("Please enter the the amount of purchase: \n");
	//get the money 
	fgets(buffer,lengthOfBuffer,stdin);
	sscanf(buffer, "%lf", &money);

	Node * node_findOffShip = searchList(offShip,passenger_ID);
	Node * node_findOnShip = searchList(onShip,passenger_ID);

	//check the passenger.
	if (node_findOffShip!=NULL)
	{
		node_findOffShip->passenger.balance += money;
	}
	else
	{
		if (node_findOnShip != NULL){
			node_findOnShip -> passenger.balance += money;
			node_findOnShip->passenger.location = 0;
		}
		else 
		{
			printf("ID is incorrect\n");
		}
	}
}

void CheckOnShipPassengerlist(Node * onShip, Node * offShip)
{
	Node *temp = onShip->next;
	int ID = 0;

	while (temp!=NULL)
	{	
		
		if (temp->passenger.location == 0)
		{
			ID = temp->passenger.ID;
			if (searchList(onShip,ID)!=NULL)
			{
				Node * newNode = removedNode(onShip, ID);
				insertList(offShip, newNode);
			}
			temp = temp->next;
		}
		else 
			temp = temp->next;
	}

}

void CheckOffShipPassengerlist(Node * onShip, Node * offShip)
{
	Node *temp  = offShip->next;
	int ID = 0;
	while (temp!=NULL)
	{	
		if (temp->passenger.location == 1)
		{
			ID = temp->passenger.ID;
			if (searchList(offShip,ID)!=NULL)
			{
				Node * newNode = removedNode(offShip, ID);
				insertList(onShip, newNode);
			}
			temp = temp->next;
		}
		else 
			temp = temp->next;
	}


}

void synchronizePassengerlists(Node * onShip, Node * offShip)
{
	int length_onShip = lengthofList(onShip);
	int length_offShip = lengthofList(offShip);
	int i;

	for (i = 0; i<length_onShip; i++)
		CheckOnShipPassengerlist(onShip, offShip);
	for (i = 0; i<length_offShip; i++)
		CheckOffShipPassengerlist(onShip, offShip);
}


void printAccountForSinglePassenger(Node *onShip, Node *offShip)
{
	printf("Please enter the passenger ID: \n");
	char buffer[lengthOfBuffer] = {'\0'};
	int passenger_ID = 0;

	fgets(buffer,lengthOfBuffer,stdin);
	sscanf(buffer, "%d", &passenger_ID);
	
	Node * node_findOffShip = searchList(offShip,passenger_ID);
	Node * node_findOnShip = searchList(onShip,passenger_ID);

	if (node_findOnShip!=NULL)
	{
		printNode(node_findOnShip);
	}
	else
	{
		if (node_findOffShip!=NULL)
		{
			printNode(node_findOffShip);
		}
		else
		{
			printf("ID is incorrect\n");
		}
	}

}

void printAllPassengerAccount(Node *onShip, Node *offShip)
{
	printf("On ship: \n");
	printAccountForOnShipPassenger(onShip);
	printf("Off Ship: \n");
	printAccountForOffShipPassenger(offShip);
}

void printAccountForOnShipPassenger(Node *onShip)
{
	//Print Accounts for onShip Passengers
	Node *temp = onShip->next;
	while (temp!=NULL)
	{	
		printf("%d\n", temp->passenger.ID);
		printf("%lf\n", temp->passenger.balance);
		temp = temp->next;
	}
}

void printAccountForOffShipPassenger(Node *offShip)
{
	//Print Accounts for offShip Passengers
	Node *temp = offShip->next;
	while (temp!=NULL)
	{	
		printf("%d\n", temp->passenger.ID);
		printf("%lf\n", temp->passenger.balance);
		temp = temp->next;
	}
}

