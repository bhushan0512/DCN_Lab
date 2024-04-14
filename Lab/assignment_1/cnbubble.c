#include <stdio.h>
#include <stdlib.h> // for rand() function
#include <string.h> // for strcpy() function

// Define a structure to represent a packet
struct packet {
    int seqno;
    char a[100];
    float time;
} p[100], temp;

// Function to sort packets based on their sequence numbers using bubble sort
void bubblesort(int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].seqno > p[j + 1].seqno) {
                temp = p[j + 1];
                p[j + 1] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int i, j, n, num;
    printf("Enter the number of frames: ");
    scanf("%d", &n);

    // Generate and fill packets with random sequence numbers
    for (i = 0; i < n; i++) {
        slabel:
        num = rand() % 100;
        for (j = 0; j <= i; j++) {
            if (p[j].seqno == num) {
                goto slabel;
            }
        }
        p[i].seqno = num;
        printf("Enter message: ");
        scanf("%s", p[i].a);
        p[i].time = rand();
    }

    printf("Before sorting:\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%s\t%f\n", p[i].seqno, p[i].a, p[i].time);
    }

    // Sort packets based on their sequence numbers
    bubblesort(n);

    printf("After sorting:\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%s\t%f\n", p[i].seqno, p[i].a, p[i].time);
    }

    return 0;
}
