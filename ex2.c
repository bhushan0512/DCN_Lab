#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FRAMES 100

struct Frame {
    int sequenceNumber;
    int time;
    char message[100];
};

int generateRandomNumber() {
    int x;
    x = rand() % 10000;
    if (x > 999)
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

int partition(struct Frame frames[], int low, int high) {
    int pivot = frames[high].sequenceNumber;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (frames[j].sequenceNumber <= pivot) {
            i++;
            swap(&frames[i], &frames[j]);
        }
    }

    swap(&frames[i + 1], &frames[high]);
    return i + 1;
}

void quickSort(struct Frame frames[], int low, int high) {
    if (low < high) {
        int pi = partition(frames, low, high);

        quickSort(frames, low, pi - 1);
        quickSort(frames, pi + 1, high);
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
    printf("Sequence Number\t\tTime\t\tMessage\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t\t%d\t\t%s\n", frames[i].sequenceNumber, frames[i].time, frames[i].message);
    }
    printf("\n");
}

int main() {
    // srand(time(NULL));

    struct Frame frames[MAX_FRAMES];

    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i].sequenceNumber = generateRandomNumber();
        frames[i].time = generateRandomTime();
        sprintf(frames[i].message, "Message %d", i + 1);
    }

    int frameCount = MAX_FRAMES;

    displayFrames(frames, frameCount, "Frames Before Sorting");

    // Use quickSort instead of bubbleSort
    quickSort(frames, 0, frameCount - 1);

    displayFrames(frames, frameCount, "Frames After Sorting");

    removeRepeatedFrames(frames, &frameCount);

    displayFrames(frames, frameCount, "Frames After Removing Repeated Sequences");

    return 0;
}
