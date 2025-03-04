#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <unistd.h>
#include <sys/neutrino.h>

void server(void)
{
    int rcvid;
    int chid;
    char message[512];

    printf("Server start working \n");

    chid = ChannelCreate(0);
    printf("Channel id: %d \n", chid);
    printf("Pid: %d \n", getpid());

    while(1)
    {
        rcvid = MsgReceive(chid, message, sizeof(message), NULL);
        if(rcvid == -1)
        {
            perror("MsgReceive");
            exit(1);
        }
        printf("Poluchili soobshenie, rcvid: %X \n", rcvid);
        printf("Soobshenie takoe: \"%s\". \n", message);

        strcpy(message, "Eto otvet");
        MsgReply(rcvid, EOK, message, strlen(message));
        printf("\"%s\". \n", message);
    }
    ChannelClose(chid);
}

int main(void)
{
    printf("Prog server \n");
    server();
    sleep(5);
    return(1);
}