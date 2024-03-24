#include <stdio.h>

struct ts
{
    int t;
    int ps;
} s[20];

void main()
{
    int n, outrate, time, np, i;

    printf("Enter the size of the bucket:");
    scanf("%d", &n);

    printf("Enter the outrate of the bucket:");
    scanf("%d", &outrate);

    printf("Enter the time interval of leak:");
    scanf("%d", &time);

    printf("Enter the number of packets:");
    scanf("%d", &np);

    for (i = 0; i < np; i++)
    {
        printf("Enter the time and size of packet%d: ", i);
        scanf("%d", &s[i].t);
        scanf("%d", &s[i].ps);
    }

    printf("oper  time  filled  free-space\n");
    int t[30], filled[30], free[30], k = 1, j = 0, flag;
    i = 0;

    do
    {
        flag = 0;
        if (i >= np)
        {
        l:
        {
            printf("remove  ");
            t[j] = time * k;
            filled[j] = filled[j - 1] - outrate;

            printf("%d      %d     ", t[j], filled[j]);
            k++;
        }
        }

        // inserting
        else if (s[i].t < time * k)
        {
            printf("insert  ");
            t[j] = s[i].t;

            if (j == 0 && s[i].ps <= n)
            {
                filled[j] = s[i].ps;
                printf("%d      %d     ", t[j], filled[j]);
            }

            else if ((filled[j - 1] + s[i].ps) <= n)
            {
                filled[j] = filled[j - 1] + s[i].ps;
                printf("%d      %d     ", t[j], filled[j]);
            }

            else
            {
                flag = 1;
                printf("%d      overflow    ", t[j]);
            }
        }

        else
        {
            i--;
            goto l;
        }

        if (flag == 0)
        {
            free[j] = n - filled[j];
            printf("%d\n", free[j]);
        }

        else
        {
            printf("\n");
            filled[j] = filled[j - 1];
        }

        j++;
        i++;
    } while (filled[j - 1] != 0);
}
