//neww
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Birthdate{
    unsigned int day ,month,year ;

}Birthdate;
typedef struct Employee{
    unsigned int id;
    char lastName[40];
    char firstName[40];
    float salary;
    Birthdate date;
    char address[100];
    char phoneNumber[14]; //11+null +2010 92017250
    char email[254]; //longest email address allowed

}Employee;

Employee ar[100]; //global variable
char fileName[]="company.txt";

Birthdate *constructDate(int day,int month,int year){
    Birthdate *dt=(Birthdate *)malloc(sizeof(Birthdate));
    dt->day=day;
    dt->month=month;
    dt->year=year;
    return dt;
}
Employee *constructEmployee(int id,char *lastName,char *firstName,float salary, int day, int month, int year,char *address,char *phoneNumber,char *email ){
   Employee *e=(Employee *)malloc(sizeof(Employee));
   e->id=id;
   strcpy(e->lastName,lastName);
   strcpy(e->firstName,firstName);
   e->salary=salary;
   e->date=*constructDate(day,month,year);
   strcpy(e->address,address);
   strcpy(e->phoneNumber,phoneNumber);
   strcpy(e->email,email);
   return e;

}


Employee *deserialize(char *st){ //read employee info from file and divide it into diff tokens
    char *token=strtok(st,",-");  // coma delimiter
    int i=0,id=0,year=0,month=0,day=0;
    float salary;
    char *lastName=NULL,*firstName=NULL,*address=NULL,*phoneNumber=NULL,*email=NULL;
    while (token){
        switch(i){
       case 0:id=atoi(token); //convert string to integer
        break;
       case 1:lastName=token;
        break;
       case 2:firstName=token;
        break;
        case 3:salary=atof(token); //atof
        break;
        case 4:day=atoi(token);
        break;
        case 5:month=atoi(token);
        break;
        case 6:year=atoi(token);
        break;
        case 7:address=token;
        break;
        case 8:phoneNumber=token;
        break;
        case 9:email=token;
        break;}
        i++;
        token=strtok(NULL,",-");
    }
    return constructEmployee(id,lastName,firstName,salary,day,month,year,address,phoneNumber,email);
}
void readFile(int *number){
    *number=0;
    int i;
    FILE *f=fopen(fileName,"r");
    if(!f){
        printf("ERROR READING FILE %s\n",fileName);
        exit(1);
    }
    char st[300];
    while(!feof(f)){//not end of file
        char *e=fgets(st,299,f);
        if(!e) break;
        Employee *test=deserialize(st);
        ar[(*number)++]=*test;
        free(test);
    }
    fclose(f);
}
int validId(char *id){
    int i=0;
    if(id[0]=='0') //id does not start with 0
        return 0;
    while (id[i]){
      char c=id[i];
      if(c<'0'||c>'9')//asci
        return 0; //0 is false
      i++;
    }
    if(i>14)      //national id 14
        return 0;
    return 1; //valid number
}
int validPhoneNumber(char *phone){
    int i=0;
    if (strlen(phone)!=11&&strlen(phone)!=13)
        return 0;
    if (strlen(phone)==11&&((phone[0]!='0'||phone[1]!='1')||(phone[2]!='1'&&phone[2]!='0'&&phone[2]!='5'&&phone[2]!='2')))
        return 0;
    if (strlen(phone)==13&&(phone[0]!='+'||phone[1]!='2'||phone[2]!='0'||phone[3]!='1'||(phone[4]!='1'&&phone[4]!='0'&&phone[4]!='5'&&phone[4]!='2')))
        return 0;
        i=2;
    while (phone[i]){
      char c=phone[i];
       if(c<'0'||c>'9')//asci
        return 0; //0 is false
      i++;
    }
  return 1;
}
int validDigits(char *s){
    int i=0;
    if (s[0]=='0') return 0;
      while (s[i]){
      char c=s[i];
       if(c<'0'||c>'9')
        return 0;
      i++;
    }
  return 1;
}

int validEmail(char *email){
    int i=0,a=0,d=0;
    if (email[0]=='-'||email[0]=='.')
        return 0;
    char*p=strstr(email,".com");
    if(!p)
        return 0;
    if(strlen(p)!=4) //last 4 characters .com
       return 0;
    if(!p)
        return 0;
    while(email[i]){
            char c=email[i];
        if(c=='@')
            ++a;                         // a should be = 1
        if(c==' ')
            return 0;
     i++;
    }
   if (a>1)
        return 0;
   return 1;
}
int validName(char *name){
    int i=0;
    while(name[i]){
            char x=name[i];
        if(!(x>='a'&&x<='z')&&!(x>='A'&&x<='Z'))
        return 0;
    i++;
    }
    return 1;
}

int isLeapYear(int year)
{
    if((year%400==0)||((year%4==0)&&(year%100!=0)))
       return 1;
    else
        return 0;
}
int validDate(Birthdate *o){
      if(o->year<1961||o->year>2004) //will always be updated employee has max 60 year min 18
        return 0;
      if(o->month<1||o->month>12)
        return 0;
      if(o->day<1||o->day>31)
        return 0;
      if(o->month==2){
        if (isLeapYear((int)o->year)){
            if(o->day>29)
            return 0;
        }
        else if (o->day>28)
            return 0;
      }
      if((o->month==4||o->month==6||o->month==9||o->month==11)&&o->day==31)
        return 0;
      return 1;
}
void queryLname(int *number){ //search function by last name
    char lname[40];
    int flag=0;
    printf("Search for an employee\n");
    printf("Enter last name: ");
    scanf("%s",lname);
    printf("\n");
    int i;
    for(i=0;i<*number;i++){
    if(strcasecmp(ar[i].lastName,lname)==0){
        printf("Id= %d\nFirst name= %s\nSalary= %.2f\nBirthday= %2d-%2d-%d\nAddress= %s\nPhone number= %s\nEmail= %s\n\n",
            ar[i].id,ar[i].firstName,ar[i].salary,ar[i].date.day,ar[i].date.month,ar[i].date.year,ar[i].address,ar[i].phoneNumber,ar[i].email);

        flag=1;
        }
    }
    if (flag==0)
    printf("No employees found\n");
}
void addEmployee(int *number){

    if(*number<100){
       int n=*number;
       (*number)++;
       printf("\n");
      printf("New employee's information\n");
       char fname[40];
        do
		{
          printf("Enter first name:");
          scanf("%s",fname);
		  if(fname[0]>='a'&&fname[0]<='z')
            fname[0]=fname[0]-32;
		}while(!validName(fname));
		strcpy(ar[n].firstName,fname);

		char lname[40];
        do
		{
          printf("Enter last name:");
		  scanf("%s",lname);
		  if(lname[0]>='a'&&lname[0]<='z')
            lname[0]=lname[0]-32;
		}while(!validName(lname));
		strcpy(ar[n].lastName,lname);

		char id[15];
		do
		{
          printf("Enter id:");
		  scanf("%s",id);
		}while(!validId(id));

		ar[n].id=atoi(id);

		char phone[16];
		do
		{
          printf("Enter phone number:");
		  scanf("%s",phone);
		}while(!validPhoneNumber(phone));
		strcpy(ar[n].phoneNumber,phone);

		char address[100];
          printf("Enter address:");//don't need to validate address
          getchar();
		  gets(address);
		  strcpy(ar[n].address,address);

		char email[254];
		do
		{
          printf("Enter email address:");
		  scanf("%s",email);
		}while(!validEmail(email));
		strcpy(ar[n].email,email);
		if(strlen(ar[n].email)>0&&ar[n].email[strlen(ar[n].email)-1]=='\n')
            ar[n].email[strlen(ar[n].email)-1]='\0';


		char salary[15];
        printf("Enter salary:");
        scanf("%s",salary);
		ar[n].salary=atof(salary);

		char day[3],month[3],year[5];
		Birthdate *t;
		printf("Enter birth date\n");
		do{
		   printf("Enter day: ");
            scanf("%s",&day);
            printf("Enter month: ");
            scanf("%s",&month);
            printf("Enter year: ");
            scanf("%s",&year);

            t=constructDate(atoi(day),atoi(month),atoi(year));

		}while(!(validDate(t)&&validDigits(day)&&validDigits(month)&&validDigits(year)));
		ar[n].date.day=atoi(day);
		ar[n].date.month=atoi(month);
		ar[n].date.year=atoi(year);
		free(t);

    }
       else{
        printf("FULL!\n");
       }
}
void printemployee(Employee e){
       printf("Id= %d\nLast name= %s\nFirst name= %s\nSalary= %.2f\nBirthday= %2d-%2d-%d\nAddress= %s\nPhone number= %s\nEmail= %s\n\n",
            e.id,e.lastName,e.firstName,e.salary,e.date.day,e.date.month,e.date.year,e.address,e.phoneNumber,e.email);
}

void modify(int *number){
    int i,e=0,u;
    char id[15],fname[40],lname[40],phone[16],address[100],email[254],salary[15], day[3],month[3],year[5];

    do
    {
        printf("Enter ID of employee to modify: ");
        scanf("%s", id);
    } while (!validId);
    for (i = 0; i < *number; i++)
    {
        if (ar[i].id == atoi(id))
        {
            e++;
            printf("Employee to be modified is:\n");
            printemployee(ar[i]);
            printf("Enter 1 if you want to modify the last name or enter 0 to skip\n ");
            scanf("%d",&u);
            if(u){
              do{
                printf("Last name: ");
                scanf("%s",lname);
                if(lname[0]>='a'&&lname[0]<='z')
                    lname[0]=lname[0]-32;
              }while(!validName(lname));
              strcpy(ar[i].lastName,lname);

            }
            printf("Enter 1 if you want to modify the first name or enter 0 to skip\n ");
            scanf("%d",&u);
            if(u){
              do{
                printf("First name: ");
                scanf("%s",fname);
                if(fname[0]>='a'&&fname[0]<='z')
                    fname[0]=fname[0]-32;
              }while(!validName(fname));
              strcpy(ar[i].firstName,fname);

            }
            printf("Enter 1 if you want to modify phone number or enter 0 to skip\n ");
            scanf("%d",&u);
            if(u){
              do{
                printf("Phone number: ");
                scanf("%s",phone);
              }while(!validPhoneNumber(phone));
              strcpy(ar[i].phoneNumber,phone);

            }
            printf("Enter 1 if you want to modify address or enter 0 to skip\n ");
            scanf("%d",&u);
            if(u){
                printf("Address: ");
                getchar();
                gets(address);
              strcpy(ar[i].address,address);
            }
            printf("Enter 1 if you want to modify email or enter 0 to skip\n ");
            scanf("%d",&u);
            if(u){
              do{
                printf("Email: ");
                scanf("%s",email);
              }while(!validEmail(email));
              strcpy(ar[i].email,email);

            }
            printf("Enter 1 if you want to modify birth date or enter 0 to skip\n ");
            scanf("%d",&u);
            if(u){
		       Birthdate *t;
            printf("Enter birth date\n");
		  do{
		   printf("Enter day: ");
            scanf("%s",&day);
            printf("Enter month: ");
            scanf("%s",&month);
            printf("Enter year: ");
            scanf("%s",&year);

            t=constructDate(atoi(day),atoi(month),atoi(year));

		}while(!(validDate(t)&&validDigits(day)&&validDigits(month)&&validDigits(year)));
		ar[i].date.day=atoi(day);
		ar[i].date.month=atoi(month);
		ar[i].date.year=atoi(year);
		 free(t);
            }
             printf("Enter 1 if you want to modify salary or enter 0 to skip\n ");
            scanf("%d",&u);
            if(u){

            printf("Enter salary:");
            scanf("%s",salary);
          ar[i].salary=atof(salary);

            }
        }



}
   if(!e)
    printf("Employee not found\n");
}


void deleteEmployee(int *number){ //delete employee using first and last name
    char lname[40],fname[40];
    int i,j,flag=0;
    printf("Enter information of employee you wish to delete\n");
    printf("Enter last name: ");
    scanf("%s",lname);
    printf("Enter first name: ");
    scanf("%s",fname);
    for(i=0;i<*number;i++){
        if(strcasecmp(ar[i].lastName,lname)==0&&strcasecmp(ar[i].firstName,fname)==0){
                flag=1;
            for(j=i;j<*number-1;j++){
                ar[j]=ar[j+1];
            }
        (*number)--;
        i=-1;
        }

    }
    if(flag==0)
        printf("Employee not found!\n");
}


void sortByLname(int *number){ //from a to z
    int i,j;
    printf("Sort employees by last name\n\n");
    Employee temp[*number];
    for(i=0;i<*number;i++){
        for(j=0;j<*number-1-i;j++){
            if(strcasecmp(ar[j].lastName,ar[j+1].lastName)>0){
                temp[j]=ar[j];
                ar[j]=ar[j+1];
                ar[j+1]=temp[j];
            }
            else if (strcasecmp(ar[j].lastName,ar[j+1].lastName)==0&&strcasecmp(ar[j].firstName,ar[j+1].firstName)>0){
                temp[j]=ar[j];
                ar[j]=ar[j+1];
                ar[j+1]=temp[j];
            }
        }
    }
}
void SortByDOB(int *number){ //from oldest to youngest //modified
    int i,j;
    printf("Sort employees by date of birth\n\n");
    Employee temp[*number];
    for(i=0;i<*number;i++){
        for(j=0;j<*number-1-i;j++){
            if(ar[j].date.year>ar[j+1].date.year){
                temp[j]=ar[j];
                ar[j]=ar[j+1];
                ar[j+1]=temp[j];
            }
            else if (ar[j].date.year==ar[j+1].date.year&&ar[j].date.month>ar[j+1].date.month){
                temp[j]=ar[j];
                ar[j]=ar[j+1];
                ar[j+1]=temp[j];
            }
            else if (ar[j].date.year==ar[j+1].date.year&&ar[j].date.month==ar[j+1].date.month&&ar[j].date.day>ar[j+1].date.day){
                temp[j]=ar[j];
                ar[j]=ar[j+1];
                ar[j+1]=temp[j];
            }
            else
                continue;
        }
    }
}
void  SortBySalary(int *number){ //from least salary
    int i,j;
    printf("Sort employees by salary\n\n");
    Employee temp[*number];
    for(i=0;i<*number;i++){
        for(j=0;j<*number-1-i;j++){
            if(ar[j].salary>ar[j+1].salary){
                temp[j]=ar[j];
                ar[j]=ar[j+1];
                ar[j+1]=temp[j];
            }
        }
    }

}
void print(int *number){
     int c,i,n;
     n=*number;
    puts("Please choose a sort option");
    puts("\t1.sort by last name from A to Z");
    puts("\t2.sort by date of birth from oldest to youngest");
    puts("\t3.sort by salary from lowest to highest");
    if(scanf(" %d", &c)!= 1){
            printf("You should enter a number\n");
            exit(0);}
    switch(c){
        case 1:sortByLname(&n);break;
        case 2:SortByDOB(&n);break;
        case 3:SortBySalary(&n);break;
        default:printf("choose again\n");break;
    }
    for(i=0;i<*number;i++){
    printf("Id= %d\nLast name= %s\nFirst name= %s\nSalary= %.2f\nBirthday= %2d-%2d-%d\nAddress= %s\nPhone number= %s\nEmail= %s\n\n",
            ar[i].id,ar[i].lastName,ar[i].firstName,ar[i].salary,ar[i].date.day,ar[i].date.month,ar[i].date.year,ar[i].address,ar[i].phoneNumber,ar[i].email);
    }
    }




void saveFile(int *number){
    FILE *f=fopen(fileName,"w"); //edit add delete
    if(!f){
        printf("ERROR CREATING FILE %s\n",fileName);
    exit(0);}
    int i;
    char st[400];
    for (i=0;i<*number;i++){
        sprintf(st,"%d,%s,%s,%.2f,%2d-%2d-%d,%s,%s,%s",ar[i].id,ar[i].lastName,ar[i].firstName,ar[i].salary,ar[i].date.day,ar[i].date.month,ar[i].date.year,ar[i].address,ar[i].phoneNumber,ar[i].email);
          if(strlen(st)>0&&st[strlen(st)-1]=='\n')
            st[strlen(st)-1]='\0';
          fprintf(f,"%s\n",st);
    }
    fclose(f);
    printf("File %s is saved\n",fileName);
}
int screen(){
    int c;
    puts("Please choose an option");
    puts("\t1.SEARCH for an employee");
    puts("\t2.ADD an employee");
    puts("\t3.DELETE an employee");
    puts("\t4.MODIFY employee's info");
    puts("\t5.PRINT entire employees'list");
    puts("\t6.SAVE changes");
    puts("\t7.QUIT the program");

    if(scanf("%d",&c)!=1){
            printf("You should enter a number !\n");
            exit(0);
            }
    return c;
}
int main()
{

    int n,c,i;
    printf("\t\t\t\t\t\t\t\tWELCOME TO THE COMPANY MANGEMENT SYSTEM\n");
    readFile(&n);
    do{
    c=screen();

    switch(c){
        case 1:queryLname(&n);break;
        case 2:addEmployee(&n);break;
        case 3:deleteEmployee(&n);break;
        case 4:modify(&n);break;
        case 5:print(&n);break;
        case 6:saveFile(&n);break;
        case 7:{
            char m[2];
            printf("Are you sure you want to exit?(Y/N)\n ");
            if(!scanf("%s",m)){
                printf("invalid try again\n");
                break;}
            else if (strcasecmp(m,"n")==0)
                break;
            else if(strcasecmp(m,"y")==0)
                exit(0);}
        default:printf("invalid choice try again\n");}
    }while(1);




    return 0;
}

