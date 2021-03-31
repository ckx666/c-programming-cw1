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
int main()
{
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
