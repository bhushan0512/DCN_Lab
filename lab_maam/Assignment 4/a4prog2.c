#include <stdio.h>
#include <string.h>

void crc(char message[], char pattern[])
{
    int msg_length = strlen(message);
    int pattern_length = strlen(pattern);
    int fcs_length = pattern_length - 1;
    char msg[20];
    strcpy(msg, message);

    // Performing CRC division
    int i;
    for (i = 0; i < msg_length; i++)
    {
        if (message[i] == '1')
        {
            if (i <= msg_length - pattern_length)
            {
                for (int j = 0; j < pattern_length; j++)
                {
                    if (message[i + j] == pattern[j])
                        message[i + j] = '0';
                    else
                        message[i + j] = '1';
                }
            }
            else
                break;
        }
    }

    printf("Remainder R is : %s\n", message);
    for (; i < msg_length + fcs_length; i++)
    {
        msg[i] = message[i];
    }

    printf("Message to be Transmitted T is : %s\n", msg);
    char choice;
    int position;
    printf("\nDo You Want to Introduce error(Y/N): ");
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y')
    {
    x:
        printf("Enter the Position: ");
        scanf("%d", &position);

        if (position < 1 || position > strlen(msg))
        {
            printf("Invalid position. Please enter a position between 1 and %d.\n", strlen(msg));
            goto x;
        }

        // Introducing error at the specified position
        msg[msg_length - position] = (msg[msg_length - position] == '1') ? '0' : '1';
    }

    printf("*** RECEIVER ***");
    printf("\nMessage received at the Receiver :%s\n", msg);
    for (i = 0; i < msg_length; i++)
    {
        if (msg[i] == '1')
        {
            if (i <= msg_length - pattern_length)
            {
                for (int j = 0; j < pattern_length; j++)
                {
                    if (msg[i + j] == pattern[j])
                        msg[i + j] = '0';
                    else
                        msg[i + j] = '1';
                }
            }
            else
                break;
        }
    }

    printf("Remainder R is : %s\n", msg);
    int flag = 0;

    for (i = 0; i < msg_length; i++)
    {
        if (msg[i] == '1')
        {
            flag = 1;
            break;
        }
    }

    if (flag)
    {
        printf("ERROR IN MESSAGE");
    }
    else
        printf("MESSAGE WITHOUT ERROR");
}

void main()
{
    char message[100];
    char pattern[100];
    char choice;
    int position;

    printf("*** SENDER ***");
    printf("\nEnter Message: ");
    scanf("%s", message);

    printf("Enter Pattern: ");
    scanf("%s", pattern);

    int msg_length = strlen(message);
    int pattern_length = strlen(pattern);

    if (pattern_length >= msg_length)
    {
        printf("Pattern size should be less than Message. Please re-enter the Pattern \n");
        return ;
    }

    printf("Given Message is  : %s\n", message);
    printf("Given Pattern is  : %s\n", pattern);
    printf("Message size is   : %d\n", msg_length);
    printf("Pattern Size is   : %d\n", pattern_length);
    printf("FCS               : %d bit\n", pattern_length - 1);

    // Appending zeros to the message
    for (int i = 0; i < pattern_length - 1; i++)
    {
        message[msg_length + i] = '0';
    }
    message[msg_length + pattern_length - 1] = '\0';

    printf("After Appending Q is: %s\n", message);
    crc(message, pattern);
}
