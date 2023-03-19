#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
struct passenger
{
    char name[20],gender,fromplace[20],toplace[20],mobnumber[15],passtrainname[20],passdate[15];
    int uninum,age,passcharges,passtimehour,passtimeminutes,passtrainnum;
    struct passenger *next;
};
struct train
{
    char trainname[20],trainfrom[20],trainto[20];
    int trainnumber,traincharges,time_hour,time_minutes,trainpassenger;
    struct train *next1;
};
struct passenger *head=NULL,*last=NULL;
struct train *head1=NULL,*last1=NULL;
void bookticket();
void normalmenu();
void adminmenu();
void addnewtrain();
void traindetailsadmin();
void bookedticket();
void cancelticket();
void traindetails();
void allbookedtickets();
void traindetails()
{
    FILE *filetrain=fopen("traindetails.txt","r+");
    struct train*b;
    b=head1;
    if(b==NULL)
    {
        b=(struct train*)malloc(sizeof(struct train));
        head1=b;
    }
    printf("\ntrain-number train-name starts-from reach-to    charges no.of-booking-left time  \n");

    while(fscanf(filetrain,"%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",&b->trainnumber,&b->trainname,&b->trainfrom,&b->trainto,&b->traincharges,&b->trainpassenger,&b->time_hour,&b->time_minutes)!=EOF)
    {
        printf("%-12d %-10s %-11s %-11s %-7d %-18d %d:%d\n",b->trainnumber,b->trainname,b->trainfrom,b->trainto,b->traincharges,b->trainpassenger,b->time_hour,b->time_minutes);
        b->next1=(struct train*)malloc(sizeof(struct train));
        b=b->next1;
        last1=b;
        b->next1=NULL;
    }
    printf("\npress any key to go back to menu :");
    getch();
    fclose(filetrain);
    system("cls");
    normalmenu();


}
void bookedticket()
{
    FILE *filebooking=fopen("ticketbooking.txt","r+");
    system("cls");
    fflush(stdin);
    printf("\nenter your name and unique id number: \n");
    int p;
    char localname[20];
    gets(localname);
    fflush(stdin);
    scanf("%d",&p);
    fflush(stdin);
    struct passenger *a;
    a=head;
    if(a==NULL)
    {
        a=(struct passenger*)malloc(sizeof(struct passenger));
        head=a;
    }
    while(fscanf(filebooking,"%s\t%c\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d\t%d",&a->name,&a->gender,&a->age,&a->fromplace,&a->toplace,&a->mobnumber,&a->uninum,&a->passcharges,&a->passtrainnum,&a->passtrainname,&a->passdate,&a->passtimehour,&a->passtimeminutes)!=EOF)
    {
        if((strcmp(localname,a->name)==0)  && p==a->uninum)
        {
            printf("\ndetails are :\n");
            printf("name: %s\ngender: %c\nage: %d\nsource station: %s\nfinal station: %s\nmobile number: %s\nunique id number: %d\npassenger charges: %d\ntrain number: %d\ntrain name: %s\ndate of journey: %s\n time: %d:%d",a->name,a->gender,a->age,a->fromplace,a->toplace,a->mobnumber,a->uninum,a->passcharges,a->passtrainnum,a->passtrainname,a->passdate,a->passtimehour,a->passtimeminutes);
            printf("\npress any key to continue ");
            getch();
            system("cls");
            normalmenu();


        }
        else   
        { 
            a->next=(struct passenger*)malloc(sizeof(struct passenger));
            a=a->next;
            last=a;
            a->next=NULL;
        }
    }
    printf("\nyou have no bookings yet\n");
    printf("press any key to go to menu ");
    getch();
    system("cls");
    normalmenu();
    
    
}
void cancelticket()
{
    FILE *filebooking=fopen("ticketbooking.txt","r+");
    FILE *filetrain=fopen("traindetails.txt","r+");
    printf("\nenter your name and unique id number: \n");
    char localname[20];
    int localtrainnum;
    int p;
    fflush(stdin);
    gets(localname);
    fflush(stdin);
    scanf("%d",&p);
    fflush(stdin);
    printf("\nenter train number: ");
    scanf("%d",&localtrainnum);
    fflush(stdin);

    struct passenger *a;
    a=head;
    if(a==NULL)
    {
        a=(struct passenger*)malloc(sizeof(struct passenger));
        head=a;
    }
    int check1=0;
    int howmanytrain=0;
    while(fscanf(filebooking,"%s\t%c\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d\t%d",&a->name,&a->gender,&a->age,&a->fromplace,&a->toplace,&a->mobnumber,&a->uninum,&a->passcharges,&a->passtrainnum,&a->passtrainname,&a->passdate,&a->passtimehour,&a->passtimeminutes)!=EOF)
    {
        if((strcmp(localname,a->name)==0)  && p==a->uninum)
        {
            ++check1;
            break;
        }
        
        howmanytrain++;
        a->next=(struct passenger*)malloc(sizeof(struct passenger));
        a=a->next;
        last=a;
        a->next=NULL;
        
    }
    if(check1!=1)
    {
        printf("\nyou have no booked ticket\n");
        printf("\npress any key to go to menu");
        getch();
        system("cls");
        normalmenu();
    }


    struct train *b1;
    b1=head1;
    if(b1==NULL)
    {
        b1=(struct train*)malloc(sizeof(struct train));
        head1=b1;
    }
    int howmanytrain2=0;
    
    while(fscanf(filetrain,"%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",&b1->trainnumber,&b1->trainname,&b1->trainfrom,&b1->trainto,&b1->traincharges,&b1->trainpassenger,&b1->time_hour,&b1->time_minutes)!=EOF)
    {
        if(b1->trainnumber==localtrainnum)
        {
            break;
        }
        howmanytrain2++;
        b1->next1=(struct train*)malloc(sizeof(struct train));
        b1=b1->next1;
        last1=b1;
        b1->next1=NULL;
    }rewind(filetrain);
    b1->trainpassenger++;
    struct train*c1;
    c1=head1;
    if(c1==NULL)
    {
        c1=(struct train*)malloc(sizeof(struct train));
        head1=c1;
    }
    if(howmanytrain2==0)
    {
        fprintf(filetrain,"%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",b1->trainnumber,b1->trainname,b1->trainfrom,b1->trainto,b1->traincharges,b1->trainpassenger,b1->time_hour,b1->time_minutes);
    }
    if(howmanytrain2>0)
    {
        for(int k=1;k<=howmanytrain2;k++)
        {
            fscanf(filetrain,"%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",&c1->trainnumber,&c1->trainname,&c1->trainfrom,&c1->trainto,&c1->traincharges,&c1->trainpassenger,&c1->time_hour,&c1->time_minutes);
            c1->next1=(struct train*)malloc(sizeof(struct train));
            c1=c1->next1;
            last1=c1;
            c1->next1=NULL;
        
        }fseek(filetrain,1,SEEK_CUR);
        fprintf(filetrain,"%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",b1->trainnumber,b1->trainname,b1->trainfrom,b1->trainto,b1->traincharges,b1->trainpassenger,b1->time_hour,b1->time_minutes);
        
    }
    fclose(filetrain);







    
    rewind(filebooking);
    int z=0;
    while(  (a->name)[z]!='\0'  )
    {
        a->name[z]='-';
        z++;
        
    }
    a->gender='-';
    a->age=00;
    
    z=0;
    while(       (a->mobnumber)[z]!='\0')
    {
        a->mobnumber[z]='-';
        z++;
    }
    
    
    
    if(howmanytrain==0)
    {
        fprintf(filebooking,"%s\t%c\t%02d\t%s\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d\t%d",a->name,a->gender,a->age,a->fromplace,a->toplace,a->mobnumber,a->uninum,a->passcharges,a->passtrainnum,a->passtrainname,a->passdate,a->passtimehour,a->passtimeminutes);

        printf("your ticket has been cancelled\n");
        fclose(filebooking);
        printf("\npress any key to continue ");
        getch();
        system("cls");
        normalmenu();
    }
    struct passenger *c=NULL;
    c=(struct passenger*)malloc(sizeof(struct passenger));
    for(int i=1;i<=howmanytrain;i++)
    {
        fscanf(filebooking,"%s\t%c\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d\t%d",&c->name,&c->gender,&c->age,&c->fromplace,&c->toplace,&c->mobnumber,&c->uninum,&c->passcharges,&c->passtrainnum,&c->passtrainname,&c->passdate,&c->passtimehour,&c->passtimeminutes);
        c->next=(struct passenger*)malloc(sizeof(struct passenger));
        c=c->next;
        last=c;
        c->next=NULL;
    }                                                                                                                                                                                   fseek(filebooking,1,SEEK_CUR);                                                    
                                                                                                                                                                                                                                                   
    fprintf(filebooking,"%s\t%c\t%02d\t%s\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d\t%d",a->name,a->gender,a->age,a->fromplace,a->toplace,a->mobnumber,a->uninum,a->passcharges,a->passtrainnum,a->passtrainname,a->passdate,a->passtimehour,a->passtimeminutes);
    printf("your ticket has been cancelled\n");
    fclose(filebooking);
    printf("\npress any key to continue ");
    
    getch();
    system("cls");
    normalmenu();


}
void traindetailsadmin()
{
    FILE *filetrain=fopen("traindetails.txt","r+");
    struct train*b;
    b=head1;
    if(b==NULL)
    {
        b=(struct train*)malloc(sizeof(struct train));
        head1=b;
    }
    printf("\ntrain-number train-name starts-from reach-to    charges no.of-booking-left time  \n");

    while(fscanf(filetrain,"%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",&b->trainnumber,&b->trainname,&b->trainfrom,&b->trainto,&b->traincharges,&b->trainpassenger,&b->time_hour,&b->time_minutes)!=EOF)
    {
        printf("%-12d %-10s %-11s %-11s %-7d %-18d %d:%d\n",b->trainnumber,b->trainname,b->trainfrom,b->trainto,b->traincharges,b->trainpassenger,b->time_hour,b->time_minutes);
        b->next1=(struct train*)malloc(sizeof(struct train));
        b=b->next1;
        last1=b;
        b->next1=NULL;
    }
    printf("\npress any key to go back to menu :");
    getch();
    fclose(filetrain);
    system("cls");
    adminmenu();
}
void bookticket()
{
    
    int howmany;
    printf("===========ticket booking===============\n");
    printf("how many tickets you want to book? ");
    fflush(stdin);
    scanf("%d",&howmany);
    fflush(stdin);
    struct passenger *a;
    struct train *b;
    for(int i=1;i<=howmany;i++)
    {
        FILE *filebooking=fopen("ticketbooking.txt","a+");
        FILE *filetrain=fopen("traindetails.txt","r+");
        a=head;
        if(a==NULL)
        {
            a=(struct passenger*)malloc(sizeof(struct passenger));
            head=a;
        }
        b=head1;
        if(b==NULL)
        {
            b=(struct train*)malloc(sizeof(struct train));
            head1=b;
        }
        int roughuninum;
        
        while(fscanf(filebooking,"%s\t%c\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d\t%d",&a->name,&a->gender,&a->age,&a->fromplace,&a->toplace,&a->mobnumber,&a->uninum,&a->passcharges,&a->passtrainnum,&a->passtrainname,&a->passdate,&a->passtimehour,&a->passtimeminutes)!=EOF)
        {
            roughuninum=a->uninum;
            a->next=(struct passenger*)malloc(sizeof(struct passenger));
            a=a->next;
            last=a;
            a->next=NULL;
        }
        roughuninum++;
        fflush(stdin);

        printf("\nenter the source station: ");
        gets((last->fromplace));
        fflush(stdin);
        printf("\nenter the place where you want to go: ");
        gets((last->toplace));
        fflush(stdin);
        int check1=0;
        int howmanytrain=0;
        while(fscanf(filetrain,"%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",&b->trainnumber,&b->trainname,&b->trainfrom,&b->trainto,&b->traincharges,&b->trainpassenger,&b->time_hour,&b->time_minutes)!=EOF)
        {
            if(   strcmp(b->trainto,last->toplace)==0 && strcmp(b->trainfrom,last->fromplace)==0)
            {
                
                ++check1;
                break;
            }
            howmanytrain++;
            b->next1=(struct train*)malloc(sizeof(struct train));
            b=b->next1;
            last1=b;
            b->next1=NULL;
        }
        
        
         
        if(check1!=1)
        {
            printf("\nno train available\n");
            printf("press any key to go back");
            getch();
            system("cls");
            bookticket();
        }
        if(b->trainpassenger==0)
        {
            printf("\nsorry no seats available\n");
            printf("\npress any key to go to menu");
            getch();
            system("cls");
            normalmenu();
        }
        printf("\nenter passenger name: ");
        gets((last->name));
        
        fflush(stdin);
        printf("\nenter gender 'm' for male and 'f' for female: ");
        scanf("%c",&(last->gender));
        fflush(stdin);
        printf("\nenter age: ");
        scanf("%d",&(last->age));
        fflush(stdin);
        int agedivison=1;
        if((last->age)<18)
        {
            agedivison=2;
        }
        printf("\nenter mobile number:");
        scanf("%s",&(last->mobnumber));
        fflush(stdin);
        printf("\nenter date of travelling as (dd/mm/yy): ");
        scanf("%s",&(last->passdate));
        fflush(stdin);

        fprintf(filebooking,"\n%s\t%c\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d\t%d",last->name,last->gender,last->age,last->fromplace,last->toplace,last->mobnumber,roughuninum,(b->traincharges)/agedivison,b->trainnumber,b->trainname,last->passdate,b->time_hour,b->time_minutes);
        (b->trainpassenger)--;
        struct train* c=NULL;
        c=(struct train*)malloc(sizeof(struct train));
        if(i<howmany)
        {
            printf("\nbooking done successfully\n");
            printf("\ndetails are :\n");
            printf("passenger name is: %s\n",last->name);
            printf("\nyour uninque id number is %d\n",roughuninum);
            printf("\ntrain name is %s and train number is %d\n",b->trainname,b->trainnumber);
            printf("passenger charges are : %d\n",b->traincharges/agedivison);
            printf("train starts from %s at %d:%d on %s and will go to %s\n",last->fromplace,b->time_hour,b->time_minutes,last->passdate,last->toplace);rewind(filetrain);
            
            if(howmanytrain==0)
            {
                
                fprintf(filetrain,"%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",b->trainnumber,b->trainname,b->trainfrom,b->trainto,b->traincharges,b->trainpassenger,b->time_hour,b->time_minutes);
                goto reachtonextbooking;
            }
            
            for(int j=1;j<=howmanytrain;j++)
            {
                fscanf(filetrain,"%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",&c->trainnumber,&c->trainname,&c->trainfrom,&c->trainto,&c->traincharges,&c->trainpassenger,&c->time_hour,&c->time_minutes);
                {
                    
                    c->next1=(struct train*)malloc(sizeof(struct train));
                    c=c->next1;
                    last1=c;
                    c->next1=NULL;
                }
            }                                                                                                                                                                                             fseek(filetrain,1,SEEK_CUR);
            fprintf(filetrain,"%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",b->trainnumber,b->trainname,b->trainfrom,b->trainto,b->traincharges,b->trainpassenger,b->time_hour,b->time_minutes);


            
            reachtonextbooking:
            {
                printf("\npress any key to fill the next booking");
                fclose(filebooking);
                fclose(filetrain);
                getch();
            }
        }
        if(i==howmany)
        {
            system("cls");
            printf("booking done successfully\n");
            printf("\ndetails are :\n");
            printf("passenger name is: %s\n",last->name);
            printf("\nyour uninque id number is %d\n",roughuninum);
            printf("\ntrain name is %s and train number is %d\n",b->trainname,b->trainnumber);
            printf("passenger charges are : %d\n",b->traincharges/agedivison);
            printf("train starts from %s at %d:%d on %s and will go to %s\n",last->fromplace,b->time_hour,b->time_minutes,last->passdate,last->toplace);rewind(filetrain);

           
            if(howmanytrain==0)
            {
                fprintf(filetrain,"%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",b->trainnumber,b->trainname,b->trainfrom,b->trainto,b->traincharges,b->trainpassenger,b->time_hour,b->time_minutes);
                goto reachtofinalbooking;
            }
            for(int j=1;j<=howmanytrain;j++)
            {
                fscanf(filetrain,"%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",&c->trainnumber,&c->trainname,&c->trainfrom,&c->trainto,&c->traincharges,&c->trainpassenger,&c->time_hour,&c->time_minutes);
                {
                    
                    c->next1=(struct train*)malloc(sizeof(struct train));
                    c=c->next1;
                    last1=c;
                    c->next1=NULL;
                }
            }                                                                                                                                                                                                                     fseek(filetrain,1,SEEK_CUR);
            fprintf(filetrain,"%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",b->trainnumber,b->trainname,b->trainfrom,b->trainto,b->traincharges,b->trainpassenger,b->time_hour,b->time_minutes);
        
            reachtofinalbooking:
            {
                printf("press any key to continue");
                fclose(filebooking);
                fclose(filetrain);
                getch();
                system("cls");
                normalmenu();
            }
            

        }
       
        

        
    }

    
}
void allbookedtickets()
{
    FILE *filebooking=fopen("ticketbooking.txt","r+");
    printf("\npassenger-name gender age source-station final-station mobile-number unique-id-no. charges train-num train-name travel-date time\n");
    struct passenger *a;
    a=head;
    if(a==NULL)
    {
        a=(struct passenger*)malloc(sizeof(struct passenger));
        head=a;
    }
    while(fscanf(filebooking,"%s\t%c\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t%d\t%d",&a->name,&a->gender,&a->age,&a->fromplace,&a->toplace,&a->mobnumber,&a->uninum,&a->passcharges,&a->passtrainnum,&a->passtrainname,&a->passdate,&a->passtimehour,&a->passtimeminutes)!=EOF)
    {
        printf("%-14s %-6c %-3d %-14s %-14s %-13s %-13d %-7d %-9d %-10s %-11s %d:%d\n",a->name,a->gender,a->age,a->fromplace,a->toplace,a->mobnumber,a->uninum,a->passcharges,a->passtrainnum,a->passtrainname,a->passdate,a->passtimehour,a->passtimeminutes);
        
        a->next=(struct passenger*)malloc(sizeof(struct passenger));
        a=a->next;
        last=a;
        a->next=NULL;
        
    }
    fclose(filebooking);
    printf("\npress any key to continue ");
    
    getch();
    system("cls");
    adminmenu();

}
void normalmenu()
{
    int option;
    printf("=============MENU==============\n");
    printf("1. book train ticket\n");
    printf("2.show booked ticket details\n");
    printf("3.show train details\n");
    printf("4.cancel booked ticket\n");
    printf("5. exit\n");
    printf("choose option: ");
    scanf("%d",&option);
    fflush(stdin);
    switch(option)
    {
        case 1:
        {
            system("cls");
            bookticket();
        }
        case 2:
        {
            system("cls");
            bookedticket();
        }
        case 3:
        {
            system("cls");
            traindetails();
        }
        case 4:
        {
            system("cls");
            cancelticket();
        }
        case 5:
        {
            exit(0);
        }
    }


}
void addnewtrain()
{
    FILE *filetrain=fopen("traindetails.txt","a+");
    struct train*b;
    b=head1;
    if(b==NULL)
    {
        b=(struct train*)malloc(sizeof(struct train));
        head1=b;
    }
    while(fscanf(filetrain,"%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",&b->trainnumber,&b->trainname,&b->trainfrom,&b->trainto,&b->traincharges,&b->trainpassenger,&b->time_hour,&b->time_minutes)!=EOF)
    {
        b->next1=(struct train*)malloc(sizeof(struct train));
        b=b->next1;
        last1=b;
        b->next1=NULL;
    }
    fflush(stdin);
    printf("\nenter train number: ");
    scanf("%d",&last1->trainnumber);
    printf("\nenter train name: ");
    fflush(stdin);
    gets(last1->trainname);
    printf("\nenter train starting point: ");
    gets(last1->trainfrom);
    printf("\nenter final point: ");
    gets(last1->trainto);
    printf("\nenter train charges for adult: ");
    scanf("%d",&last1->traincharges);
    printf("\nenter total number of passengers it can afford: ");
    scanf("%d",&last1->trainpassenger);
    printf("\nenter time(hour) in 24 hour format:  ");
    scanf("%d",&last1->time_hour);
    printf("\nenter time(minutes): ");
    scanf("%d",&last1->time_minutes);
    fprintf(filetrain,"\n%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d",last1->trainnumber,last1->trainname,last1->trainfrom,last1->trainto,last1->traincharges,last1->trainpassenger,last1->time_hour,last1->time_minutes);
    printf("\ntrain added successfully");
    fclose(filetrain);
    printf("\nenter any key to continue: ");
    getch();
    system("cls");
    adminmenu();
    

}
void adminmenu()
{
    system("cls");
    printf("1.display train details\n");
    printf("2.display booked ticket database\n");
    printf("3.add new trains\n");
    printf("4.exit\n");
    printf("\nchoose option: ");
    int choose;
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:
        {
            system("cls");
            traindetailsadmin();
        }
        case 2:
        {
            system("cls");
            allbookedtickets();
        }
        case 3:
        {
            system("cls");
            addnewtrain();
        }
        case 4:
        {
            exit(0);
        }
        default:
        {
            printf("\nyou have choosen an incorrect option ");
            printf("\npress anything to refill it ");
            getch();
            system("cls");
            adminmenu();

        }
    }


}
int main()
{
    char password[6]="77338",pass[6];
    char user[20],admin[20]="root",decision;
    int option;
    while(1)
    {
        printf("\n\n                     =======log in==========\n\n\n");
        printf("select what are you: \n");
        printf("                         1.normal user\n                         2.admin\n");
        printf("                          enter your choice:  ");
        scanf("%d",&option);
        fflush(stdin);
        switch(option)
        {
            case 1:
            {
                system("cls");
                normalmenu();
            }
            case 2:
            {
                while(1)
                {
                    system("cls");
                    printf("                       Enter adminname: ");
                    gets(user);
                    
                    printf("                       Enter 5 digit password: ");
                    for(int k=0;k<=4;k++)
                    {
                        pass[k]=getch();
                        putch('*');
                        fflush(stdin);

                    }
                    getch();
                    int l=0;
                    for(int k=0;k<=4;k++)
                    {
                        if(pass[k]==password[k])
                            l++;

                    }

                    if(strcmp(user,admin)==0  && l==5)
                    {
                        printf("\n\n\n                         login successful\n\n");
                        fflush(stdin);
                        printf("                     presss any key to continue");
                        getch();
                        system("cls");
                        adminmenu();
                        break;

                    }
                    else
                    {
                        printf("\nincorrect username or password\n");
                        printf("press any key to refill it ");
                        getch();
                    }
                }
               
            }
            default:
            {
                printf("\ninvalid option");
                printf("\npress any key to refill it ");
                getch();
                system("cls");
            }
        }
    }


}