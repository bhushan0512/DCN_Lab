#include <stdio.h>

struct node
{
    unsigned dist[20];
    unsigned from[20];
} rt[10];

int main()
{
    int dmat[20][20];
    int n, i, j, k, count = 0;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("\nEnter the cost matrix:(Assign value 999 if there is no direct connection)\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            scanf("%d", &dmat[i][j]);
            dmat[i][i] = 0;
            rt[i].dist[j] = dmat[i][j];
            rt[i].from[j] = j;
        }

    printf("\nInitial Tables:\n");
    for (i = 0; i < n; i++)
    {
        printf("\nRouter %d:\n", i + 1);
        printf("Destination\tDistance\tNext Hop\n");

        for (j = 0; j < n; j++)
        {
            if (rt[i].dist[j] == 999)
            {
                printf("%d\t\t%d\t\t-\n", j + 1, rt[i].dist[j]);
            }
            else
            {
                printf("%d\t\t%d\t\t%d\n", j + 1, rt[i].dist[j], rt[i].from[j] + 1);
            }
        }
    }

    do
    {
        count = 0;
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                for (k = 0; k < n; k++)

                    if (rt[i].dist[j] > dmat[i][k] + rt[k].dist[j])
                    {
                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
    }

    while (count != 0);
    printf("\nUpdated Tables:\n");

    for (i = 0; i < n; i++)
    {
        printf("\nRouter %d:\n", i + 1);
        printf("Destination\tDistance\tNext Hop\n");

        for (j = 0; j < n; j++)
        {
            printf("%d\t\t%d\t\t%d\n", j + 1, rt[i].dist[j], rt[i].from[j] + 1);
        }
    }

    printf("\n");
    return 0;
}
