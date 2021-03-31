#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include"book_management.h"
#include"other.c"
#include"log_reg.c"
#include"search.c"
#include"librarian.c"
#include"user.c"
//BookArray* cre_head()
//{
//	BookArray* nodehead = (BookArray*)malloc(sizeof(BookArray));
//	nodehead->next=NULL;
//	return nodehead; 
//} 
// 
//BookArray* cre_node(Book data)
//{
//	BookArray* new_node = (BookArray*)malloc(sizeof(BookArray));
//	new_node->data= data;
//	new_node->next=NULL;
//	return new_node;
//}
//void addByName(BookArray* nodehead, Book data)
//{
//	BookArray* new_node = cre_node(data);
//	new_node->next= nodehead->next;
//	nodehead->next=new_node;
//}
//void removeByName(BookArray* nodehead, char *bookName)
//{
//	BookArray* leftNode= nodehead;
//	BookArray* postNode = nodehead->next;
//	while(postNode!=NULL && strcmp(postNode->data.Title,bookName))
//	{
//		leftNode=postNode;
//		postNode=leftNode->next;
//
//	}
//	//search result
//	
//	if(postNode==NULL) 
//		return;
//	else
//	{
//		leftNode->next = postNode->next;
//		free(postNode);
//		postNode=NULL;
//	}
// }
//BookArray* searchByName(BookArray* nodehead, char *bookName)
//{
//	BookArray* postNode = nodehead->next;
//	while(postNode!=NULL && strcmp(postNode->data.Title,bookName))
//	{
//		postNode = postNode->next;
//	}
//	return postNode;
//}
//void displaythebook(BookArray* nodehead)
//{
//	BookArray* pointmove = nodehead->next;
//	printf("id\tTitle\tAuthors\tyear\tcopies\n");
//	while(pointmove!=NULL)
//	{
//		printf("%d\t%s\t%s\t%d\t%d\n", pointmove->data.id, pointmove->data.Title, pointmove->data.author,pointmove->data.year,pointmove->data.copies);
//		pointmove=pointmove->next;
//	}
//}
////file operation
////write
//void saveFile(const char* fileName,BookArray* nodehead)//store user's infomation on a separate file(username file)
//{
//	FILE *fp=fopen(fileName,"w");
//BookArray* pointmove = nodehead->next;
//	while(pointmove!=NULL)
//	{
//		fprintf(fp,"%d\t%s\t%s\t%d\t%d\n", pointmove->data.id, pointmove->data.Title, pointmove->data.author,pointmove->data.year,pointmove->data.copies);
//		pointmove=pointmove->next;
//	}
//	fclose(fp); 
// } 
// //
//int store_books(FILE *file){//store book infomation on a separate file(bookinfo1)
//		file = fopen("bookinfo1.txt","w");
//		BookArray* pointmove =bookList->next;
//		while(pointmove!=NULL)
//		{
//		fprintf(file,"%d\t%s\t%s\t%d\t%d\n", pointmove->data.id, pointmove->data.Title, pointmove->data.author,pointmove->data.year,pointmove->data.copies);
//		pointmove=pointmove->next;
//		}
//	fclose(file); 
//	return 0;
//}
////read
//void readFile(const char* fileName, BookArray* nodehead)//read user's infomation on a separate file(username file)
//{
//	FILE *fp=fopen(fileName,"r");//if not exist then create
//	if(fp==NULL)
//	{//if open the first time then create
//		fp=fopen(fileName,"w+");
//	}
//	Book tempData;
//	while (fscanf(fp,"%d\t%s\t%s\t%d\t%d\n", &tempData.id, tempData.Title, tempData.author, &tempData.year, &tempData.copies)!=EOF)
//	{//insert into the head
//		addByName(bookList, tempData);
//	} 
//	fclose(fp); 
// }
//int load_books(FILE *file){//read book infomation on a separate file(bookinfo1)
//	file =fopen("bookinfo1.txt", "r");//if open the first time then create
//	Book tempData;
//	if(file==NULL)
//	{//if not exist then create
//		file=fopen("bookinfo1.txt","w+");
//	}
//	while (fscanf(file,"%d\t%s\t%s\t%d\t%d\n", &tempData.id, tempData.Title, tempData.author, &tempData.year, &tempData.copies)!=EOF)
//	{
//		addByName(bookList, tempData);//insert into the head
//	} 
//	fclose(file); 
//	return 0;
//}
// void menu()//print out the main menu
//{
//	printf("\nPlease choose an option\n");
//	printf("1) Register an account\n");
//	printf("2) Login\n");
//	printf("3) Search for books\n");
//	printf("4) Display all books\n");
//	printf("5) Quit\n");
//	printf(" Option: ");
//}
//
//void cmd()//the main system
//{
//	char option[100];
//	scanf("%s", option);
//	getchar();
//	switch (atoi(option))
//	{
//		case 1:
//			if(registermenu()==1)
//			{
//				printf("Registered library account successfully!\n");
//			}
//			break;
//		case 2:
//			if(loginmenu()!=1)
//			{
//				printf("Username is not existing, please register first!\n");
//			}
//			break;
//		case 3:
//			searchbook();
//			break;
//		case 4:
//			displaythebook(bookList);
//			break;
//		case 5:
//			printf("Thank you for using the library!\n");
//			printf("Goodbye!");
//			exit(0);
//			break;
//		default:
//			printf("Sorry, the option you entered was invalid, please try again.\n");
//			break;
//		}
//}

int main()
{
	int usercount;
	FILE *fp;
	FILE *book;
	bookList= cre_head();
	if(load_books(book)!=0)
	{
		printf("load_books fail!\n");
	}
	head = (struct useraccount *)malloc(sizeof(struct useraccount));
	fp = fopen("users", "a+");
	fclose(fp); 
	end = head;
	 struct useraccount *p;
	FILE *fp1;
	p = head;
	fp1 = fopen("users", "ab+");
	while (fread(p,sizeof(struct useraccount),1,fp1))
	{
		if (p->next != NULL)
		{
			p = (struct useraccount  *)malloc(sizeof(struct useraccount ));
			end->next = p;
			end = p;
			end->next = NULL;
		}
	}
	while (1)
	{
		menu();
		cmd();
	}
	return 0;
}
