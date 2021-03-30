//
// Created by ckx on 2021-03-28.
//
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
//#include"book_management.h"
char userName[100];
int cop_ies[100];
typedef struct _Book
{
    int id;
    char Title[100];
//		char *Title; //book Title
//		char *authors; //comma separated list of authors

    char author[100];
    int year;
    int copies;
    int in_copies;
}Book;


typedef struct _BookArray
{
    Book data;
    struct _BookArray *next;
    unsigned int length;
}BookArray;
BookArray* listbook = NULL;
//创建表头：表头就是一个结构体标量
BookArray* createHead()
{

    BookArray* headNode = (BookArray*)malloc(sizeof(BookArray));

    headNode->next=NULL;
    return headNode;
}
BookArray* createNode(Book data)
{
    BookArray* newNode = (BookArray*)malloc(sizeof(BookArray));
    newNode->data= data;
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
int Booktotal=0;

void menu();
void cmd();
void readuserfile();
void readbookfile();
void userfunction(struct useraccount *p);
void librarianview();
void writefile(int flag);
void searchbook();
void insertByHead(BookArray* headNode, Book data)
{
    BookArray* newNode = createNode(data);
    newNode->next= headNode->next;
    headNode->next=newNode;
}
void deleteByName(BookArray* headNode, char *bookName)
{
    BookArray* posLeftNode= headNode;
    BookArray* posNode = headNode->next;
    while(posNode!=NULL && strcmp(posNode->data.Title,bookName))
    {
        posLeftNode=posNode;
        posNode=posLeftNode->next;

    }
    //search result
    if(posNode==NULL)
        return;
    else
    {
        posLeftNode->next = posNode->next;
        free(posNode);
        posNode=NULL;
    }
}
BookArray* searchByName(BookArray* headNode, char *bookName)
{
    BookArray* posNode = headNode->next;
    while(posNode!=NULL && strcmp(posNode->data.Title,bookName))
    {
        posNode = posNode->next;
    }
    return posNode;
}
BookArray* find_book_by_title (const char *Title){
    BookArray* posNode = listbook->next;
    while(posNode!=NULL && strcmp(posNode->data.Title, Title))
    {
        posNode = posNode->next;
    }
    return posNode;
}
BookArray*  find_book_by_author (const char *author){
    BookArray* Movepoint = listbook->next;
    int i = 0;
    printf("id\tTitle\tAuthors\tyear\tcopies\n");
    while(Movepoint!=NULL)//if one author write many books
    {
        if(strcmp(Movepoint->data.author, author)==0)
        {

            printf("%d\t%s\t%s\t%d\t%d\n", Movepoint->data.id, Movepoint->data.Title, Movepoint->data.author,Movepoint->data.year,Movepoint->data.copies);
            i++;
        }
        Movepoint=Movepoint->next;
    }
    if(i==0)
    {
        printf("\nNot found!\n");
    }
}
BookArray* find_book_by_year (unsigned int year)
{
    BookArray* Movepoint = listbook->next;
    int i = 0;
    printf("id\tTitle\tAuthors\tyear\tcopies\n");
    while(Movepoint!=NULL)
    {
        if(Movepoint->data.year==year)//if many books have the same year
        {

            printf("%d\t%s\t%s\t%d\t%d\n", Movepoint->data.id, Movepoint->data.Title, Movepoint->data.author,Movepoint->data.year,Movepoint->data.copies);
            i++;
        }
        Movepoint=Movepoint->next;
    }
    if(i==0)
    {
        printf("\nNot found!\n");
    }
}
BookArray* searchByAthor(BookArray* headNode, char *authorName)
{
    BookArray* posNode = headNode->next;
    while(posNode!=NULL && strcmp(posNode->data.author,authorName))
    {
        posNode = posNode->next;
    }
    return posNode;
}
void displaythebook1(BookArray* headNode)
{
    BookArray* pMove = headNode->next;
    printf("id\tTitle\tAuthors\tyear\tcopies\n");
    while(pMove!=NULL)
    {
        printf("%d\t%s\t%s\t%d\t%d\n", pMove->data.id, pMove->data.Title, pMove->data.author,pMove->data.year,pMove->data.copies);
        pMove=pMove->next;
    }
}
void displaythebook(BookArray *headNode)// arrange the order
{
    BookArray* p= headNode->next;
    BookArray* q = headNode->next;
    for (p ;p!=NULL;p=p->next)
    {
        for (q;q->next!=NULL;q=q->next)
        {
            if (q->data.id < q->next->data.id)
            {
                //交换值
                Book tempData=q->data;
                q->data=q->next->data;
                q->next->data=tempData;
            }
        }
    }
    displaythebook1(headNode);
}

int countbooklist(BookArray* headNode)
{
    BookArray* pMove = headNode->next;
    while(pMove!=NULL)
    {
        Booktotal++;
        pMove=pMove->next;
    }
    Booktotal++;
    return Booktotal;
}

//file operation
//write
void saveInfoToFile(const char* fileName,BookArray* headNode)//store user's infomation on a separate file(username file)
{
    FILE *fp=fopen(fileName,"w");
    BookArray* pMove = headNode->next;
    while(pMove!=NULL)
    {
        fprintf(fp,"%d\t%s\t%s\t%d\t%d\n", pMove->data.id, pMove->data.Title, pMove->data.author,pMove->data.year,pMove->data.copies);
        pMove=pMove->next;
    }
    fclose(fp);
}
//
int store_books(FILE *file){//store book infomation on a separate file(bookinfo1)
    file = fopen("bookinfo1.txt","w");
    BookArray* pMove =listbook->next;
    while(pMove!=NULL)
    {
        fprintf(file,"%d\t%s\t%s\t%d\t%d\n", pMove->data.id, pMove->data.Title, pMove->data.author,pMove->data.year,pMove->data.copies);
        pMove=pMove->next;
    }
    fclose(file);
    return 0;
}
//read
void readInfoFromFile(const char* fileName, BookArray* headNode)//read user's infomation on a separate file(username file)
{
    FILE *fp=fopen(fileName,"r");//if not exist then create
    if(fp==NULL)
    {//if open the first time then create
        fp=fopen(fileName,"w+");
    }
    Book tempData;
    while (fscanf(fp,"%d\t%s\t%s\t%d\t%d\n", &tempData.id, tempData.Title, tempData.author, &tempData.year, &tempData.copies)!=EOF)
    {//insert into the head
        insertByHead(listbook, tempData);
    }
    fclose(fp);
}
int load_books(FILE *file){//read book infomation on a separate file(bookinfo1)
    file =fopen("bookinfo1.txt", "r");//if open the first time then create
    Book tempData;
    if(file==NULL)
    {//if not exist then create
        file=fopen("bookinfo1.txt","w+");
    }
    while (fscanf(file,"%d\t%s\t%s\t%d\t%d\n", &tempData.id, tempData.Title, tempData.author, &tempData.year, &tempData.copies)!=EOF)
    {
        insertByHead(listbook, tempData);//insert into the head
    }
    fclose(file);
    return 0;
}
void menu()//print out the main menu
{
    printf("\nPlease choose an option\n");
    printf("1) Register an account\n");
    printf("2) Login\n");
    printf("3) Search for books\n");
    printf("4) Display all books\n");
    printf("5) Quit\n");
    printf(" Option: ");
}
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
    pc->bookcount = 0;
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
            printf("\n(logged in as: librarian)");
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
            printf("\n(logged in as: %s)\n", pc->username);
            strcpy(userName,pc->username);/*creat the name for userfile*/
            strcat(userName,"");
            strcat(userName,str);
            userfunction(pc);/*go to user menu*/
            return 1;
        }
        pc = pc->next;
    }
}

void librarianview()
{
    int option;
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
            case 1://title, author, and year to add
                tempBook.id = countbooklist(listbook);   //id
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
                        saveInfoToFile("bookinfo1.txt",listbook);
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
                result=searchByName(listbook,tempBook.Title);

                if(result->data.copies!=result->data.in_copies)//if the book is loaned , cnanot remove. By compare the initial copies with the resent one
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
                displaythebook(listbook);
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
int remove_book(Book book)
{
    BookArray* postLeftNode= listbook;
    BookArray* postNode = listbook->next;
    while(postNode!=NULL && strcmp(postNode->data.Title,book.Title))
    {
        postLeftNode=postNode;
        postNode=postLeftNode->next;

    }
    if(postNode==NULL)
        return;
    else
    {
        postLeftNode->next = postNode->next;
        free(postNode);
        postNode=NULL;
    }
    return 0;
}
int add_book(Book book)
{
    BookArray* newNode = createNode(book);
    newNode->next= listbook->next;
    listbook->next=newNode;
    return 0;
}

void cmd()//the main system
{
    int option;
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
            searchbook();
            break;
        case 4:
            displaythebook(listbook);
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
    int j;
    Book tempBook;//a tempotary varies to store the book
    BookArray* result=NULL;//result of rearch
    printf("\nPlease choose an option\n");
    printf("1) Find books by Title\n");
    printf("2) Find books by author\n");
    printf("3) Find books by year\n");
    printf("4) Return to previous menu\n");
    printf(" Option: ");
    int option;
    scanf("%d", &option);
    getchar();
    while(1){
        switch (option)
        {
            case 1:
                printf("Please enter Title：");
                scanf("%s", tempBook.Title);
                result=find_book_by_title(tempBook.Title);
                if(result==NULL)
                {
                    printf("Not found!\n");

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
                    printf("id\tTitle\tAuthors\tyear\tcopies\n");
                    printf("%d\t%s\t%s\t%d\t%d\n", result->data.id, result->data.Title, result->data.author, result->data.year, result->data.copies);
                }
                break;
            case 2:
                printf("Please enter author：");
                scanf("%s", tempBook.author);
                find_book_by_author(tempBook.author);
                break;
            case 3:
                printf("Please enter year：");
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
void userfunction(struct useraccount *pc)
{
    int option;
    int end = 0;
    Book tempBook;//临时的变量存储书籍信息
    BookArray* result=NULL;//查找结果
    BookArray* result2=NULL;//查找结果
    BookArray* user_Name = NULL;
    user_Name= createHead();
    readInfoFromFile(userName, user_Name);//write the infomation into the user's own file
    while (1)
    {
        printf("Please choose an option\n");
        printf("1) Borrow a book\n");
        printf("2) Return a book\n");
        printf("3) Search for books\n");
        printf("4) Display all books\n");
        printf("5) Log out\n");
        printf(" Option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                printf("\n");//if exist the number copies -1, else cannot borrow
                printf("Enter the name of the book you wish to borrow：");
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
                            saveInfoToFile("bookinfo1.txt",listbook);//record the changes of the copies
                            strcpy(tempBook.author,result->data.author);
                            tempBook.year=result->data.year;
                            tempBook.copies=1;
                            tempBook.id=result->data.id;
                            insertByHead(user_Name,tempBook);//add the book into the head
                            saveInfoToFile(userName,user_Name);//save the file
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
                printf("You have already borrowed these books：\n");//return books from a list of borrowed books

                displaythebook(user_Name);
                printf("Enter the name of the book you wish to return：");
                scanf("%s",tempBook.Title);
                result=searchByName(listbook,tempBook.Title);
                if(result==NULL)
                {
                    printf("Do not have this book!\n");
                }
                else
                {
                    result->data.copies++;//record the changes of the copies
                    saveInfoToFile("bookinfo1.txt",listbook);//save the file
                    deleteByName(user_Name, tempBook.Title);
                    saveInfoToFile(userName,user_Name);//save the file
                    printf("Return book successfully!\n");//feedback message to the user when book returned is completed.
                }
                break;
            case 3:
                searchbook();
                break;
            case 4:
                displaythebook(listbook);
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
int main()
{
    FILE *fp;
    FILE *book;
    listbook= createHead();
//	readInfoFromFile("bookinfo1.txt",listbook);
    if(load_books(book)!=0)
    {
        printf("load_books fail!\n");
    }
    head = (struct useraccount *)malloc(sizeof(struct useraccount));
    end = head;
    bookend = bookhead;
    fp = fopen("users", "a+");
//	usercount1 = fread(head, sizeof(struct useraccount), 1, fp);
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
            p = (struct useraccount *)malloc(sizeof(struct useraccount));
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