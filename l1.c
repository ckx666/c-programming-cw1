//
// Created by ckx on 2021-03-28.
//
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
char userName[100];
int cop_ies[100];
struct bookInfo
{
    int ID;
    char Title[100];
    char Athors[100];
    int year;
    int copies;
    int in_copies;
};
struct Node
{
    struct bookInfo data;
    struct Node *next;
};
struct Node* listbook = NULL;
//创建表头：表头就是一个结构体标量
struct Node* createHead()
{
    //动态申请内存
    struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
    headNode->next=NULL;
    return headNode;
}
struct Node* createNode(struct bookInfo data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data=data;
    newNode->next=NULL;
    return newNode;
}
struct useraccount        //user
{
    int bookcount;
    char username[30];
    char userpassword[30];
    struct useraccount *next;
};

//char librarianname[10]="librarian";
//char librarianpassword[10]="librarian";
char librarianname[10]="1";
char librarianpassword[10]="1";
struct useraccount *head = NULL, *end = NULL;
struct bookstruct  *bookhead = NULL, *bookend = NULL;
int usercount, bookcount;
void userregister();
void userlogin();
void menu();
void cmd();
void readuserfile();
void readbookfile();
void userfunction(struct useraccount *p);
void librarianview();
void writefile(int flag);
void searchbook();
void insertNodeByHead(struct Node* headNode, struct bookInfo data)
{
    struct Node* newNode = createNode(data);
    //必须先连接，再断开
    newNode->next= headNode->next;
    headNode->next=newNode;
}
//
//指定位置删除
void deleteNodeByName(struct Node* headNode, char *bookName)
{
    struct Node* posLeftNode= headNode;
    struct Node* posNode = headNode->next;
    //书籍名字是字符串，字符串比较函数
    while(posNode!=NULL && strcmp(posNode->data.Title,bookName))
    {
        posLeftNode=posNode;
        posNode=posLeftNode->next;

    }
    //讨论查找结果
    if(posNode==NULL)
        return;
    else
    {
        printf("删除成功\n");
        posLeftNode->next = posNode->next;
        free(posNode);
        posNode=NULL;
    }
}
//
struct Node* searchByName(struct Node* headNode, char *bookName)
{
    struct Node* posNode = headNode->next;
    while(posNode!=NULL && strcmp(posNode->data.Title,bookName))
    {
        posNode = posNode->next;
    }
    return posNode;
}
struct Node* searchByAthor(struct Node* headNode, char *authorName)
{
    struct Node* posNode = headNode->next;
    while(posNode!=NULL && strcmp(posNode->data.Athors,authorName))
    {
        posNode = posNode->next;
    }
    return posNode;
}
//struct Node* searchByYear(struct Node* headNode, char *year)
//{
//	struct Node* posNode = headNode->next;
//	while(posNode!=NULL)
//	{
//				char i;
//				sprintf(i,"%d",posNode->data.year);
//				printf("ID\tTitle\tAuthors\tyear\tcopies\n");
//				if(strcmp(i, year)==0)
//				{
//										printf("%d\t%s\t%s\t%d\t%d\n", posNode->data.ID, posNode->data.Title, posNode->data.Athors, posNode->data.year, posNode->data.copies);
//					}
//
//		posNode = posNode->next;
//	}
//	return;
//}
void printList(struct Node* headNode)
{
    struct Node* pMove = headNode->next;
    printf("ID\tTitle\tAuthors\tyear\tcopies\n");
    while(pMove!=NULL)
    {
        printf("%d\t%s\t%s\t%d\t%d\n", pMove->data.ID, pMove->data.Title, pMove->data.Athors,pMove->data.year,pMove->data.copies);
        pMove=pMove->next;
    }
}
void printList1(struct Node* headNode)
{
    int year;
    int i=0;
    struct Node* pMove = headNode->next;
    printf("Please enter year：");
    scanf("%d", &year);
    printf("ID\tTitle\tAuthors\tyear\tcopies\n");
    while(pMove!=NULL)
    {
        if(pMove->data.year==year)
        {

            printf("%d\t%s\t%s\t%d\t%d\n", pMove->data.ID, pMove->data.Title, pMove->data.Athors,pMove->data.year,pMove->data.copies);
            i++;
        }
        pMove=pMove->next;
    }
    if(i==0)
    {
        printf("\nNot found!\n");
    }
}
//void searchByYear(struct Node* headNode, int year)
//{
//	struct Node* pMove = headNode->next;
//	printf("ID\tTitle\tAuthors\tyear\tcopies\n");
//	while(pMove!=NULL)
//	{
//		if(pMove->data.year == year)
//		{
//			printf("%d\t%s\t%s\t%d\t%d\n", pMove->data.ID, pMove->data.Title, pMove->data.Athors,pMove->data.year,pMove->data.copies);
//			pMove=pMove->next;
//		}
//		else
//		{
//			pMove=pMove->next;
//		}
//
//	}
//}

int Booktotal=0;

int countbooklist(struct Node* headNode)
{
    struct Node* pMove = headNode->next;
    while(pMove!=NULL)
    {
        Booktotal++;
        pMove=pMove->next;
    }
    Booktotal++;
    return Booktotal;
}
void deleteNodeName(struct Node* headNode, char *bookName)
{
    struct Node* posLeftNode= headNode;
    struct Node* posNode = headNode->next;
    struct Node* result=NULL;//查找结果
    result=searchByName(listbook,bookName);
    //书籍名字是字符串，字符串比较函数
    while(posNode!=NULL && strcmp(posNode->data.Title,bookName))
    {
        posLeftNode=posNode;
        posNode=posLeftNode->next;

    }
    //讨论查找结果
    if(posNode==NULL)
    {
        printf("not found\n");
        return;
    }

    else
    {
        if(result->data.copies!=cop_ies[result->data.ID])
        {
            printf("Remove unsuccessfully! Because it is on loan!\n");
            return;
        }
        else
        {
            printf("Remove book successfully! ");
            posLeftNode->next = posNode->next;
            free(posNode);
            posNode=NULL;
        }
    }
}
//直接文件操作
//写操做
void saveInfoToFile(const char* fileName, struct Node* headNode)
{
    FILE *fp=fopen(fileName,"w");
    struct Node* pMove = headNode->next;
    while(pMove!=NULL)
    {
        fprintf(fp,"%d\t%s\t%s\t%d\t%d\n", pMove->data.ID, pMove->data.Title, pMove->data.Athors,pMove->data.year,pMove->data.copies);
        pMove=pMove->next;
    }
    fclose(fp);
}
//
//读操作
void readInfoFromFile(const char* fileName, struct Node* headNode)
{
    FILE *fp=fopen(fileName,"r");//第一次打开不存在
    if(fp==NULL)
    {//如果不存在就创建
        fp=fopen(fileName,"w+");
    }
    struct bookInfo tempData;
    while (fscanf(fp,"%d\t%s\t%s\t%d\t%d\n", &tempData.ID, tempData.Title, tempData.Athors, &tempData.year, &tempData.copies)!=EOF)
    {
        insertNodeByHead(listbook, tempData);
    }
    fclose(fp);
}

void menu()
{
    printf("\nPlease choose an option\n");
    printf("1) Register an account\n");
    printf("2) Login\n");
    printf("3) Search for books\n");
    printf("4) Display all books\n");
    printf("5) Quit\n");
    printf(" Option: ");
}
void userregister()
{
    char username[50];
    char userpassword[50];
    struct useraccount *p;
    p = (struct useraccount *)malloc(sizeof(struct useraccount));
    FILE *fp;

    printf("Please enter a username: ");
    while (gets(username))
    {
        if (strcmp(username, librarianname) == 0)
        {
            printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
            printf("Please enter a username: ");
        }
        else if (judge(username))
        {
            printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
            printf("Please enter a username: ");
        }
        else if (strlen(username) < 20 && !judge(username) && strcmp(username, librarianname) != 0)
            break;
        else
        {
            printf("too complex\n");
            printf("Please enter a username: ");
        }
    }
    strcpy(p->username, username);
    printf("Please enter a password: ");
    while (gets(userpassword))
    {
        if (strlen(userpassword) < 20)
            break;
        else
            printf("too complex");
    }
    strcpy(p->userpassword, userpassword);
    p->bookcount = 0;
    end->next = p;
    end = p;
    end->next = NULL;
//	}
//	usercount++;
    fp = fopen("user", "w");
    p = head;
    while (p != NULL)
    {
        fwrite(p, sizeof(struct useraccount), 1, fp);
        p = p->next;
    }
    fclose(fp);
    printf("Registered library account successfully!\n");

}

int judge(char *name)
{
    struct useraccount *p;
    p = head;
    while (p != NULL && usercount != 0)
    {
        if (strcmp(name, p->username) == 0)
            return 1;
        p = p->next;
    }
    return 0;
}

void userlogin()
{
    struct useraccount *p;
    char username[50];
    char str[]=".txt";
    char userpassword[50];
    int exist = 0;

    FILE *fp;
    p = head;
    printf("Please enter your username: ");
    scanf("%s", username);
//	gets(username);
    printf("Please enter your password: ");
    scanf("%s", userpassword);
//	gets(userpassword);

    while (p != NULL)
    {
        if (strcmp(username, librarianname) == 0)
        {
            exist = 1;
            while (strcmp(userpassword, librarianpassword) != 0)
            {
                printf("Password is wrong! Please enter again!\n");
                printf("Please enter your password again: ");
//				gets(librarianpassword);
                scanf("%s", librarianpassword);
            }
            printf("\n(logged in as: librarian)\n");
            librarianview(p);
        }
        if (strcmp(p->username, username) == 0)
        {
            exist = 1;
            while(strcmp(p->userpassword, userpassword) != 0)
            {
                printf("Password is wrong! Please enter again!\n");
                printf("Please enter your password again: ");
                scanf("%s", userpassword);
//				gets(userpassword);
            }
            printf("\n(logged in as: %s)\n", p->username);
            strcpy(userName,p->username);
            strcat(userName,"");
            strcat(userName,str);
//			saveInfoToFile(userName,listbook);
            userfunction(p);
        }
        p = p->next;
    }
    if (exist==0)
    {
        printf("Username is not existing, please register first!\n");
    }
}

void librarianview()
{
    int option;
    int end = 0;
    char year[5];
    char copy[10];
    int count=0;
    struct bookInfo tempBook;//临时的变量存储书籍信息
    struct Node* result=NULL;//查找结果
//	Book tempBook;//临时的变量存储书籍信息
//	BookArray* result=NULL;//查找结果
    char bookname[100];
    char bookauthor[100];
    while (1)
    {
        printf("\nPlease choose an option\n");
        printf("1) Add a book\n");
        printf("2) Remove a book\n");
        printf("3) Search for books\n");
        printf("4) Display all books\n");
        printf("5) Log out\n");
        printf(" Option:");
        scanf("%d", &option);
        getchar();
        switch (option)
        {
            case 1:
//			add();

//			count =  + 1;
                tempBook.ID = countbooklist(listbook);

                printf("Enter the title of the book you wish to add: ");
////			scanf("%s", tempBook.Title);
                while (gets(bookname))
                {
                    if (strlen(bookname) > 10)
                    {
                        printf("too long! Enter the title of the book you wish to add again: ");
                    }
                    else
                        break;
                }
                strcpy(tempBook.Title, bookname);
                result=searchByName(listbook,tempBook.Title);
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

                    strcpy(tempBook.Athors, bookauthor);
//	//			scanf("%s", tempBook.Athors);
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
                    if(n==4)
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

                            tempBook.copies = atoi(copy);
//						cop_ies[tempBook.ID]=tempBook.copies;
                            tempBook.in_copies=tempBook.copies;
//						insertNodeByHead(listbook,tempBook);
                            if(add_book(tempBook)==0){
                                saveInfoToFile("bookinfo1.txt",listbook);
                                printf("Add book successfully!\n");
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
                        saveInfoToFile("bookinfo1.txt",listbook);
                        printf("Add book successfully!\n");
                    }
                    else
                    {
                        printf("Sorry, you attempted to add an invalid book, please try again.\n");
                    }
                }
                break;
            case 2:
//			deletebook();
                printf("\n");
                printf("Enter the title of the book you wish to remove:");
                scanf("%s",tempBook.Title);
                result=searchByName(listbook,tempBook.Title);

                if(result->data.copies!=result->data.in_copies)
                {
                    printf("Remove unsuccessfully! Because it is on loan!\n");
                }
                else
                {
//				deleteNodeName(listbook, tempBook.Title);
                    if(remove_book(tempBook)==0){
                        saveInfoToFile("bookinfo1.txt",listbook);
                        printf("Remove book successfully!\n");
                    }
                    else
                    {
                        printf("Remove book unsuccessfully! ");
                    }
                }

                break;
            case 3:
//			searchbook();
//			printf("输入查找的书名：");
//			scanf("%s", tempBook.Title);
//			result=searchByName(listbook,tempBook.Title);
//			if(result==NULL)
//			{
//				printf("未找到");
//			}
//			else
//			{
//				printf("ID\tTitle\tAuthors\tyear\tcopies\n");
//				printf("%d\t%s\t%s\t%d\t%d\n", result->data.ID, result->data.Title, result->data.Athors, result->data.year, result->data.copies);
//			}
                break;
            case 4:
                searchbook();
//			printList(listbook);
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
int remove_book(struct bookInfo data)
{
    deleteNodeName(listbook, data.Title);
    return 0;
}
int add_book(struct bookInfo data)
{
    insertNodeByHead(listbook, data);
    return 0;
}

void cmd()
{
    int option;
    struct bookInfo tempBook;//临时的变量存储书籍信息
    struct Node* result=NULL;//查找结果
    scanf("%d", &option);
    getchar();
    switch (option)
    {
        case 1:
            userregister();
            break;
        case 2:
            userlogin();
            break;
        case 3:
//			printf("查找书籍\n");
//			printf("输入查找的书名：");
//			scanf("%s", tempBook.Title);
//			result=searchByName(listbook,tempBook.Title);
//			if(result==NULL)
//			{
//				printf("未找到");
//			}
//			else
//			{
//				printf("ID\tTitle\tAuthors\tyear\tcopies\n");
//				printf("%d\t%s\t%s\t%d\t%d\n", result->data.ID, result->data.Title, result->data.Athors, result->data.year, result->data.copies);
//			}
            searchbook();
            break;
        case 4:
            printList(listbook);
            break;
        case 5:
            printf("Thank you for using the library!\n");
            printf("Goodbye!");
            exit(0);
            break;
        default:
            printf("Sorry, the option you entered was invalid, please try again.\n");
            break;
    }
}

void searchbook()
{
    int end =0;
    struct bookInfo tempBook;//临时的变量存储书籍信息
    struct Node* result=NULL;//查找结果
    printf("\nPlease choose an option\n");
    printf("1) Find books by title\n");
    printf("2) Find books by author\n");
    printf("3) Find books by year\n");
    printf("4) Return to previous menu\n");
    printf(" Option: ");
    int option;
    scanf("%d", &option);
    getchar();
//	while(1){
    switch (option)
    {
        case 1:
            printf("Please enter title：");
            scanf("%s", tempBook.Title);
            result=searchByName(listbook,tempBook.Title);
            if(result==NULL)
            {
                printf("Not found!");

                while (1)
                {
                    printf("Input 1 to leave: ");
                    scanf("%d", &end);
                    if (end == 1)
                        break;
                }
            }
            else
            {
                printf("ID\tTitle\tAuthors\tyear\tcopies\n");
                printf("%d\t%s\t%s\t%d\t%d\n", result->data.ID, result->data.Title, result->data.Athors, result->data.year, result->data.copies);
            }
            break;
        case 2:
            printf("Please enter author：");
            scanf("%s", tempBook.Athors);
            result=searchByAthor(listbook,tempBook.Athors);
            if(result==NULL)
            {
                printf("Not found!");
                end=1;
            }
            else
            {
                printf("ID\tTitle\tAuthors\tyear\tcopies\n");
                printf("%d\t%s\t%s\t%d\t%d\n", result->data.ID, result->data.Title, result->data.Athors, result->data.year, result->data.copies);
            }
            break;
        case 3:
            printList1(listbook);
//			printList(listbook);
//			if(result==NULL)
//			{
//				printf("Not found!");
//				end=1;
//			}
//			else
//			{
//				printf("ID\tTitle\tAuthors\tyear\tcopies\n");
//				printf("%d\t%s\t%s\t%d\t%d\n", result->data.ID, result->data.Title, result->data.Athors, result->data.year, result->data.copies);
//			}
            break;
        case 4:
            end = 1;
            break;
        default:
            printf("Sorry, the option you entered was invalid, please try again.\n");
            break;
    }
//		if (end == 1)
//				break;
//	}
}
void userfunction(struct useraccount *p)
{
    int option;
    int end = 0;
    struct bookInfo tempBook;//临时的变量存储书籍信息
    struct Node* result=NULL;//查找结果
    struct Node* result2=NULL;//查找结果
    struct Node* user_Name = NULL;
    user_Name= createHead();
    readInfoFromFile(userName, user_Name);
    while (1)
    {
        printf("Please choose an option\n");
        printf("1) Borrow a book\n");
        printf("2) Return a book\n");
//		printf("3) 已借阅书籍信息\n");
        printf("3) Search for books\n");
        printf("4) Display all books\n");
        printf("5) Log out\n");
        printf(" Option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                printf("\n");//存在可以借阅num-1， 不存在借阅失败
                printf("Enter the name of the book you wish to borrow：");
                scanf("%s",tempBook.Title);
                result=searchByName(listbook,tempBook.Title);
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
                            saveInfoToFile("bookinfo1.txt",listbook);
//						saveInfoToFile("bookinfo1.txt",listbook);
                            strcpy(tempBook.Athors,result->data.Athors);
                            tempBook.year=result->data.year;
                            tempBook.copies=1;
                            tempBook.ID=result->data.ID;
                            insertNodeByHead(user_Name,tempBook);
                            saveInfoToFile(userName,user_Name);
                            printf("You have successfully borrowed the book!\n");
                        }
                        else
                        {
                            printf("There is no copy of this book at present!\n");
                        }
                    }
                    else
                    {
                        printf("Sorry, you already have a copy of this book on loan.\n");
                    }
                }
                break;
            case 2:
                printf("\n");//当前num+1
                printList(user_Name);
                printf("输入归还的书名：");
                scanf("%s",tempBook.Title);
                result=searchByName(listbook,tempBook.Title);
                if(result==NULL)
                {
                    printf("来源非法\n");
                }
                else
                {

                    result->data.copies++;
                    saveInfoToFile("bookinfo1.txt",listbook);
                    deleteNodeByName(user_Name, tempBook.Title);
                    saveInfoToFile(userName,user_Name);
                    printf("Return book successfully!\n");

                }
                break;
            case 3:
                printList1(listbook);
                break;
            case 4:
                printList(listbook);
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
void readuserfile()
{
    struct useraccount *p;
    FILE *fp;

    p = head;
    fp = fopen("user", "ab+");
    while (fread(p,sizeof(struct useraccount),1,fp))
    {
        if (p->next != NULL)
        {
            p = (struct useraccount *)malloc(sizeof(struct useraccount));

            end->next = p;
            end = p;
            end->next = NULL;
        }
    }
}


int main()
{
    FILE *fp;
    listbook= createHead();
    readInfoFromFile("bookinfo1.txt",listbook);
    head = (struct useraccount *)malloc(sizeof(struct useraccount));
    end = head;
    bookend = bookhead;
    fp = fopen("user", "a+");
    usercount = fread(head, sizeof(struct useraccount), 1, fp);
    fclose(fp);
    end = head;
    readuserfile();
    while (1)
    {
        menu();
        cmd();
    }
    return 0;
}


