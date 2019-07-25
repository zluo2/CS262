//Zhiwen Luo G00991813
//CS262
//Project_2_The George Mason University Short Message Service System

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sms.h"

#define lengthOfFileName 50
#define lengthOfPackedArray 120
#define lengthOfUnpackedArray 160
#define lengthOfBuffer 160

void menu ();
void PackArray(char *packed, size_t packedSize, char *unpacked, size_t unpackedSize);
void UnpackArray(char *unpacked, size_t unpackedSize, char *packed, size_t packedSize);

int main(){

	int runThisProgram = 1;
	char choice = 0;

	while (runThisProgram){

		menu();
		//get the choice from the user
		choice = getchar();
		getchar(); // eliminate "enter"

		if (choice == 'P' || choice == 'p'){

			//initialize
			char buffer[lengthOfBuffer] = {'\0'};;
			char buffer1[lengthOfBuffer] = {'\0'};
			char filename[lengthOfFileName] = {'\0'};

			//get the filename 
			printf("%s\n","Please enter a filename in which to save the packed array: ");
			fgets(buffer, lengthOfFileName, stdin);
			sscanf(buffer,"%s",filename);

			//get the message 
   			printf("%s\n","The line of text to pack and save: " );
			fgets(buffer1, lengthOfBuffer, stdin);

			// remove the newline character
			if (strlen(buffer1)>=1)
				buffer1[strlen(buffer1)-1] = 0;

			//initialize
			int i = 0;
			char unPacked[lengthOfUnpackedArray] = {'\0'};
			char packed[lengthOfPackedArray] = {'\0'};

			//convert the message 
			for (i = 0; i<strlen(buffer1); i++){
				unPacked[i] = CharToSMS(buffer1[i]);
			}

			FILE * outFile;
   			outFile = fopen (filename , "wb");

   			//check 
			if (outFile == NULL)
    		{
        		printf("Error opening outfile, Please try again\n");
        		printf("\n");
        		continue;
    		}

    		//pack the unpack message
    		PackArray(packed, lengthOfPackedArray, unPacked, strlen(unPacked));

    		//write the pack message to file
    		fwrite(packed,sizeof(char),strlen(packed),outFile);

    		//close the file 
    		fclose(outFile);

    		//flushing the input buffer
    		if (strlen(buffer1) == (lengthOfBuffer-2)){
				char ch;
				while((ch = getchar()) != '\n' && ch != EOF);
    		}

    		printf("\n");
		}
		else if (choice == 'U' || choice == 'u'){

			//initialize
			char buffer[lengthOfBuffer] = {'\0'};
			char filename[lengthOfFileName] = {'\0'};
			char output[lengthOfUnpackedArray] = {'\0'};

			//get the message 
			printf("%s\n","Please enter a filename which contains a save message in the packed format: ");
			fgets(buffer, lengthOfFileName, stdin);
			sscanf(buffer,"%s",filename);

			FILE * inFile;
   			inFile = fopen (filename , "rb");

   			//check 
   			if (inFile == NULL)
    		{
        		printf("Error opening infile, please try again\n");
        		printf("\n");
        		continue;
    		}

    		//initialize
    		char packed[lengthOfPackedArray] = {'\0'};
    		char unPacked[lengthOfUnpackedArray] = {'\0'};

    		//read the pack message from the file 
    		fread(packed,sizeof(char),lengthOfBuffer,inFile);
    		
    		//unpack the pack message 
    		UnpackArray(unPacked, lengthOfUnpackedArray, packed, strlen(packed));

    		//convert the unpack message to SMS message 
    		int i = 0;
    		for (i = 0; i<strlen(unPacked);i++)
    			output[i] = SMSToChar(unPacked[i]);
    		
    		printf("%s\n",output);
    		printf("\n");

    		//close the infile 
    		fclose(inFile);
		} 
		else if (choice == 'Q' || choice == 'q'){

			printf("%s\n","Have a good day, Bye");
			break;
		}
		else{
			printf("%s\n","Please enter correct choice!");
			printf("\n");
		}
	}

	return 0;
}

void menu (){

	printf("%s\n","Pack and save a line of text: Options are 'P' or 'p'");
	printf("%s\n","Unpacked and print a line of text: Options are 'U' or 'u'");
	printf("%s\n","Quit: Options are 'Q' or 'q'");
	printf("%s\n","Please enter your choice: ");
}

void PackArray(char *packed, size_t packedSize, char *unpacked, size_t unpackedSize){

	int i = 0;
	int count = 0;
	int change = 0;

	//four unpack characters convert three pack characters 
	for (i = 0; i<unpackedSize; i++){
		if ((i+1)%4 == 0 ) continue;
		unsigned char temp1 = unpacked[i];
		unsigned char temp2 = unpacked[i+1];
		temp1 = temp1 >> change;
		temp2 = temp2 << (6-change);
		temp1 = temp1 | temp2;
		packed[count++] = temp1;
		change = (change+2)%6;
	}

	if (unpackedSize%4 != 0){

		unsigned char temp1 = unpacked[unpackedSize];
		temp1 = temp1 >> change;
		packed[count] = temp1;
	}

}

void UnpackArray(char *unpacked, size_t unpackedSize, char *packed, size_t packedSize){

	int i = 0;
	//four unpack characters convert three pack characters 
	for (i = 0; i<packedSize/3; i++){ //so the pack message divided 3 

		unsigned char temp1;
		unsigned char temp2;
		unsigned char temp3;

		temp1 = packed[i*3];
		temp1 = temp1<<2;
		temp1 = temp1>>2;
		unpacked[4*i] = temp1;

		temp1 = packed[i*3];
		temp2 = packed[i*3+1];
		temp1 = temp1>>6;
		temp2 = temp2<<4;
		temp2 = temp2>>2;
		unpacked[4*i+1] = temp2|temp1;

		temp2 = packed[i*3+1];
		temp3 = packed[i*3+2];
		temp2 = temp2>>4;
		temp3 = temp3<<6;
		temp3 = temp3>>2;
		unpacked[4*i+2] = temp2|temp3;

		temp3 = packed[i*3+2];
		temp3 = temp3>>2;
		unpacked[4*i+3] = temp3;	
	}

	//For one more char 
	if (packedSize%3 == 1){

		unsigned char temp1;
		temp1 = packed[packedSize-1];
		temp1 = temp1<<2;
		temp1 = temp1>>2;
		unpacked[4*i] = temp1;
	}
	//For two more chars
	else if (packedSize%3 == 2){

		unsigned char temp1;
		unsigned char temp2;

		temp1 = packed[packedSize-2];
		temp1 = temp1<<2;
		temp1 = temp1>>2;
		unpacked[4*i] = temp1;

		temp1 = packed[packedSize-2];
		temp2 = packed[packedSize-1];
		temp1 = temp1>>6;
		temp2 = temp2<<4;
		temp2 = temp2>>2;
		unpacked[4*i+1] = temp2|temp1;
	}
}