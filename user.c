#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include"book_management.h"

void userfunction(struct useraccount *pc)
{
	char option[100];
	int end = 0;
 	Book tempBook;//temp store
	BookArray* result=NULL;//search result
	BookArray* result2=NULL;//search result
	user_Name = NULL;
	user_Name= cre_head();
	readuserFile(userName);//write the infomation into the user's own file
	while (1)
	{
		printf("\n(logged in as: %s)\n", userName1);
		printf("Please choose an option\n");
		printf("1) Borrow a book\n");
		printf("2) Return a book\n");
		printf("3) Search for books\n");
		printf("4) Display all books\n");
		printf("5) Log out\n");
		printf(" Option: ");
		scanf("%s", option);
		switch (atoi(option))
		{
		case 1:
			printf("\n");//if exist the number copies -1, else cannot borrow
			printf("Enter the name of the book you wish to borrow£º");	
			scanf("%s",tempBook.Title);
			result=find_book_by_title(tempBook.Title);
			if(result==NULL)
			{
				printf("Do not have this book!");
			}
			else
			{
				result2=searchByName(user_Name,tempBook.Title);
				if(result2==NULL)
				{
					if(result->data.copies>0)
					{
						result->data.copies--;
						saveFile("bookinfo1.txt",bookList);//record the changes of the copies
						strcpy(tempBook.author,result->data.author);
						tempBook.year=result->data.year;
						tempBook.copies=1;
						tempBook.id=result->data.id;
						addByName(user_Name,tempBook);//add the book into the head
						saveFile(userName,user_Name);//save the file
						printf("You have successfully borrowed the book!\n");//feedback message to the user when book borroweded is completed.
						}
					else
					{
						printf("It is lent out! There is no copy of this book at present!\n");
					}
				}
				else
				{
					printf("Sorry, you already have a copy of this book on loan.\n"); //users to borrow just one copy of the same book at a time
				 } 
			}
			break;
		case 2:
			printf("\n");//num+1 
			printf("You have already borrowed these books£º\n");//return books from a list of borrowed books 

			displaythebook(user_Name);
			printf("Enter the name of the book you wish to return£º");	
			scanf("%s",tempBook.Title);
			result=searchByName(user_Name,tempBook.Title);
			if(result==NULL)
			{
				printf("Do not have this book!\n");
			}
			else
			{
				result2=find_book_by_title(tempBook.Title);
				result2->data.copies++;//record the changes of the copies
				saveFile("bookinfo1.txt",bookList);//save the file
				removeByName(user_Name, tempBook.Title);
				saveFile(userName,user_Name);//save the file
				printf("Return book successfully!\n");//feedback message to the user when book returned is completed.
			}
			break;
		case 3:
			searchbook();
			break;
		case 4:
			displaythebook(bookList);
			break;
		case 5:
			end = 1;
			break;
		default:
			printf("Sorry, the option you entered was invalid, please try again.\n");
		}
		if (end == 1)
			break;
	}
}
