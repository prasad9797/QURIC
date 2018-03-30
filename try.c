#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define IN 1
#define OUT 0
#define ADMIN 1234

void AddBook();
void DisplayBookInfo();
void Searchbook();
void Addmember();
void Issue();
void ReturnBook();
void DisplayMemberInfo();
void DeleteBook();
void EditBookInfo();
void DeleteMember();
//void EditMemberInfo();*/
void Exit();


char info[500];
char infom[500];

struct
{
  int bookId;
  char bookName[50] ;
  char author[50];
  int noOfChap;
  int status;
}book;
struct
{
  int memberId;
  char memberName[25] ;
  char department[25];
  int availableCard;
  int phoneNo;
}member;


FILE *libraryData;
FILE *memberData;
FILE *file1;
FILE *file2;
FILE *temp1;
FILE *temp2;


int main()
{
    int choice=0,i;

    printf("\n*********************************************************\n\t\tLIBRARY MANAGEMENT SYSTEM\n*********************************************************\n");
    do{
    printf("\n\t<<<<MENU>>>>\n\n 1>  Add A New Book\n 2>  Display Book Information\n 3>  Search a book \n 4>  Add A New Member \n 5>  Issue \n 6>  Return A Issued Book \n 7>  Display Member Information \n 8>  Delete Book \n 9>  Edit Book Information \n 10> Delete Member \n 11> Edit Member Information \n 12> Exit the program \n\n\t Enter your choice  ");
    scanf("%i",&choice);


    switch (choice)
    {
        case 1:
            AddBook();
            break;
        case 2:
        	DisplayBookInfo();
            break;
        case 3:
            Searchbook();
            break;
        case 4:
            Addmember();
            break;
        case 5:
			Issue();
            break;
        case 6:
        	ReturnBook();
        	break;
        case 7:
        	DisplayMemberInfo();
        	break;
		case 8:
           DeleteBook();
           break;
        case 9:
        	EditBookInfo();
        	break;
        case 10:
        	DeleteMember();
        	break;
//        case 11:
  //      	EditMemberInfo();
    //    	break;
        case 12:
        	Exit();
        	break;
        default:
            printf(" Sorry Invalid Input\n");
    }
}while(choice!=12);
 return (0);
}

void AddBook()
{
	int i,found=0; 
	book.status=IN;
    libraryData = fopen("libraryData.txt","a+");
    printf("Enter The Unique Id of The Book :(Numeric) \n");
        scanf("%d",&book.bookId);
    printf("Enter The Name of The Book :\n");
        scanf("%s",book.bookName);
	printf("Enter The Name of Author :\n");
        scanf("%s",book.author);
    printf("Enter The Number of Chapters Of The Book:(Numeric)\n");
        scanf("%d",&book.noOfChap);
        while(book.noOfChap==0)
        {
        	printf("Number of Chapters Of The Book Cannot Be Zero:(Enter Numeric Value)\n");
			scanf("%d",&book.noOfChap);
		}
    fprintf( libraryData,"\n%d\t%s\t%s\t%d\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap);
    fclose( libraryData);
    printf("Your Book has been Successfully Added\n");

}


void DisplayBookInfo()
{
    libraryData = fopen("libraryData.txt","a+");
    printf("______________________________________________\nBook Id\t Name\tAuthor\tStatus\tNo.Of Chapter\n______________________________________________\n");
  while(!feof(libraryData))
    {
        fgets(info,500,libraryData);
        printf("%s\n",info);
    }
    printf("______________________________________________\n\n");
    fclose(libraryData);
  }


void Searchbook()
{
    int i,a,findId;
    char find[25],stats[3];
    int found=0;
    if((libraryData=fopen("libraryData.txt","r"))==NULL)
        printf("\n\n Sorry The File Is Empty\n\n");
    else
    {
    	printf("\n 1>Search By Name Of Book:\n 2>Search By Unique Id Of Book:\n 3>Search Book With Chapter More Than 5:\n 4>Generic Search  \n\n\t Enter Your Choice  ");
    	scanf("%d",&i);
    	switch(i)
		{

		case 1:
        	printf("\nEnter The Name Of Book : \n\n");
            scanf("%s",find);
             while(feof(libraryData)==0 && found==0)
        {
        fscanf(libraryData,"%d %s %s %d %d", &book.bookId,book.bookName,book.author,&book.status,&book.noOfChap);
            if(strcmp(find,book.bookName)==0)
                found=1;

        }
        break;
        case 2:
        	printf("\nEnter The Unique Id Of Book : \n");
            scanf("%d",&findId);
            while(feof(libraryData)==0 && found==0)
        {
        fscanf(libraryData,"%d %s %s %d %d", &book.bookId,book.bookName,book.author,&book.status,&book.noOfChap);
        if(findId==book.bookId)
        found=1;

        }
        break;
        case 3:
            while(feof(libraryData)==0)
        	{
        		fscanf(libraryData,"%d %s %s %d %d", &book.bookId,book.bookName,book.author,&book.status,&book.noOfChap);
	            if(5<book.noOfChap)
				{
        	    	if(book.status==IN)
            	    strcpy(stats,"IN");
            		else
      		        strcpy(stats,"OUT");
        	   		printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\nNumber Of Chapters Is: %d\n\n",book.bookId,book.bookName,book.author,stats,book.noOfChap);
	        	    found=3;
				}
        	}
     		fclose(libraryData);
        	break;
        case 4:
        		printf("\n\nChoose From The Following\n\n1> Member ID or Number Of Chapter To Be Searched :\n2> Name Of Book Or Author : \n");
            	scanf("%d",&a);
            	switch(a)
				{
            		case 1:
           			 	printf("\nEnter The Number To Search : \n");
           				scanf("%d",&findId);
           				while(feof(libraryData)==0)
       					{
       					fscanf(libraryData,"%d %s %s %d %d", &book.bookId,book.bookName,book.author,&book.status,&book.noOfChap);
           				if(findId==book.bookId || findId==book.noOfChap)
           					{
                 				if(book.status==IN)
                				strcpy(stats,"IN");
            					else
                				strcpy(stats,"OUT");
           						printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\nNumber Of Chapters Is: %d\n\n",book.bookId,book.bookName,book.author,stats,book.noOfChap);
								found=3;
       						}
   						}
   					break;
    				case 2:
    				 	printf("\nEnter The Name To Search : \n");
            			scanf("%s",find);
           				while(feof(libraryData)==0)
       					{
       						fscanf(libraryData,"%d %s %s %d %d", &book.bookId,book.bookName,book.author,&book.status,&book.noOfChap);
           					if(strcmp(find,book.bookName)==0 || strcmp(find,book.bookName)==0)
           					{
        	       				if(book.status==IN)
            	   				strcpy(stats,"IN");
           						else
                				strcpy(stats,"OUT");
           						printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\nNumber Of Chapters Is: %d\n\n",book.bookId,book.bookName,book.author,stats,book.noOfChap);
								found=3;
        					}
    					}
    				break;
				}
        break;
        	
        }

        if(found==1 && found!=2 && found!=3)
        {
            if(book.status==IN)
            strcpy(stats,"IN");
            else
            strcpy(stats,"OUT");
        	printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\nNumber Of Chapters Is: %d\n\n",book.bookId,book.bookName,book.author,stats,book.noOfChap);
        }
        else if(found!=1 && found!=2 && found!=3)
        printf("\n\nSorry There is no such Entry\n");
        fclose(libraryData);
    }

}



void Addmember()
{

    memberData = fopen("memberData.txt","a+");
    printf("Enter The userid of the Member(Numeric) :\n");
    scanf("%d",&member.memberId);
    printf("Enter The Name of the Member :\n");
    scanf("%s",member.memberName);
    printf("Enter The Department\n");
    scanf("%s",member.department);
    printf("Enter The phone number of the member:\n");
    scanf("%d",&member.phoneNo);
    member.availableCard=5;
    fprintf(memberData,"\n%d\t%s\t%s\t%d\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
    fclose(memberData);
    printf("\n\n New Member Is Successfully Added\n");


}

void Issue()
{
    int memberid,check1=0,check2=0;
	char issuBookName[20];
	temp1=libraryData;
	temp2=memberData;
    DisplayMemberInfo();
    printf("\nEnter The userid of the Member : \n");
    scanf("%d",&memberid);
    if((memberData=fopen("memberData.txt","r"))==NULL)
    printf(" Sorry The file is empty\n\n");
    else
    {
        while(!feof(memberData)&& check1==0)
        {
            fscanf(memberData,"%d %s %s %d %d ",&member.memberId,&member.memberName,&member.department,&member.phoneNo,&member.availableCard);
            if(memberid==member.memberId)
            {
            	check1=1;
            }
        }
        if(check1)
        {
            if(member.availableCard<1)
            {
                printf(" Sorry You Have No More Library Card\n");
            }
            else
            {   DisplayBookInfo();
                printf("\nEnter The Name of book :");
                scanf("%s",issuBookName);
                if((libraryData=fopen("libraryData.txt","r"))==NULL)
                printf(" Sorry The file is empty\n\n");
                else
                {
                    while(!feof(libraryData)&& check2==0)
                    {
                        fscanf(libraryData,"%d %s %s %d %d", &book.bookId,book.bookName,book.author,&book.status,&book.noOfChap);
                        if(strcmp(issuBookName,book.bookName)==0)
                        check2=1;
                    }
                    if(check2)
                    {
                        if(book.status==0)
                        {
                            printf(" Sorry The Book already issued...\n");
                        }
                        else
                        {

                            file2=fopen("file2.txt","w");
                            if((temp2=fopen("memberData.txt","r"))==NULL)
                            printf(" Sorry The file is empty\n\n");
                            else
                            {
                                while(!feof(temp2))
                                {
                                    fscanf(temp2,"%d %s %s %d %d ",&member.memberId,member.memberName,member.department,&member.phoneNo,&member.availableCard);


                                    if(memberid==member.memberId)
                                    {
                                        member.availableCard--;
                                        fprintf(file2,"\n %d\t%s\t%s\t%d\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
                                    }
                                    else
									{
                                        fprintf(file2,"\n %d\t%s\t%s\t%d\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
									}
                                    if(feof(temp2))
                                    break;
                                }
                            }
                            fclose(temp2);
                            fclose(file2);


                            file1=fopen("file1.txt","w");
                            if((temp1=fopen("libraryData.txt","r"))==NULL)
                            printf(" Sorry The file is empty\n\n");
                            else
                            {
                                while(!feof(temp1))
                                {
                                    fscanf(temp1,"%d %s %s %d %d", &book.bookId,book.bookName,book.author,&book.status,&book.noOfChap);
                                    if(strcmp(issuBookName,book.bookName)!=0)
                                    {
                                        fprintf(file1,"\n%d\t%s\t%s\t%d\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap);
                                    }
                                    else
                                    {
                                        fprintf(file1,"\n%d\t%s\t%s\t%d\t%d",book.bookId,book.bookName,book.author,0,book.noOfChap);
                                	}
                                }
                            }
                            fclose(temp1);
                            fclose(file1);
                            fclose(libraryData);
                            fclose(memberData);
                            remove("libraryData.txt");
                            rename("file1.txt","libraryData.txt");
                            remove("memberData.txt");
                            rename("file2.txt","memberData.txt");
                            printf("\n\nYou Have Successfully Issued A Book\n");
                        }
                    }
                    else if(!check2)
                    printf(" Sorry There Is No Such Book\n");
                }
            }
        }
        else if(!check1)
        printf(" Sorry Invalid User id\n");
	}

}


void DisplayMemberInfo()
{
	memberData = fopen("memberData.txt","a+");
    printf("_______________________________________________\nMemid\tName\tDept\tPh.no\tAvailablecards\n_______________________________________________");
    do
    {
    	fgets(infom,500,memberData);
        printf("%s\n",infom);
    }while(!feof(memberData));
    printf("\n_______________________________________________\n");
    fclose(memberData);
}


void ReturnBook()
{
	int memberid,check1=0,check2=0,flag=0;
	char retbookname[20];
    temp1=libraryData;
	temp2=memberData;
    DisplayMemberInfo();
    printf("\nEnter The userid of the Member :\n");
    scanf("%d",&memberid);
    if((memberData=fopen("memberData.txt","r"))==NULL)
    printf("Sorry The file is empty\n\n");
    else
    {
        while(!feof(memberData) && check1==0)
        {
            fscanf(memberData,"%d %s %s %d %d ",&member.memberId,member.memberName,member.department,&member.phoneNo,&member.availableCard);
            if(memberid==member.memberId)
            {
                check1=1;
            }
        }
        if(check1)
        {
            if(member.availableCard>=5)
            {
                printf("Sorry You Have No More Cards\n");
            }
            else
            {
				DisplayBookInfo(); 
			    printf("\nEnter The Name of book :");
                scanf("%s",retbookname);
                if((libraryData=fopen("libraryData.txt","r"))==NULL)
                printf("Sorry The file is empty\n\n");
                else
                {
                    while(!feof(libraryData) && check2==0)
                    {
                        fscanf(libraryData,"%d %s %s %d %d", &book.bookId,book.bookName,book.author,&book.status,&book.noOfChap);
                        if(strcmp(retbookname,book.bookName)==0)
                        check2=1; 
                    }
                    if(check2)
                    {
                        if(book.status==1)
                        {
                            printf("Sorry The Book already in stock\n");
                        }
                        else
                        {    
                            
                            file2=fopen("file2.txt","w");
                            if((temp2=fopen("memberData.txt","a+"))==NULL)
                            printf("Sorry The file is empty\n\n");
                            else
                            { 
                                while(!feof(temp2))
                                {
                                    fscanf(temp2,"%d %s %s %d %d ",&member.memberId,member.memberName,member.department,&member.phoneNo,&member.availableCard);
                            
                                    
                                    if(memberid==member.memberId)
                                    {
                                        member.availableCard++;
                                        fprintf(file2,"\n %d\t%s\t%s\t%d\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
                                    }
                                    else
                                    {
                                        fprintf(file2,"\n %d\t%s\t%s\t%d\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);
                                    }
                                    if(feof(temp2))
                                    break;
                                }
                            }
                            fclose(temp2);
                            fclose(file2);
                            

                            file1=fopen("file1.txt","w");
                            if((temp1=fopen("libraryData.txt","r"))==NULL)
                                printf("Sorry The file is empty\n\n");
                            else
                            {
                                while(!feof(temp1))
                                {
                                    fscanf(temp1,"%d %s %s %d %d", &book.bookId,book.bookName,book.author,&book.status,&book.noOfChap);
                                    if(strcmp(retbookname,book.bookName)!=0)
                                    {
                                    	fprintf(file1,"\n%d\t%s\t%s\t%d\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap);
                                    }
                                    else
                                    {
                                        fprintf(file1,"\n%d\t%s\t%s\t%d\t%d",book.bookId,book.bookName,book.author,1,book.noOfChap);
                                    }
                                }
                            }
                            fclose(temp1);
                            fclose(file1);
                            fclose(libraryData);
                            fclose(memberData);
                            printf("\n\nBook Successfully Returned\n");
                            remove("libraryData.txt");
                            rename("file1.txt","libraryData.txt");
                            remove("memberData.txt");
                            rename("file2.txt","memberData.txt");

                        }                
                    }
                    else if(!check2)
                        printf("Sorry There Is No Such Book\n");
                
                }
            }
        }
        else if(!check1)
            printf("Sorry Invalid User Id\n");
        

    }
    
}


void DeleteBook()
{
	int password,bookid;
	printf("\nEnter The Admin Password\n");
	scanf("%d",&password);
	if(ADMIN==password)
	{
		void DisplayBookInfo();
		printf("\nEnter The Id Of Book To Delete :\n");
        scanf("%d",bookid);
    	if((libraryData=fopen("libraryData.txt","r"))==NULL)
        printf("Sorry The file is empty\n\n");	
		else
		{
			file1=fopen("file1.txt","a+");
			while(!feof(libraryData))
            {
            	fscanf(libraryData,"%d %s %s %d %d", &book.bookId,book.bookName,book.author,&book.status,&book.noOfChap);
            	if(bookid==book.bookId)
				{
					if(book.status==0)
                	{
                    	printf("Sorry Cannot Delete Issued Book\n");
                	}
				}
				if(bookid!=book.bookId)
				fprintf(file1,"\n%d\t%s\t%s\t%d\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap);				
			}
            fclose(file1);
            fclose(libraryData);
            printf("\n\nBook Successfully Deleted\n");
            remove("libraryData.txt");
            rename("file1.txt","libraryData.txt");
		}
	}
	else
	printf("Sorry Password Is Incorrect\n");
}


void DeleteMember()
{
	int password,memberid;
	printf("\nEnter The Admin Password\n");
	scanf("%d",&password);
	if(ADMIN==password)
	{
		DisplayMemberInfo();
		printf("\nEnter The Id Of Member To Delete :\n");
        scanf("%d",&memberid);
    	if((memberData=fopen("memberData.txt","r"))==NULL)
        printf("Sorry The file is empty\n\n");	
		else
		{
			file2=fopen("file2.txt","a+");
			while(!feof(memberData))
            {
            	fscanf(memberData,"%d %s %s %d %d ",&member.memberId,member.memberName,member.department,&member.phoneNo,&member.availableCard);
            	if(memberid==member.memberId)
				{
					if(member.availableCard<5)
                	{
                    	printf("Sorry Cannot Delete Member Until Issued Books Are Returned\n");
                	}
				}
				if(memberid!=member.memberId)
				fprintf(file2,"\n%d\t%s\t%s\t%d\t%d",member.memberId,member.memberName,member.department,member.phoneNo,member.availableCard);				
			}
            fclose(file2);
            fclose(memberData);
            printf("\n\nMember Successfully Deleted\n");
            remove("memberData.txt");
            rename("file2.txt","memberData.txt");
		}			
				
	}
	else
	printf("Sorry Password Is Incorrect\n");		
}


void EditBookInfo()
{
	int password,memberid,i,check=0;
	printf("\nEnter The Admin Password\n");
	scanf("%d",&password);
	if(ADMIN==password)
	{
		void DisplayBookInfo();
		printf("\nEnter The Id Of Book To Delete :\n");
        scanf("%d",bookid);
    	if((libraryData=fopen("libraryData.txt","r"))==NULL)
        printf("Sorry The file is empty\n\n");	
		else
		{
			file1=fopen("file1.txt","a+");
			while(!feof(libraryData))
            {
            	fscanf(libraryData,"%d %s %s %d %d", &book.bookId,book.bookName,book.author,&book.status,&book.noOfChap);
            	if(bookid==book.bookId)
				{
					if(book.status==0)
                	{
                    	printf("Sorry Cannot Delete Issued Book\n");
                	}
				}
				if(bookid!=book.bookId)
				fprintf(file1,"\n%d\t%s\t%s\t%d\t%d",book.bookId,book.bookName,book.author,book.status,book.noOfChap);
				else
				{
					do
					{
					printf("\nEnter Your Choice\n 1> Edit Book Id \n 2> Edit Book Name \n 3> Edit Book Author \n 4> Edit Number Of Chapter Of Book\n");
					scanf("%d",&i);
					switch(i)
					{
						case 1:
					}
					}while(check==0);
				}				
			}
            fclose(file1);
            fclose(libraryData);
            printf("\n\nBook Successfully Deleted\n");
            remove("libraryData.txt");
            rename("file1.txt","libraryData.txt");			
		}		
	}
	else
	printf("Sorry Password Is Incorrect\n");	
}


void Exit()
{
  exit(0);
}
