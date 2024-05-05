#include <stdio.h>

struct packet
{
    int seqno;
    int ponum;
    char sip[20];
    char dip[20];
    int pid;
    char a[100];
    float time;
} p[100], temp;

void insertionsort(int n)
{
    int i, j;
    for (i = 1; i < n - 1; i++)
    {
        temp = p[i];
        for (j = i - 1; j >= 0 && temp.seqno < p[j].seqno; j--)
        {
            p[j + 1] = p[j];
        }
        p[j + 1] = temp;
    }
}

void main()
{
    int i, j, n, num;
    printf("Enter the number of frames:");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
    slabel:
        num = rand() % 100;
        for (j = 0; j <= i; j++)
        {
            if (p[j].seqno == num)
            {
                goto slabel;
            }
        }
        p[i].seqno = num;
        printf("Enter message:");
        scanf("%s", &p[i].a);
        printf("Enter packet id:");
        scanf("%d", &p[i].pid);
        printf("Enter port number:");
        scanf("%d", &p[i].ponum);
        printf("Enter source ip:");
        scanf("%s", &p[i].sip);
        printf("Enter destination ip:");
        scanf("%s", &p[i].dip);
    }

    printf("Before sorting:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%s\t%s\t%s\n", p[i].seqno, p[i].pid, p[i].ponum, p[i].sip, p[i].dip, p[i].a);
    }

    insertionsort(n);
    printf("After sorting:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%s\t%s\t%s\n", p[i].seqno, p[i].pid, p[i].ponum, p[i].sip, p[i].dip, p[i].a);
    }
}
