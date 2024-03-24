#include<stdio.h>
#include<string.h>

void main()
{
char msg[20],s1[10]= {'1','0'};
int i,op,count=0;
printf("*** SENDER ***");
printf("\nEnter the message:");
scanf("%s",&msg);

for(i=0; msg[i]!='\0'; i++)
{
if(msg[i]=='1')
count++;
}

int len=strlen(msg);
if(count%2==0)
{
sprintf(msg, "%s%c", msg,s1[0]);
printf("Even Parity\n");
printf("Message to be Transmitted:%s",msg);
}
else
{
sprintf(msg, "%s%c", msg,s1[1]);
printf("Odd Parity\n");
printf("Message to be Transmitted:%s",msg);
}

printf("\nDo you want to introduce error(y/n):");
char ch;
int pos;
scanf(" %c",&ch);

if(ch=='y')
{
x:
printf("Enter the position:");
scanf("%d",&pos);

if(len<pos)
{
printf("\nInvalid position. Please re enter\n");
goto x;
}
pos=pos-1;

if(msg[pos]=='1')
msg[pos]='0';
else
msg[pos]='1';
}

printf("*** RECEIVER ***");
printf("\nMessage received at the Receiver:%s",msg);
len=strlen(msg);
count=0;

for(i=0; msg[i+1]!='\0'; i++)
{
if(msg[i]=='1')
count++;
}

if(msg[len-1]=='0')
if(count%2!=0)
printf("\nMESSAGE WITHOUT ERROR");
else
printf("\nERROR IN MESSAGE");

if(msg[len-1]=='1')
if(count%2==0)
printf("\nMESSAGE WITHOUT ERROR");
else
printf("\nERROR IN MESSAGE");
}
