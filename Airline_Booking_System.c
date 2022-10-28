#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<Windows.h>

void reserve(int x);
void cancel();
void display();
void savefile(); 
int s[110];
int rupees[110];
struct airline
{
	char passport[15];
	char name[15];
    char destination[15];
	int seat_num;
	char email[15];
	struct airline *following;
}
*begin, *user1,*dummy; 

void textcolor (int color)
{
    static int __BACKGROUND;

    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


    GetConsoleScreenBufferInfo(h, &csbiInfo);

    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             color + (__BACKGROUND << 4));
}

void main()
{
	int choice;
	begin = user1 = NULL;
	int num = 1;
	do
	{
		
		printf("\n\n\t\t **");
		printf("\n\t\t                   WELCOME TO INTERNATIONAL AIRLINES");
		printf("\n\t\t   *");
		printf("\n\n\n\t\t Please enter your choice from below (1-4):");
		printf("\n\n\t\t 1. Reservation");
		printf("\n\n\t\t 2. Cancel");
		printf("\n\n\t\t 3. DISPLAY RECORDS");
		printf("\n\n\t\t 4. EXIT");
		printf("\n\n\t\t Enter your choice :");



		scanf("%d", &choice);
        fflush(stdin);
		switch (choice)
		{
		case 1:
			reserve(num);
			num++;
			break;
		case 2:
			cancel();
			break;
		case 3:
			display();
			break;
		case 4:
		{
			savefile();
			 break;
		}
		default:
            textcolor(4);
			printf("\n\n\t SORRY INVALID CHOICE!");
			printf("\n\n\t PLEASE CHOOSE FROM 1-4");
			textcolor(15);
		}
		getch();
	} while (choice != 4);
}
void details()
{
	printf("\n\t Enter your passport number:");
	gets(user1->passport);
    fflush(stdin); 
	while(strlen(user1->passport)!=12)
	{
        textcolor(4);
		printf("\t Invalid Passport number.\n");
		printf("\t Please enter your passport number again: ");
		textcolor(15);
		gets(user1->passport); fflush(stdin); 
	}
	printf("\n\t Enter your  name:");
	gets(user1->name);
    fflush(stdin);
	printf("\n\t Enter your email address:");
	gets(user1->email);
    fflush(stdin);
    printf("\n\t Enter the Destination : ");
    gets(user1->destination);
    fflush(stdin);
    printf("\n\t Reconfirm destination->");
    char desti[100];
    scanf("%s",desti);
    FILE *fp = fopen("final_data.csv","r");
if(fp == NULL)
{
textcolor(4);
printf("Cannot open file\n");
textcolor(15);
}
else{
char line[1000];
int count = 0;
int found=-1;
while(fgets(line,1000,fp) != NULL)
{
char *PNR = strtok(line,",");
char *arrival = strtok(NULL,",");
char *departure = strtok(NULL,",");
char *origin = strtok(NULL,",");
char *destination = strtok(NULL,",");
char *cost=strtok(NULL,",");
if(strcmp(destination,desti)== 0)
{count+=1;
printf("Option \t\t\t%d : \t\t\t%s:leaving at \t\t\t%s \t\t\tIST\n",count,PNR,departure);
s[count]=atoi(PNR);
rupees[count]=atoi(cost);
}
}


}
fclose(fp);
}



void reserve(int x)
{
	user1 = begin;
	if (begin == NULL)
	{
		begin = user1 = (struct airline*)malloc(sizeof(struct airline));
		details();
		user1->following = NULL;
		int choice;
		printf("enter choice->");
		scanf("%d",&choice);
		printf("Your Flight PRN is %d",s[choice]);
		int f;
		printf("\nEnter your choice for the following:");
		printf("\n1.BUSINESS CLASS:Additional charges of Rs.12000 will be applied along with the travel expenses");
		printf("\n2.ECONOMy CLASS:Additional charges of Rs.12000 will be applied along with the travel expenses");
		printf("\n3.FIRST CLASS:Additional charges of Rs.12000 will be applied along with the travel expenses");
		scanf("%d",&f);
		if(f==1)
			printf("Your price is %d",rupees[choice]+12000);
		else if(f==2)
			printf("Your price is %d",rupees[choice]+8000);
		else
			printf("Your price is %d",rupees[choice]+4000);
        textcolor(14);
		printf("\n\t Seat booking successful!");
		printf("\n\t your seat number is: Seat A-%d", x);
		textcolor(15);
		user1->seat_num = x;
		return;
	}
	else if (x > 15)
	{
		printf("\n\t\t Seats Full.");
		return;
	}
	else
	{
		while (user1->following)
			user1 = user1->following;
		user1->following = (struct airline *)malloc(sizeof(struct airline));
		user1 = user1->following;
		details();
		user1->following = NULL;
		printf("Enter your choice ->");
        int choice;
        scanf("%d",&choice);
        textcolor(14);
		printf("Your Flight PRN is %d",s[choice]);
		int f;
		printf("\nEnter your choice for the following:");
		printf("\n1.BUSINESS CLASS->");
		printf("\n2.ECONOMIC CLASS->");
		printf("\n3.FIRST CLASS->");
        printf("\n4.PREMIUM ECONOMIC->");
		scanf("%d",&f);
		if(f==1)
			printf("\nYour price is-> %d",rupees[choice]+40000);
		else if(f==2)
			printf("\nYour price is-> %d",rupees[choice]+4000);
		else if(f==3)
			printf("\nYour price is-> %d",rupees[choice]+70000);
        else if(f==4)
			printf("\nYour price is-> %d",rupees[choice]+70000);
        else 
            printf("INVALID CHOICE");
		printf("\n\t Seat booking succesful!\n\n Thank you!!!!");
		printf("\n\t your seat number is: Seat A-%d", x);
		textcolor(15);
		user1->seat_num = x;
		return;
	}
} 

void savefile()
{
	FILE *p = fopen("SS Airline records", "w");
	if (!p)
	{
		printf("\n Error in opening file!");
		return;
	}
	user1 = begin;
	while (user1)
	{
		fprintf(p, "%-15s", user1->passport);
		fprintf(p, "%-15s", user1->name);
		fprintf(p, "%-15s", user1->email);
        fprintf(p, "%-15s", user1->destination);
        fprintf(p, "\n");
		user1 = user1->following;
	}
	printf("\n\n\t Details have been saved to a file (SS Airline records)");
	fclose(p);
}

void display()
{
	user1 = begin;
	while (user1)
	{
        textcolor(5);
		printf("\n\n Passport Number : %-6s", user1->passport);
		printf("\n         name : %-15s", user1->name);
		printf("\n      email address: %-15s", user1->email);
		printf("\n      Seat number: A-%d", user1->seat_num);
        printf("\n     Destination:%-15s", user1->destination);
		printf("\n\n++=====================================================++");
		textcolor(15);
		user1 = user1->following;
	}

}

void cancel()
{
	user1 = begin;
	system("cls");
	char passport[6];
	printf("\n\n Enter passort number to delete record?:");
	gets(passport); fflush(stdin);
	if (strcmp(begin->passport, passport) == 0)
	{
		dummy = begin;
		begin = begin->following;
		free(dummy);
		printf(" Booking has been deleted bearning passport no: %s ",passport);
		return;

	}

	while (user1->following)
	{
		if (strcmp(user1->following->passport, passport) == 0)
		{
			dummy = user1->following;
			user1->following = user1->following->following;
			free(dummy);
			textcolor(4);
			printf(" Booking has been deleted bearing passport number: %s",passport);
			textcolor(15);
			getch();
			return;
		}
		user1 = user1->following;
	}
}