#include <stdio.h>
void main()
{
    FILE *fp = fopen("/home/student/Documents/out.tr", "r");
    char x = 'd';
    char c;
    int count = 0;

    if (!fp)
    {
        printf("can't open file");
    }

    while ((c = getc(fp)) != EOF)
    {
        if (c == 'd')
        {
            count++;
        }
    }
    printf("packet dropped %d", count);
    fclose(fp);
}
