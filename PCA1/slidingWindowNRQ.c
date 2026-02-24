#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_FRAMES 100

int window_size, total_frames;

/* Function to send frames */
void send_frames(int start, int end) {
    for (int i = start; i < end; i++) {
        printf("Sending Frame %d\n", i);
        sleep(1);
    }
}

int main() {
    srand(time(0));

    printf("Enter the window size: ");
    scanf("%d", &window_size);

    printf("Enter total number of frames to send: ");
    scanf("%d", &total_frames);

    if (total_frames > MAX_FRAMES || window_size > total_frames) {
        printf("Invalid input! Window size must be <= total frames\n");
        return 1;
    }

    int base = 0;

    while (base < total_frames) {

        int end;
        if (base + window_size < total_frames)
            end = base + window_size;
        else
            end = total_frames;

        /* Send frames in current window */
        send_frames(base, end);

        /* Simulate ACK reception */
        int ack = base + (rand() % window_size + 1);

        if (ack >= end) {
            printf("ACK received for frames %d to %d\n", base, end - 1);
            base = end;   // slide window
        } else {
            printf("ACK lost at frame %d\n", ack);
            printf("Resending from frame %d\n", ack);
            base = ack;   // Go-Back-N
        }
   
        printf("\n");
    }

    printf("All frames sent successfully\n");
    return 0;
}