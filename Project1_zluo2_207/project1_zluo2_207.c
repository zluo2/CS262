//Zhiwen Luo G00991813
//CS262
//Project_1_Slot_Machine

#include <stdio.h>
#include <stdlib.h>

#define typeC "Cherry"
#define typeDB "Double Bar"
#define typeSB "Single Bar"
#define typeB "Blank"

void SpinReels(int *a, int *b, int *c);
void DisplaySpin(int a, int b, int c);
unsigned int CalculatePayout(int bet,int a,int b,int c);
void enterRandomSeed();
int checkBank(int bet, int allMoney);

int main(){

	char answer = 'y';
	int allMoney = 100;
	enterRandomSeed();

	while (answer == 'y'|| answer == 'Y')
	{
		
		printf("You only have %d, and you can place your bet between 1 to 10 every time\n", allMoney);
		printf("Before the Beginning of this game\n");
		printf("Please place your bet:    \n");

		int bet = 0;
		scanf("%d",&bet);
		getchar();  //eliminate "enter"

		if (bet>0 && bet<=10 && checkBank(bet,allMoney)){

			allMoney -= bet;

			int randomNum, randomNum1, randomNum2;
			int payout = 0;
			SpinReels(&randomNum,&randomNum1,&randomNum2);
			payout = CalculatePayout(bet,randomNum,randomNum1,randomNum2);
			allMoney+=payout;

			DisplaySpin(randomNum,randomNum1,randomNum2);
			printf("Payout is %d\n",payout);
			printf("Your bankroll is %d\n",allMoney);
			
			if (allMoney == 0){
				printf("Sorry, you don't have money now. See you next time!\n");
				break;
			}
		}
		else continue;

		while(1){

			printf("Do you want to play this game again? \n");
			printf("Please enter Y or y as Yes  \n");
			printf("Please enter N or n as NO:  \n");

			answer = getchar();
			getchar();

			if (answer == 'n'||answer == 'N'){
				printf("Welcome back, you have %d in the backroll\n", allMoney);
				break;
			}

			if (answer == 'y'|| answer == 'Y' || answer == 'N' || answer == 'n')
				break;
			else printf("Please enter correct character\n");
			
		}
 	}

	return 0;

}

void SpinReels(int *a, int *b, int *c){

	*a = random()%40+1;
	*b = random()%40+1;
	*c = random()%40+1; 
}

void enterRandomSeed(){

	unsigned int mySeed = 0;
	printf("Hello, please enter a luck number as RNG:  \n");
	scanf("%d", &mySeed);
	getchar(); //eliminate "enter"
	srandom(mySeed);
}

int checkBank(int bet, int allMoney){

	int rest = allMoney - bet;
	if (rest>=0)
		return 1;

	else {
		printf("Sorry, you don't have enough money\n");
		return 0;
	}
} 

void DisplaySpin(int a, int b, int c){

	if (a == 1)
			printf("    %s    ",typeC);
		else if (2<=a && a<=4)
			printf("    %s    ",typeDB);
		else if (5<=a && a<=8)
			printf("    %s    ",typeSB);
		else 
			printf("    %s    ",typeB);

	if (b == 1)
			printf("%s    ",typeC);
		else if (2<=b && b<=4)
			printf("%s    ",typeDB);
		else if (5<=b && b<=8)
			printf("%s    ",typeSB);
		else 
			printf("%s    ",typeB);

	if (c == 1)
			printf("%s\n",typeC);
		else if (2<=c && c<=4)
			printf("%s\n",typeDB);
		else if (5<=c && c<=8)
			printf("%s\n",typeSB);
		else 
			printf("%s\n",typeB);
}

unsigned int CalculatePayout(int bet, int a, int b, int c){

	int multi = 0;
	int temp[3] = {a,b,c};
	int count = 0;

	int i;
	for (i=0;i<3;i++){
		if (temp[i]>8)
			count++;
	}

	if (count == 0){
		multi = 1;
		int i;
		for (i=0; i<3; i++){

			if (temp[i] == 1)
				multi *= 3;
			else if (2<=temp[i] && temp[i]<=4)
				multi *= 2;
			else if (5<=temp[i] && temp[i]<=8)
				multi *= 1;
		}
	}
	else{
		int i;
		for (i=0; i<3; i++){

			if (temp[i] == 1)
				multi += 3;
			else if (2<=temp[i] && temp[i]<=4)
				multi += 2;
			else if (5<=temp[i] && temp[i]<=8)
				multi += 1;
			else
				multi += 0;
		}
	}

	return bet*multi;			
}
