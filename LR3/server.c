#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/neutrino.h>

int is_consonant(char c)
{
    c = tolover(c);
    if (!isalpha(c)) return 0;
    return c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'y';
}
void filter_consonants(const char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (is_consonant(input[i])) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
}

void server(void)
{
    int rcvid;
    int chid;
    char message[512];
    char consonants[512];

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
        filter_consonants(message, consonants);
        printf("Soglasnie: \"%s\". \n", consonants);

        if(MsgReply(rcvid, EOK, consonants, strlen(consonants)+1) == -1){
            perror("MsgReply error");
        }
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