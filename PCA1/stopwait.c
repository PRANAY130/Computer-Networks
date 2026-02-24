#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TIMEOUT 3
#define IDLE 0
#define WAIT_ACK 1

int simulate_error(){
    return rand()%2;
}

int main(){
    int state=IDLE;
    int seq=0;
    int frame=0;
    int total_frame=5;

    srand(time(NULL));

    while(frame<total_frame){

        if(state==IDLE){
            if(simulate_error()){
                printf("Sender: Frame %d sent successfully (seq=%d)\n",frame,seq);
                state=WAIT_ACK;
            } else {
                printf("Sender: Frame %d lost (seq=%d)\n",frame,seq);
            }
        }

        if(state==WAIT_ACK){
            if(simulate_error()){
                printf("Receiver: ACK of Frame %d received (seq=%d)\n",frame,seq);
                frame++;
                seq=1-seq;
            } else {
                sleep(TIMEOUT);
                printf("Receiver: ACK lost of frame %d (seq=%d)\n",frame,seq);
            }
            state=IDLE;
        }
    }

    printf("All frames transmitted successfully.\n");
}