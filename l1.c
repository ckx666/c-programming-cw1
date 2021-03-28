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
    //变量规则 使用前必须初始化
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


int registermenu();
int loginmenu();


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
int registermenu()/*Register users. If the username has been used it will print Sorry, registration unsuccessful,
the username you entered already exists and can type an another name or password;
else print Registered library account successfully!*/
{
    char username[50];
    char userpassword[50];
    struct useraccount *pc;
    pc = (struct useraccount *)malloc(sizeof(struct useraccount));
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
    strcpy(pc->username, username);
    printf("Please enter a password: ");
    while (gets(userpassword))
    {
        if (strlen(userpassword) < 20)
            break;
        else
            printf("too complex");
    }
    strcpy(pc->userpassword, userpassword);
    pc->bookcount = 0;
    end->next = pc;
    end = pc;
    end->next = NULL;
//	}
//	usercount++;
    fp = fopen("user", "w");
    pc = head;
    while (pc != NULL)
    {
        fwrite(pc, sizeof(struct useraccount), 1, fp);
        pc = pc->next;
    }
    fclose(fp);
    return 1;
//	printf("Registered library account successfully!\n");

}

int judge(char *name)/*This is to judge whether the username exists.*/
{
    struct useraccount *pc;
    pc = head;
    while (pc != NULL && usercount != 0)
    {
        if (strcmp(name, pc->username) == 0)
            return 1;
        pc= pc->next;
    }
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
                printf("Please enter your password again: ");
                scanf("%s", librarianpassword);
            }
            printf("\n(logged in as: librarian)");
            librarianview(pc);/*go to librarian menu*/
            return 1;
        }
        if (strcmp(pc->username, username) == 0)
        {
            while(strcmp(pc->userpassword, userpassword) != 0)
            {
                printf("Password is wrong! Please enter again!\n");
                printf("Please enter your password again: ");
                scanf("%s", userpassword);
            }
            printf("\n(logged in as: %s)\n", pc->username);
            strcpy(userName,pc->username);/*creat the name for userfile*/
            strcat(userName,"");
            strcat(userName,str);
//			saveInfoToFile(userName,listbook);
            userfunction(pc);/*go to user menu*/
            return 1;
        }
        pc = pc->next;
    }
//	if (exist==0)
//	{
//		printf("Username is not existing, please register first!\n");
//	}
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
                            cop_ies[tempBook.ID]=tempBook.copies;
                            insertNodeByHead(listbook,tempBook);

                            saveInfoToFile("bookinfo1.txt",listbook);
                            printf("Add book successfully!\n");
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
                        cop_ies[tempBook.ID]=tempBook.copies;
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

//			if(result->data.copies!=cop_ies[result->data.ID])
//			{
//				printf("Remove unsuccessfully! Because it is on loan!\n");
//			}
//			else
//			{
                deleteNodeName(listbook, tempBook.Title);
                saveInfoToFile("bookinfo1.txt",listbook);
//				printf("Remove book successfully! ");
//			}

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
            if(registermenu()==1)
            {
                printf("Registered library account successfully!\n");
            }
            break;
        case 2:
            if(loginmenu()!=1)
            {
                printf("Username is not existing, please register first!\n");
            }

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

