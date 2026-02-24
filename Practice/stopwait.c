#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define IDLE 0
#define WAIT_ACK 1
#define TIMEOUT 3

int errorSimulate(){
    return rand()%2;
}

int main (){
    int frame=0;
    int sequence=0;
    int state=IDLE;
    int totalFrames;

    printf("Enter the number of frames to be send:");
    scanf("%d",&totalFrames);

    srand(time(NULL));

    while (frame<totalFrames){

        if (state==IDLE){
            if (errorSimulate()){
                printf("Sender: The frame number %d (seq:%d) is sent successfully waiting for ack\n",frame,sequence);
                state=WAIT_ACK;
            }
            else{
                printf("Sender: Frame %d (seq:%d) is not sent. Resend the frame.\n",frame,sequence);
            }
        }
        else if (state==WAIT_ACK){
            if (errorSimulate()){
                printf("Receiver: The acknowlegdement of the frame %d (seq:%d) is successfull\n",frame,sequence);
                frame++;
                sequence=1-sequence;
            }
            else{
                sleep(TIMEOUT);
                printf("Receiver: The Acknowledment of frame %d (seq:%d) is not succesful. Frame is to be resend\n",frame,sequence);
            }
            state=IDLE;
        }
    }

    printf("All frammes sent successfully\n");
    return 0;

}