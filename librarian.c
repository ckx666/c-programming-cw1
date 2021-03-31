#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include"book_management.h"
int remove_book(Book book)
{
	BookArray* postLeftNode= bookList;
	BookArray* postNode = bookList->next; 
	
	while(postNode!=NULL && strcmp(postNode->data.Title,book.Title))
	{
		postLeftNode=postNode;
		postNode=postLeftNode->next;

	}
	if(postNode==NULL) 
		return 1;
	else
	{
		postLeftNode->next = postNode->next;
		free(postNode);
		postNode=NULL;
		return 0;
	}

}
int add_book(Book book)
{
	BookArray* new_node = cre_node(book);
	new_node->next= bookList->next;
	bookList->next=new_node;
	return 0; 
}
int countbooklist(BookArray* nodehead)
{
	int Booktotal=0;
	BookArray* pointmove = nodehead->next;
	while(pointmove!=NULL)
	{
		Booktotal++;
		pointmove=pointmove->next;
	}
	Booktotal +=1;
	return Booktotal;
 } 
void librarianview()
{
	char option[100];
	int end = 0;
	char year[5];
	char copy[10];
	int count=0;
	Book tempBook;//temporary varities to store book infomation
	BookArray* result=NULL;//reseach result
	char bookname[100];
	char bookauthor[100];
	while (1)
	{
		printf("\n(logged in as: librarian)");
		printf("\nPlease choose an option\n");
		printf("1) Add a book\n");
		printf("2) Remove a book\n");
		printf("3) Search for books\n");
		printf("4) Display all books\n");
		printf("5) Log out\n");
		printf(" Option:");
		scanf("%s", option);
		switch (atoi(option))
		{
		case 1://title, author, and year to add
			tempBook.id = countbooklist(bookList);   //id
			printf("Enter the Title of the book you wish to add: ");
			while (gets(bookname))
			{
				if (strlen(bookname) > 10)
				{
					printf("too long! Enter the Title of the book you wish to add again: ");
				}
				else
					break;
			}
			strcpy(tempBook.Title, bookname);//name
			result=find_book_by_title(tempBook.Title);
			if(result==NULL)
			{
				printf("Enter the author of the book you wish to add: ");
				while (gets(bookauthor))
				{
					if (strlen(bookauthor) > 10)
					{
						printf("too long! Enter the author of the book you wish to add again: ");
					 } 
			else
					break;
				}
			
			strcpy(tempBook.author, bookauthor);//author
			printf("Enter the year that the book you wish to add was released: ");
			gets(year);
			int i;
			int n=0;
			for(i=0;i<4;i++)
			{
				if(isdigit(year[i]))
				{
						n++;
				}			
				
			}
			if(n==4)//limit the year, only the 4 number is valid
			{
				tempBook.year = atoi(year);
				printf("Enter the number of copies of the book you wish to add:");
				while (gets(copy))
				{
					if (strlen(copy) > 10)
					{
						printf("too much! Enter the number of copies of the book you wish to add again: ");
					}
					else
						break;
				}
				n=0;
				for(i=0;i<10;i++)
				{
					if(isalpha(copy[i]))
					{
						n++;
					}
				}
				if(n==0)
				{
						FILE *book1;
						tempBook.copies = atoi(copy);
						tempBook.in_copies=tempBook.copies;
						if(add_book(tempBook)==0){
							if(store_books(book1)==0)
							{
								printf("Add book successfully!\n");
							}
							else
							{
								printf("Add book unsuccessfully!\n");
							}
							
						}
						else
						{
							printf("Add book unsuccessfully!\n");
						}
						
					}
					else
					{
					printf("Sorry, you attempted to add an invalid book, please try again.\n");
					}
				}
				else
				{
					printf("Sorry, you attempted to add an invalid book, please try again.\n");
				}
				
				}
				else
				{
					printf("Enter the number of copies of the book you wish to add:");//if the mane is the same, just add the copies
					while (gets(copy))
					{
						if (strlen(copy) > 10)
						{
							printf("too much! Enter the number of copies of the book you wish to add again: ");
						}
						else
							break;
					}
					int n=0;
					int i;
					for(i=0;i<10;i++)
					{
						if(isalpha(copy[i]))
						{
						n++;
						}
					}
					if(n==0)
					{
				
						tempBook.copies = atoi(copy);
						result->data.copies+=tempBook.copies;
						tempBook.in_copies=tempBook.copies;
						saveFile("bookinfo1.txt",bookList);
						printf("Add book successfully!\n");
					}
					else
					{
					printf("Sorry, you attempted to add an invalid book, please try again.\n");//feedback massages
					}
				}
			break;
		case 2:
			printf("\n");
			printf("Enter the Title of the book you wish to remove:");// to remove
			scanf("%s",tempBook.Title);
			result=searchByName(bookList,tempBook.Title);
			if(result==NULL){
				printf("\nCannot find this book! So cannot remove!\n");
			}
			else if(result->data.copies!=result->data.in_copies)//if the book is loaned , cnanot remove. By compare the initial copies with the resent one
			{
				printf("Can not Remove! Because it is on loan!\n");
			}
			else
			{
				FILE *book2;
				if(remove_book(tempBook)==0){
					if(store_books(book2)==0)
							{
							printf("Remove book successfully!\n");
							}
							else
							{
								printf("Remove book unsuccessfully!\n");
							}
							
				}
				else
				{
							printf("Remove book unsuccessfully! ");//feedback massages
				}
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
			break;
		}
		if (end == 1)
			break;
	}
}
