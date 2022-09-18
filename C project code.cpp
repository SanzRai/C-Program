#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ENTER 13
#define TAB 9
#define BCKSPC 8

struct person
{
    char name[30];
    char country_code[4];
    char mble_no[20];
    char sex[8];
    char mail[100];
};

// Defining person data type.
typedef struct person person;

// All function declaration.
void remove_all();
void print_menu();
void add_person();
void list_record();
void search_person();
void remove_person();
void update_person();
void take_input(person *p);

char takepassword(char pwd[20]){
	int i;
	char ch;
	while(1){
		ch =getch();
		if(ch == ENTER || ch == TAB){
			pwd[i] = '\0';
			break;
		}
		else if(ch == BCKSPC){
			if(i>0){
				i--;
				printf("\b \b");
			}
		}
		else{
			pwd[i++] = ch;
			printf("* \b");
			
		}
	}
}

// Program starts here.
int main()
{
	int w=0;
	char username[20]="sanjina",uname[20];
	char password[20]="raee",pas[20];
	top:
	printf("\t\t\t\t	=====================================\n");
	printf("\t\t\t\t	||------------Login Page-----------||\n");
	printf("\t\t\t\t	=====================================\n");
	printf("\nEnter username\t");
	scanf("%s",&uname);
	printf("\nEnter password\t");
	takepassword(pas);
	if(strcmp(uname,username)==0&&strcmp(pas,password)==0){
		printf("\n\nlogin success");
		getch();
		
	}
	else{
		printf("\n\nlogin is not sucessful try again\n");
		
		getch();
		while(w<2){
			w++;
			system("cls");
			goto top;
		}
		exit(0);
			
	}
    start();
    
    return 0;
}

// This function will start our program.
int start()
{
    int choice;
    while(1)
    {
        print_menu();
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                list_record();
                getchar();
                getchar();
                break;
            case 2:
                add_person();
                getchar();
                getchar();
                break;
            case 3:
                search_person();
                getchar();
                getchar();
                break;
            case 4:
                remove_person();
                getchar();
                getchar();
                break;
            case 5:
                update_person();
                getchar();
                getchar();
                break;
            case 6:
                remove_all();
                getchar();
                getchar();
                break;
            default :
                system("cls");
                printf("Thanks for using phonebook visit again : )\n");
                getchar();
                getchar();
                exit(1);
        }
    }
}

// This will print main menu.
void print_menu()
{
    system("cls");
    printf("\t\t****************************************************************\n");
    printf("\t\t*                  Welcome TO My phone book                    *\n");
    printf("\t\t****************************************************************\n\n");
    printf("\t\t\t1) list record\n\n");
    printf("\t\t\t2) Add person\n\n");
    printf("\t\t\t3) Search person Details\n\n");
    printf("\t\t\t4) Remove person\n\n");
    printf("\t\t\t5) Update person\n\n");
    printf("\t\t\t6) Delete all contacts\n\n");
    printf("\t\t\t7) exit Phonebook\n\n\n");

    printf("\t\t\t\tEnter your Choice : ");
}

// This function will add contact into phonebook.
void add_person()
{
	//no records
    system("cls");
    FILE *fp;
    fp = fopen("phonebook_db", "ab+");
    if (fp == NULL)
    {
        printf("Error in file opening, Plz try again !\n");
        printf("Press any key to continue....\n");
        return;
    }
    
    else
    {
        person p;
        take_input(&p);
        fwrite(&p, sizeof(p), 1, fp);
        fflush(stdin);
        fclose(fp);
        system("clear");
        printf("Record added Successfully\n");
        printf("Press any key to continue ....\n");

    }
}

// By this we take contact information.
void take_input(person *p)
{
    system("cls");
    // This getchar is for taking \n occured by previous functions.
    // So that scanset in scanf will work properly.
    getchar();
    printf("Enter name : ");
    // Here we are using scanset '^' - >  until get
    scanf("%[^\n]s",p->name);

    printf("Enter country code : ");
    scanf("%s",p->country_code); 
    
    printf("Enter mobile no : ");
    scanf("%s",p->mble_no); 

    printf("Enter sex : ");
    scanf("%s",p->sex); 
    
    printf("Enter email : ");
    scanf("%s",p->mail); 
}

// This function will list contact available in phonebook.
void list_record()
{
	//no records
    system("cls");
    FILE *fp;
    fp = fopen("phonebook_db", "rb");
    if (fp == NULL)
    {
        printf("Error in file opening, Plz try again !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        person p;
        printf("\n\t\t\t\t******************************************************************************\n");
        printf("\t\t\t\t*                  Here is all records listed in phonebook                   *\n");
        printf("\t\t\t\t******************************************************************************\n\n\n");
        printf("  NAME\t\t\t\t   COUNTRY CODE\t\t    PHONE NO\t\t    SEX\t\t             EMAIL\n");
        printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
        // fseek(fp,-(sizeof(p)*2L),2);
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            int i;
            int len1 = 40 - strlen(p.name);
            int len2 = 19 - strlen(p.country_code);
            int len3 = 15;
            int len4 = 21 - strlen(p.sex);
            printf("%s",p.name);
            for(i=0;i<len1;i++) printf(" ");

            printf("%s",p.country_code);
            for(i=0;i<len2;i++) printf(" ");

            printf("%s",p.mble_no);
            for(i=0;i<len3;i++) printf(" ");

            printf("%s",p.sex);
            for(i=0;i<len4;i++) printf(" ");

            printf("%s",p.mail);
            printf("\n");
            fflush(stdin);
        }
        fflush(stdin);
        fclose(fp);
        printf("\n\nPress any key to continue....\n");
        
    }
}

// This function will search contact in phonebook.
void search_person()
{
    system("cls");
    char phone[20];
    printf("Enter Phone number of the person you want to search : ");
    scanf("%s",&phone);

    FILE *fp;
    fp = fopen("phonebook_db", "rb");
    if (fp == NULL)
    {
        printf("Error in file opening, Plz try again !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        int flag = 0;
        person p;
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(strcmp(p.mble_no,phone)==0)
            {
                printf("  NAME\t\t\t\t   COUNTRY CODE\t\t    PHONE NO\t\t    SEX\t\t             EMAIL\n");
                printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
                int i;
                int len1 = 40 - strlen(p.name);
                int len2 = 19 - strlen(p.country_code);
                int len3 = 15;
                int len4 = 21 - strlen(p.sex);
                printf("%s",p.name);
                for(i=0;i<len1;i++) printf(" ");

                printf("%s",p.country_code);
                for(i=0;i<len2;i++) printf(" ");

                printf("%s",p.mble_no);
                for(i=0;i<len3;i++) printf(" ");

                printf("%s",p.sex);
                for(i=0;i<len4;i++) printf(" ");

                printf("%s",p.mail);
                printf("\n");

                flag = 1;
                break;
            }
            else continue;
            // fflush(stdin);
        }
        if(flag == 0) 
        {
            system("cls");
            printf("Person is not in the Phonebook\n");
        }
        fflush(stdin);
        fclose(fp);
        printf("\n\nPress any key to continue....\n");
    }

}

// This function will remove contact from phonebook.
void remove_person()
{
    system("cls");
    char phone[20];
    printf("Enter Phone number of the person you want to remove from phonebook : ");
    scanf("%s",&phone);

    FILE *fp,*temp;
    fp = fopen("phonebook_db", "rb");
    temp = fopen("temp","wb+");
    if (fp == NULL)
    {
        printf("Error in file opening, Plz try again !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        person p;
        int flag = 0;
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(strcmp(p.mble_no,phone)==0)
            {
                system("cls");
                printf("Person removed successfully\n");
                flag = 1;
            }
            else fwrite(&p,sizeof(p),1,temp);
            fflush(stdin);
        }
        if(flag == 0)
        {
            system("cls");
            printf("No record found for %d number\n",phone);
        }
        fclose(fp);
        fclose(temp);
        remove("phonebook_db");
        rename("temp","phonebook_db");
        fflush(stdin);
        printf("Press any key to continue....\n");
        
    }

}

// This function will update contact information.
void update_person()
{

    system("cls");
    char phone[20];
    printf("Enter Phone number of the person you want to update details : ");
    scanf("%s",&phone);

    FILE *fp,*temp;
    fp = fopen("phonebook_db", "rb");
    temp = fopen("temp","wb+");
    if (fp == NULL)
    {
        printf("Error in file opening, Plz try again !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        int flag = 0;
        person p;
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(strcmp(p.mble_no,phone)==0) 
            {   
                take_input(&p);
                fwrite(&p, sizeof(p), 1, temp);
                system("clear");
                printf("Data updated successfully\n");
                flag = 1;
            }
            else fwrite(&p,sizeof(p),1,temp);
            fflush(stdin);
        }
        if(flag == 0)
        {
            system("cls");
            printf("No record found for %d number\n",phone);
        }
        fclose(fp);
        fclose(temp);
        remove("phonebook_db");
        rename("temp","phonebook_db");
        fflush(stdin);
        printf("Press any key to continue....\n");
    }
}

// This function will clear all the data of phonebook.
void remove_all()
{
    char choice;
    system("cls");
    remove("./phonebook_db");
    printf("All data in the phonebook deleted successfully\n");
    printf("Press any key to continue ... \n");
}
