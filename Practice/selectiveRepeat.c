#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAXFRAMES 100

int totalFrames, windowSize;
int ackArray[MAXFRAMES];

void sendFrame(int i){
    printf("Frame %d is send\n",i);
    sleep(1);
}

int main(){
    printf("Enter the total number of frames to be sent:");
    scanf("%d",&totalFrames);

    printf("Enter the window size:");
    scanf("%d",&windowSize);

    for (int i=0; i<totalFrames; i++){
        ackArray[i]=0;
    }

    int base=0;

    while (base<totalFrames){
        int end;

        if(base+windowSize<totalFrames){
            end=base+windowSize;
        }
        else{
            end=totalFrames;
        }

        for (int i=base; i<end; i++){
            if (ackArray[i]==0){
                sendFrame(i);

                int error=rand()%2;

                if (error){
                    printf("Frame %d is sent Successfully\n",i);
                    ackArray[i]=1;
                }
                else{
                    printf("Frame %d is lost\n",i);
                }
            }
        }

        while (base<totalFrames && ackArray[base]==1){
            base++;
        }
    }

    printf("All frames are sent successfully\n");

    return 0;
}