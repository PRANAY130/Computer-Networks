#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAXFRAMES 100

int windowSize, totalFrames;

void sendFrames(int start, int end){
    for (int i=start; i<end; i++){
        printf("Sending frame %d\n",i);
        sleep(1);
    }
}

int main(){

    srand(time(0));
    printf("Enter the number of Frames to be transfered:");
    scanf("%d",&totalFrames);

    printf("Enter the window Size:");
    scanf("%d",&windowSize);

    if (windowSize>totalFrames || totalFrames>MAXFRAMES){
        printf("Invalid InPut! Try again");
        return 1;
    }

    int base=0;

    while(base<totalFrames){
        int end;

        if (base+windowSize<totalFrames){
            end=base+windowSize;
        }
        else{
            end=totalFrames;
        }

        sendFrames(base,end);

        int ack=base+(rand()%windowSize+1);

        if (ack>=end){
            printf("Frames from %d to %d is tranfered successfully\n",base,end-1);
            base=end;
        }

        else{
            printf("Error in sending frame %d \n.Resending from Frame %d\n",ack,ack);
            base=ack;
        }
    }
    printf("All frames are send successfully\n");

    return 0;

}