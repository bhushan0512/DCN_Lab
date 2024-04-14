#include<stdio.h>
#include<stdlib.h>

struct packet
{
int seqno;
char a[100];
float time;
}
p[100],temp;

void quicksort(int left,int right)
{
int i,j,pivot;
if(left<right)
{
i=left;
j=right+1;
pivot=p[left].seqno;
do
{
do
{
i++;
}

while(p[i].seqno<pivot&&i<=right);
do
{
j--;
}

while(p[j].seqno>pivot&&j>=left);
if(i<j)
{
temp=p[i];
p[i]=p[j];
p[j]=temp;
}
}

while(i<=j);
temp=p[left];
p[left]=p[j];
p[j]=temp;
quicksort(left,j-1);
quicksort(j+1,right);
}
}

void main()
{
int i,j,n,num;
printf("Enter the number of frames:");
scanf("%d",&n);
for(i=0; i<n; i++)
{
slabel:
num=rand()%100;
for(j=0; j<i; j++)
{
if(p[j].seqno==num)
goto slabel;
}
p[i].seqno=num;
printf("Enter message:");
scanf("%s",p[i].a);
p[i].time=rand();
}

printf("Before sorting:\n");
for(i=0; i<n; i++)
{
printf("%d\t%s\t%f\n",p[i].seqno,p[i].a,p[i].time);
}

quicksort(0,n-1);
printf("After sorting:\n");
for(i=0; i<n; i++)
{
printf("%d\t%s\t%f\n",p[i].seqno,p[i].a,p[i].time);
}
}
