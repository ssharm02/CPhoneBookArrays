//PhoneBook project by Sarthak Sharma and Luis Ortiz

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define MAX 50
#include <ctype.h>
typedef struct Phonebook_Contacts {
	char fName[30];
	char lName[30];
	char phone[11];
}Phonebook;
//void addToContacts (Phonebook *);

int counter = 0;
char fileName[20] = "Phonedata.txt";
FILE *read;
FILE *write;


//Load function loads the txt file and then stores its contents in an array
void loadFromFile(char filename[10], Phonebook contacts[]){
	// create temp variables that hold the data while reading the file 
	char tmpfName[30]; 
	char tmplName[30]; 
	char tmpPhone[11]; 
	int counter; // will be used to determine the index at which the record will be saved
	FILE *input=fopen(filename,"r+");
	
	if(input==NULL) 
		printf("Error: Cannot open the file");
	else
		{
		//fscanf(input, "%*[^\n]"); // discard the first line
		counter=0; // the next record will be written to index 0
		// continue in reading the file till the EOF
		
		while(!feof(input)){
			strcpy(tmpfName,""); 
			fscanf(input,"%s %s %s", tmpfName, tmplName, tmpPhone); 
			if(strcmp(tmpfName,"")!=0){
				// At this point we gurantee we have new data into the tmpName
				// so will copy data from the tmp variables to the array
				strcpy(contacts[counter].fName,tmpfName);
				strcpy(contacts[counter].lName,tmplName); 
				strcpy(contacts[counter].phone,tmpPhone); 
				// after inserting a record, increment the counter to determine 
				// the place for the new record 
				counter++;		
			}		
		} // the end of the while 
		// we reach here when reaching the end of the file so close it
		fclose(input);
	} // the end of the else that indicates the file has been openned 

}

void addToContacts(Phonebook * pb)
{
	write = fopen(fileName, "a");
	if (write == NULL)
	{
		perror("The following error occurred ");
	}
	else {
		counter++;
printf("Enter first name: ");
scanf("%s", pb[counter-1].fName);
printf("Enter last name: ");
scanf("%s", pb[counter-1].lName);
printf("Enter phone number: ");
scanf("%s", pb[counter-1].phone);
fprintf(write, "%s\t%s\t%s\n", pb[counter-1].fName, pb[counter-1].lName, pb[counter-1].phone);
	fclose(write);
	}
}//end of function
//Simple method that clears the console screen  
void clrscr(void)
{
    system("@cls||clear");
}

//Method deletes entries that are stored in memory as user types
void DeleteEntry (Phonebook * Phonebook)
{
   int x = 0;
   int i = 0;
   char deleteFirstName[20];  
 

      printf("\nFirst name: ");
      scanf("%s", deleteFirstName);

      for (x = 0; x < counter; x++)
      {
         if (strcmp(deleteFirstName, Phonebook[x].fName) == 0) 
         {
                for ( i = x; i < counter - 1; i++ )
               {
                  strcpy(Phonebook[i].fName, Phonebook[i+1].fName); 
                  strcpy(Phonebook[i].lName, Phonebook[i+1].lName); 
                  strcpy(Phonebook[i].phone, Phonebook[i+1].phone); 
               } 
               printf("Record deleted from the phonebook.\n\n");
               --counter; 
               return;
            } 
         
      }    

   printf("That contact was not found, please try again.");
}

void printContactData(Phonebook p){
printf("\nFirst Name: %s\nLast Name: %s \nPhone: %s \n",
		p.fName, p.lName, p.phone);
} 

//search function seraching for char name in the Phonebook contacts array
void search (Phonebook contacts[]) {
	char tempName[30];
	printf("Enter name to search: ");
	scanf("%s", tempName);
	for (int i =0;i<50;i++) {
		if(strcmp(tempName,contacts[i].fName)==0) {
			printContactData(contacts[i]);
		}
	 	else if (strcmp(tempName,contacts[i].fName)!=0) {
			printf("Nothing was found");
		}
}//end of search function
}
//This method prints the entire phonebook with the latest saved records
void printThePhoneBook(Phonebook contacts[]){
	for (int i = 0; i <25; i++) {
	printContactData(contacts[i]);
	}
}
int main(void) {
	
	Phonebook contacts[50];	
	Phonebook * pb;
	pb = (Phonebook*) malloc(sizeof(Phonebook)*100);
	loadFromFile(fileName, contacts);

	int choice;
	while(choice != 5) 
	{
	printf("\n\n\t\tPhonebook App made by Luis Ortiz and Sarthak Sharma \n\n\n");
	printf("Main menu:\n");
	printf("1: Add Records to PhoneBook\n");
	printf("2: Search All PhoneBook\n");
	printf("3: Delete From PhoneBook\n");
	printf("4: Load Full PhoneBook\n");
	printf("Enter a Choice from 1 to 5: ");
	scanf("%d", &choice);
		
		//Switch statement asks for user choice and calls the appropriate method for the particular choice
		switch(choice) 
		{
		case 1: addToContacts(pb); //method to insert data into the linked list
				clrscr(); //method to clear the screen

		break;
		case 2: search(contacts);
				getchar(); //get char before clearing the screen
				getchar();
				clrscr();
				
		break;
		case 3: DeleteEntry(pb);
				getchar();
				getchar();
				clrscr();
		break;
		case 4: printThePhoneBook(contacts);
				getchar();
				getchar();
				clrscr();
		break;
		default:
			printf("\n\nThanks for using the program.\n\n");
			return 0;
		}//end of switch statement
	}//end of while loop

	return 0;
}
