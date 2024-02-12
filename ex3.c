#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FRAMES 10

struct Frame {
    int sequenceNumber;
    int packetId;
    char sourceIPAddress[100];
    char destinationIPAddress[100];
    int port;
    char message[100];
};

int generateRandomNumber() {
    int x;
    x = rand() % 1000;
    if (x > 99)
        return x;
    generateRandomNumber();
}

int generateRandomTime() {
    return rand() % 100;
}

void swap(struct Frame *a, struct Frame *b) {
    struct Frame temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort(struct Frame frames[], int n) {
    int i, j;
    struct Frame key;
    for (i = 1; i < n; i++) {
        key = frames[i];
        j = i - 1;

        while (j >= 0 && frames[j].sequenceNumber > key.sequenceNumber) {
            frames[j + 1] = frames[j];
            j = j - 1;
        }

        frames[j + 1] = key;
    }
}

void removeRepeatedFrames(struct Frame frames[], int *n) {
    for (int i = 0; i < *n; i++) {
        for (int j = i + 1; j < *n;) {
            if (frames[i].sequenceNumber == frames[j].sequenceNumber) {
                for (int k = j; k < *n - 1; k++) {
                    frames[k] = frames[k + 1];
                }
                (*n)--;
            } else {
                j++;
            }
        }
    }
}

void displayFrames(struct Frame frames[], int n, const char *title) {
    printf("%s:\n", title);
    printf("Sequence Number\tPacket ID\tSource IP \tDestination \t port \tMessage\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%s\t%s\t%d\t%s\n", frames[i].sequenceNumber, frames[i].packetId, frames[i].sourceIPAddress, frames[i].destinationIPAddress, frames[i].port, frames[i].message);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    struct Frame frames[MAX_FRAMES];

    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i].sequenceNumber = generateRandomNumber();
        frames[i].packetId = i + 1;
        sprintf(frames[i].sourceIPAddress, "192.168.1.%d", i + 1);
        sprintf(frames[i].destinationIPAddress, "10.0.0.%d", i + 1);
        frames[i].port = 8080 + i;
        sprintf(frames[i].message, "Message %d", i + 1);
    }

    int frameCount = MAX_FRAMES;

    displayFrames(frames, frameCount, "Frames Before Sorting");

    insertionSort(frames, frameCount);

    displayFrames(frames, frameCount, "Frames After Sorting");

    removeRepeatedFrames(frames, &frameCount);

    displayFrames(frames, frameCount, "Frames After Removing Repeated Sequences");

    return 0;
}
