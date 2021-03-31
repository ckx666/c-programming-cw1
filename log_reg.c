#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include"book_management.h"

int registermenu()/*Register users. Check wether the username has been used it (print Sorry, registration unsuccessful, 
the username you entered already exists) and can type an another name or password; 
if not used print Registered library account successfully!*/
{
	char username[50];
	char userpassword[50];
	struct useraccount *pc;
	pc = (struct useraccount *)malloc(sizeof(struct useraccount));
	FILE *fp;
		printf("Please enter a username: ");
		while (gets(username))
		{
			if (strcmp(username, librarianname) == 0)//librarian account check
			{
				printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
				printf("Please enter a username: ");
			}
			else if (judge(username))//tell whether has the same name user account check.
			{
				printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
				printf("Please enter a username: ");
			}
			else if (strlen(username) >= 20)
			{
				printf("too complex\n");
				printf("Please enter a username: ");
			}
			else
					break;
		}
		strcpy(pc->username, username);
		printf("Please enter a password: ");
		while (gets(userpassword))
		{
			if (strlen(userpassword) >= 20)
			{
				printf("too complex\n");
				printf("Please enter a username: ");
			}
			else
				break;
		}
		strcpy(pc->userpassword, userpassword);
//		pc->bookcount = 0;
		end->next = pc;
		end = pc;
		end->next = NULL;
	fp = fopen("users", "w");
	pc = head;
	while (pc != NULL)
	{
		fwrite(pc, sizeof(struct useraccount), 1, fp);//write into the file
		pc = pc->next;
	}
	fclose(fp);
	return 1;

}
int judge(char *name)//tell whether has the same name 
{
		struct useraccount *p;
		p = head;
		int i=0;
		while (p != NULL)//usercount1 != 0
		{
			if (strcmp(name, p->username) == 0)
				i++;
			p = p->next;//search the list
		}
		if(i!=0)
			return 1;
		else
			return 0;
}

int loginmenu()/*User login: Allow registered users to 
login by their username 
and password then display the 
 usermenu. Feedback 
message to the user for a 
wrong username or password. */
{
	struct useraccount *pc;
	char username[50];
	char str[]=".txt";
	char userpassword[50];
	FILE *fp;
	pc = head;
	printf("Please enter your username: ");
	scanf("%s", username);
	printf("Please enter your password: ");
	scanf("%s", userpassword);
	while (pc != NULL)
	{
		if (strcmp(username, librarianname) == 0)/*check librarian account*/
		{
			while (strcmp(userpassword, librarianpassword) != 0)
			{
				printf("Password is wrong! Please enter again!\n");
				printf("Please enter your password again: ");//wrong password
				scanf("%s", librarianpassword);				
			}

			librarianview(pc);/*go to librarian menu*/
			return 1;
		}
		if (strcmp(pc->username, username) == 0)
		{
			while(strcmp(pc->userpassword, userpassword) != 0)
			{
				printf("Password is wrong! Please enter again!\n");
				printf("Please enter your password again: ");//wrong password
				scanf("%s", userpassword);	
			}

			strcpy(userName1,pc->username);/*creat the name for userfile*/
			strcpy(userName,pc->username);/*creat the name for userfile*/
			strcat(userName,"");
			strcat(userName,str);
			userfunction(pc);/*go to user menu*/
			return 1;
		}
		pc = pc->next;
	}
}
