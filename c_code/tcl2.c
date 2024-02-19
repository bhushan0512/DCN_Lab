#include<stdio.h>
void main(){
    FILE *fp = fopen("/home/adminmca/Documents/bhushan/tcl/out.tr", "r");
    char x = 'd';
    char c;
    int count = 0;

    if(!fp)
        printf("Cant't open a file");
    
    while ((c=getc(fp))!=EOF)
    {
        if (c == 'd')
            count++;
    }
    printf("Packet droppped %d\n", count);
    fclose(fp);
}