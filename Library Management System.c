#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<windows.h>


struct USER {
	char name[20];
	char ID[15];
	char code[10];
	int day;
	int month;
	int year;
	char date_ret[10];
	int new_day,new_month,new_year;
};
struct BOOKS {
	char bk_id[15];
	char bk_code[10];
};
struct MANAGE {
	char name[50];
	char code[15];
	char auth[25];
	char cat[25];
};

void gotoxy(int x, int y)                //for positioning cursor
{
COORD coord;
coord.X = x;                       // X and Y coordinates
coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void display();  //display function
void issue();
void issue_bk(struct USER *ptr);
void return_bk();
void management();
void viewRecord();
void addBook();
void viewBookRecord();
void deleteBook();
void searchBooks();

//password function
char password(struct USER *ptr); 
char pass[]="user123";
char pass2[]="management123";

//universal struct variables
	struct USER us;
	struct USER *ptr=&us;
	struct BOOKS bk;
	struct BOOKS *ptr2=&bk;
	struct MANAGE mg;
	
//universal file pointers

FILE *ifp;  //input file pointer
FILE *tempfp; // temporary file pointer
FILE *bkfp;  // file for book issued by user 
FILE *temp2fp; // second temporary file pointer
FILE *fptr;  // file pointer for book record.
FILE *temp3fp; //temporary file for book record

//main
main()
{
	int ch;

	while(1)
	{
		display();
		system("cls");
		printf("\n\n1-Student \t\t 2-Management\n\nEnter your choice :");
		scanf("%d",&ch);
		if(ch==1)
		{
			password(ptr);
			system("cls");
			issue();
		}
		else if(ch==2)
			management();
		else 
		{
			Beep(900,300);
			Beep(900,300);
			Beep(900,300);
			printf("\n\n\t\tWrong Input!!!");
			sleep(2);
		}
	}  // end of while
	
}  // end of main

//password function
char password(struct USER *ptr)
{
	int p=0; 
	char pas[20],ch;
	system("cls");

	printf("\nId :");
	scanf("%s",ptr->ID);
	printf("\nPassword:");
   
   for(p=0;p<20;p++)
   {
     	ch=getch();
 		pas[p] = ch;
 		if(ch!=13)
 		{
  			printf("*");
		}
		if(ch==13)
		break;
   }
   	pas[p]='\0'; 
	
	//comparing password
	if(strcmp(pas,pass)==0)
	{
		printf("\n\n\t\t\tLogin Successful!!");
		printf("\n\tpress any key to continue..");
		getch();
	}
	else 
	{
		printf("\n\n\t\t\tLogin UnSuccessful!!\n Try Again..");
		printf("\n\n\t\tpress any key to continue..");
		getch();
		password(ptr);
	}

}



//display
void display()
{
	system("cls");
	int i;
	gotoxy(30,5);	
	for(i=0;i<20;i++)
	{
		usleep(80000);  // sleep(time in seconds)  time in milliseconds
		printf("==");
		if(i==10)
		printf(" e-Library ");
	}
	gotoxy(30,10);
printf("press any key to continue");
getch();
}

void issue()
{
	int choice; 
	system("cls");
		printf("\n1-Issue Book\n2-return book\n3-Search Book\n4-View Book Record\n5-Exit\n");
		printf("\n\nEnter Your Choice :");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
				issue_bk(&us);
				break;
			case 2:
				return_bk();
				break;
			case 3:
				searchBooks();
				break;
			case 4:	
				viewBookRecord();
				break;
			case 5:
				main();
				break;
			default:
				printf("\n\nInvalid Input\nPress Any Key To Continue..!");	
				getch();
				issue();
				
		}
		

	
}
void issue_bk(struct USER *ptr)
{
	char print;
	int f3=0;
	// creating file of issued books
	bkfp=fopen("Books.txt","ab");
		if(bkfp==NULL)
		{
			printf("File Not Found");
			exit(1);
		}	
		// creating file for record os users
	ifp=fopen("Record.txt","ab");
		if(ifp==NULL)
		{
			printf("File Not Found");
			exit(1);
		}	
		
	fseek(ifp,0,SEEK_END);
	system("cls");
	gotoxy(10,2);
	printf("ISSUE BOOK\n");
	printf("\nEnter 4-character Code Of Book :");
	fflush(stdin);
	gets(ptr->code);
	fptr=fopen("BkRec.txt","rb");
	printf("\nDate(DD/MM/YYYY) :  ");
	printf("  -  -    ");
	gotoxy(19,6);
	scanf("%d",&ptr->day);
	gotoxy(23,6);
	scanf("%d",&ptr->month);
	gotoxy(26,6);
	scanf("%d",&ptr->year);
	gotoxy(4,15);
	printf("**********NOTE : Book Should Be Returned witin 7 Days!**********\n");
		//checking dates for return date
	if(us.month==1 || us.month==3 ||  us.month==5 ||  us.month==7 ||  us.month==10 ||  us.month==12 )
	{
		us.new_day=us.day+7;
		if(us.month==12 && us.new_day>31)
		{
			us.new_day=us.new_day-31; // for example if the user chooses date 25, after a week it will 1 of new month.
			us.new_month=1;
			us.new_year++;
		}
		else if(us.new_day>31)
		{
			us.new_day=us.new_day-31; 
			us.new_month=us.month+1;
			us.new_year=us.year;
		}
		else
		{
			us.new_month=us.month;
			us.new_year=us.year;
		}
		
	}
	else if(us.month==4 || us.month==6 ||  us.month==9 ||  us.month==11)
	{
		us.new_day=us.day+7;
		if(us.new_day>30)
		{
			us.new_day=us.new_day-30; 
			us.new_month=us.month+1;
			us.new_year=us.year;
		}
		else
		{
			us.new_month=us.month;
			us.new_year=us.year;
		}
		
	}
	else if(us.month==2)// Month Of Feb
	{
		if(us.year%4==0)  // leap year
		{
			us.new_day=us.day+7;
			if(us.new_day>29)
			{
				us.new_day=us.new_day-29;
				us.new_month=us.month+1;
				us.new_year=us.year;
			}
			else
			{
				us.new_day=us.day;
				us.new_month=us.month;
				us.new_year=us.year;
			}
		}
		else
		{
			us.new_day=us.day+7;
			if(us.new_day>28)
			{
				us.new_day=us.new_day-28;
				us.new_month=us.month+1;
				us.new_year=us.year;
			}
			else
			{
				us.new_month=us.month;
				us.new_year=us.year;
			}
		}
	}
	printf("\nEnter 'p' To Generate Slip. OR Press 0 TO Exit\n");
	print=getch();
	if(print=='p')
	{
		system("cls");
		printf("\n\n******************  RESULT  ******************\n\n");
		printf("\nID :%s\nBook Code :%s\nDATE OF ISSUE: %d/%d/%d\nDATE OF Return: %d/%d/%d ",us.ID,us.code,us.day,us.month,us.year,us.new_day,us.new_month,us.new_year);
		printf("\n\n\t=========================\n\tpress any key to continue\n\t=========================");
		getch();
	}
	else if(print=='0')
	main();
	else 
	{
		Beep(900,300);
		Beep(900,300);
		Beep(900,300);
		printf("\n\n\t\tWrong Input!!!");
		sleep(2);
		issue_bk(&us);
		
	}
	strcpy(bk.bk_id,us.ID);
	strcpy(bk.bk_code,us.code);
	//writing data into files
	fwrite(&us,sizeof(us),1,ifp);
	fwrite(&bk,sizeof(bk),1,bkfp);
//	closing files
	fclose(ifp);
	fclose(bkfp);
	printf("\n\n\t\tInput Successful..");
	sleep(1);

}
void return_bk()
{
	char i_id[20],cd[15];
	int found=0,found2=0;
	
	system("cls");
	gotoxy(10,2);
	printf("RETURN BOOK\n\n");
		
	ifp=fopen("Record.txt","rb");
	if(ifp==NULL)
		{
			printf("error! Cannot Find File..");
			exit(1);
		}
		strcpy(i_id,ptr->ID);
		while(fread(&us,sizeof(us),1,ifp))
		{
	
			if(strcmp(i_id,us.ID)==0)
			{
				found=1;
				printf("\n=======================");
				printf("\nID:%s\nBOOK CODE :%s\nDATE OF ISSUE: %d/%d/%d\nDATE OF Return: %d/%d/%d",i_id,us.code,us.day,us.month,us.year,us.new_day,us.new_month,us.new_year);
    			printf("\n=======================");
			}
		}
		
		tempfp=fopen("Temp.txt","ab");
		temp2fp=fopen("Temp2.txt","ab");
		bkfp=fopen("Books.txt","rb");
		if(tempfp==NULL || bkfp==NULL || temp2fp==NULL)
		{
			printf("error! Cannot Find File..");
			main();
		}
		if(found==1)
		{
			printf("\n\nEnter Code of Book To Return: ");
			scanf("%s",cd);
		}
		rewind(ifp);
		while(fread(&us,sizeof(us),1,ifp))
			{
				
				if(strcmp(cd,us.code)==0)
				{
					printf("\n==================");
					printf("\nID:%s\nBook Code :%s\n",us.ID,us.code);
					printf("\n==================");
					printf("\n\t\t\t\t\tPlease Wait...\n");
					sleep(3);
					printf("\n\n-------------------------\nBook Succesfully Returned..\n-------------------------\n");
					sleep(2);
					printf("\n-------------------------\nYour Record Has Been Updated Successfully..\n-------------------------\n");
					sleep(2);
					printf("\nPress Any Key To Continue..");
					getch();	
				}
//				 deleting the book which has been returned
				else
				{
					fwrite(&us,sizeof(us),1,tempfp);
				}
			} // end of while
			
			rewind(bkfp);
			while(fread(&bk,sizeof(bk),1,bkfp))
			{
				if(strcmp(cd,bk.bk_code)==0)
				{
					found2=1;
				}
				else 
				fwrite(&bk,sizeof(bk),1,temp2fp);					
				
			}
		
		if(found==0 || found2==0)
		{
			Beep(900,300);
			Beep(900,300);
			Beep(900,300);
			printf("\n\n\t\tRecord Not Found!!");
			sleep(2);
		}
		// closing files
		fclose(ifp);
		fclose(tempfp);
		fclose(bkfp);
		fclose(temp2fp);
		//renaming files
		remove("Record.txt");
		rename("Temp.txt","Record.txt");
		remove("Books.txt");
		rename("Temp2.txt","Books.txt");
	
}

// function for management
void management()
{
	int p=0; 
	char pas[20],ch;
	system("cls");
	printf("\nPassword: ");
   
   for(p=0;p<20;p++)
   {
     	ch=getch();
 		pas[p] = ch;
 		if(ch!=13)
 		{
  			printf("*");
		}
		if(ch==13)
		break;
   }
   	pas[p]='\0'; 
	
	//comparing password
	if(strcmp(pas,pass2)==0)
	{
		printf("\n\n\t\t\tLogin Successful!!");
		printf("\n\n\tpress any key to continue..");
		getch();
		
		system("cls");
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(20,5);
		printf("\xDB\xDB\xDB\xDB\xB2 1. View Issue Record ");	
		gotoxy(20,7);
		printf("\xDB\xDB\xDB\xDB\xB2 2. Add Books   ");	
		gotoxy(20,9);
		printf("\xDB\xDB\xDB\xDB\xB2 3.View books");
		gotoxy(20,11);
		printf("\xDB\xDB\xDB\xDB\xB2 4. Delete Books");
		gotoxy(20,13);
		printf("\xDB\xDB\xDB\xDB\xB2 5. Search Book");
		gotoxy(20,15);
		printf("\xDB\xDB\xDB\xDB\xB2 6. Exit");
		
		switch(getch())
		{
			case '1':
				viewRecord();
				break;	
			case '2':
				addBook();
				break;
			case '3':
				viewBookRecord();
				break;
			case '4':
				deleteBook();
				break;		
			case '5':
				searchBooks();
				break;
			case '6':
				main();
				break;
			default:
				printf("\n\nInvalid Input\nPress Any Key To Continue..!");	
				getch();
				management();
				break;
		}  // end of switch
		

	
	}
	else 
	{
		Beep(900,300);
		Beep(900,300);
		Beep(900,300);
		printf("\n\n\t\tLogin UnSuccessful!!\n Try Again..");
		printf("\n\n\n\t\tpress any key to continue..");
		getch();
		management();
	}
	
}  // end of management


//view record of issued books
void viewRecord()
{
	int i=0;
	
	system("cls");
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2   List Of Issued Books  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n\n");
	ifp=fopen("Record.txt","rb");
	rewind(ifp);
	
	printf("ID\t\tBOOK NO.\t\tBOOK CODE\t\t\t\tDATE OF ISSUE \t\t DATE OF RETURN \n\n\n");
	int count;
	for(count=0;count<130;count++)
	printf("~");
	printf("\n\n\n");
	while(fread(&us,sizeof(us),1,ifp))
	{
		printf("  %s\t    %d\t\t\t %s \t\t\t\t%d/%d/%d\t\t\t%d/%d/%d\n\n",us.ID,i+1,us.code,us.day,us.month,us.year,us.new_day,us.new_month,us.new_year); 
	}
	for(count=0;count<130;count++)
	printf("~");
	printf("\n\n\n\t\tPress any key To Continue..");
	getch();
	
	// closing files
	fclose(ifp);
}

// add a  book to record
void addBook()
{
	system("cls");
	char another='Y';
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2   ADD BOOKS   \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	fptr=fopen("BkRec.txt","ab");
	while(another=='Y' || another=='y')
	{
		system("cls");
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 ADD BOOKS\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		printf("\n\n\nEnter Details\n\nBook Name :");
		fflush(stdin);
		scanf("%[^\n]",mg.name);  // %[^\n] is the format specifier to read string with white spaces
		printf("\nBook Code :");
		fflush(stdin);
		scanf("%s",mg.code);
		printf("\nAuthor Of Book :");
		fflush(stdin);
		scanf("%[^\n]",mg.auth);
		printf("\nCategory :");
		fflush(stdin);
		scanf("%s",mg.cat);
	    printf("\n\t\t\t\t\tPlease Wait...\n");
		sleep(3);
		printf("\n\n-------------------------\nBook Succesfully Added..\n-------------------------\n");
		sleep(2);
		printf("\n-------------------------\nYour Record Has Been Updated Successfully..\n-------------------------\n");
		sleep(2);
		
		printf("\n\nAdd More Books?(Y/N)");
		another=getch();
		if(another=='N' || another=='n')
		{
			printf("\n\n\n\t\tPress any key To Continue..");
			getch();	
		}	
		fwrite(&mg,sizeof(mg),1,fptr);  // writing into the file
		
	}  // end of while
	fclose(fptr);
	
}  // end of add books


// view book record
void viewBookRecord()
{
	int i=0;
	system("cls");
	printf("\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2   Books Record   \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	fptr=fopen("BkRec.txt","rb");
	if (fptr==NULL)
	{
		printf("\n\nError!! File Not Found!");
		main();
	}
	rewind(fptr);
	
	
	printf("\n\n\n\n\n\n\nBOOK NO.\t\tCategory\t\tNAME\t\t\tBOOK CODE\t\t\tAuthor\n\n");
	int count;
	for(count=0;count<130;count++)
	printf("-");
	printf("\n\n\n\n");
	//reading from file
	int j=7;
	printf("\n\n\n");
	while(fread(&mg,sizeof(mg),1,fptr))
	{
		gotoxy(2,j+4);
		printf("%d",i+1);
		gotoxy(25,j+4);
		printf("%s",mg.cat);
		gotoxy(45,j+4);
		printf("%s",mg.name);
		gotoxy(76,j+4);
		printf("%s",mg.code);
		gotoxy(105,j+4);
		printf("%s",mg.auth);
		j++;
		i++;
	}
	printf("\n\n\n");
	for(count=0;count<130;count++)
	printf("-");
	printf("\n\nPress Any Key To Continue..");
	getch();
	
	// closing files
	fclose(fptr);
}
// deleting books
void deleteBook()
{
	int found3=0;
	char book_code[15];
	system("cls");
	gotoxy(30,1);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  Delete Book   \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n\n\n");
	
	printf("Enter Book Code To Delete :");
	scanf("%s",book_code);
	
	fptr=fopen("BkRec.txt","rb");
	temp3fp=fopen("Temp3.txt","ab");
	
	rewind(fptr);
	while(fread(&mg,sizeof(mg),1,fptr))
	{
		if(strcmp(book_code,mg.code)==0)
		{
			found3=1;
		}
		else
		fwrite(&mg,sizeof(mg),1,temp3fp);  // writing into the file
	}  //end of while
	
	
		if(found3==0)
		{
			Beep(900,300);
			Beep(900,300);
			Beep(900,300);
			printf("\n\n\t\tRecord Not Found!!");
			sleep(2);
		}
		else
		{
			printf("\n\t\t\t\t\tPlease Wait...\n");
			sleep(3);
			printf("\n\n-------------------------\nBook Succesfully Deleted..\n-------------------------\n");
			sleep(2);
			printf("\n-------------------------\nYour Record Has Been Updated Successfully..\n-------------------------\n");
			sleep(2);
			printf("\nPress Any Key To Continue..");
			getch();	
		}
	
	fclose(fptr);
	fclose(temp3fp);
	remove("BkRec.txt");
	rename("Temp3.txt","BkRec.txt");
	
} // end of delete books

void searchBooks()
{
	char se[30],num;
	int f=0,f2=0,count;
	system("cls");
	printf("\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  Search Book  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n\n");
	
	printf("Enter Code OR Category OF Book :");
	scanf("%s",se);
	FILE *fptr;
	fptr=fopen("BkREc.txt","rb");
		while(fread(&mg,sizeof(mg),1,fptr))
		{
			if(strcmp(se,mg.code)==0 || strcmp(se,mg.cat)==0)
			f2=1;
		}
		if(f2==1)
		{
			for(count=0;count<130;count++)
			printf("-");	
			printf("\n\nBOOK NO.\t\tCategory\t\tNAME\t\t\tBOOK CODE\t\t\tAuthor\n\n");
			for(count=0;count<130;count++)
			printf("-");
		}
		int j=8;
		int i=0;
		f=0;
		rewind(fptr);
	while(fread(&mg,sizeof(mg),1,fptr))
	{
		if(strcmp(se,mg.code)==0 || strcmp(se,mg.cat)==0)
		{
				gotoxy(2,j+2);
				printf("%d",i+1);
				gotoxy(25,j+2);
				printf("%s",mg.cat);
				gotoxy(45,j+2);
				printf("%s",mg.name);
				gotoxy(76,j+2);
				printf("%s",mg.code);
				gotoxy(105,j+2);
				printf("%s",mg.auth);
				j++;
				i++;
				f=1;
		}
	
	}

	if(f==0)
	{
		printf("\n\nErrorr!! Book Not Found!");
		gotoxy(90,j+8);
		printf("Press 0 To Exit");
		printf("\n\nPress Any Key To Continue..");
		num=getch();	
		if(num=='0')
		main();
		else 
		searchBooks();
	}
//	closing file
		fclose(fptr);
		
		printf("\n\nPress Any Key To Continue..");
		getch();	
	
//end of searchbook	
}  




