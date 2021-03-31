#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include"book_management.h"
void searchbook()
{
	int end =0;
	int j;
	Book tempBook;//a tempotary varies to store the book
	BookArray* result=NULL;//result of rearch
	while(1){	
	printf("\nPlease choose an option\n");
	printf("1) Find books by Title\n");
	printf("2) Find books by author\n");
	printf("3) Find books by year\n");
	printf("4) Return to previous menu\n");
	printf(" Option: ");
	char option[100];
	scanf("%s", option);

	switch (atoi(option))
	{
		case 1:
			printf("Please enter Title£º");
			scanf("%s", tempBook.Title);
			result=find_book_by_title(tempBook.Title);
			if(result==NULL)
			{
				printf("\nNot found!\n");
			}
			else
			{
				printf("id\tTitle\tAuthors\tyear\tcopies\n");
				printf("%d\t%s\t%s\t%d\t%d\n", result->data.id, result->data.Title, result->data.author, result->data.year, result->data.copies);
			}
			break;

		case 2:
			printf("Please enter author£º");
			scanf("%s", tempBook.author);
			find_book_by_author(tempBook.author);
			break;
		case 3:
			printf("Please enter year£º");
			scanf("%i", &tempBook.year);	
			find_book_by_year(tempBook.year);
			break;
		case 4:
			end = 1;
			break;
		default:
			printf("Sorry, the option you entered was invalid, please try again.\n");
			break;
		}
		if (end == 1)
				break;
	}	
}







BookArray* find_book_by_title (const char *title){
		BookArray* postNode = bookList->next;
		while(postNode!=NULL && strcmp(postNode->data.Title, title))
		{
		postNode = postNode->next;
		}
		return postNode;
}
BookArray*  find_book_by_author (const char *author){
	BookArray* Movepoint = bookList->next;
	int i = 0;
	

	while(Movepoint!=NULL)//if one author write many books
	{
		
		if(strcmp(Movepoint->data.author, author)==0)
		{
			i++;
		}
		Movepoint=Movepoint->next;
	}
	Movepoint = bookList->next;
	if(i==0)
	{
		printf("\nNot found!\n");
	}
	else
	{
		printf("id\tTitle\tAuthors\tyear\tcopies\n");
		while(Movepoint!=NULL)//if one author write many books
	{
		
		if(strcmp(Movepoint->data.author, author)==0)
		{
			
			printf("%d\t%s\t%s\t%d\t%d\n", Movepoint->data.id, Movepoint->data.Title, Movepoint->data.author,Movepoint->data.year,Movepoint->data.copies);
		}
		Movepoint=Movepoint->next;
	}
	}
}
BookArray* find_book_by_year (unsigned int year)
{
	BookArray* Movepoint = bookList->next;
	int i = 0;
	

	while(Movepoint!=NULL)
	{
		if(Movepoint->data.year==year)//if many books have the same year
		{
			i++;
		}
		Movepoint=Movepoint->next;
	}
	Movepoint = bookList->next;
	if(i==0)
				{
					printf("\nNot found!\n");
				}	
	else{
			printf("id\tTitle\tAuthors\tyear\tcopies\n");
			while(Movepoint!=NULL)
	{
		if(Movepoint->data.year==year)//if many books have the same year
		{
			
			printf("%d\t%s\t%s\t%d\t%d\n", Movepoint->data.id, Movepoint->data.Title, Movepoint->data.author,Movepoint->data.year,Movepoint->data.copies);
		}
		Movepoint=Movepoint->next;
	}
	}
}
