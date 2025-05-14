#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/neutrino.h>

int is_not_consonant(char c)
{
    c = tolower(c);
    if (!isalpha(c)) return 1;
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

// Переименовали функцию
void filter_non_consonants(const char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (is_not_consonant(input[i])) {
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
    char non_consonants[512];

    printf("Server start working \n");

    chid = ChannelCreate(0);
    if (chid == -1) {
        perror("ChannelCreate failed");
        exit(1);
    }
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
        filter_non_consonants(message, non_consonants);
        printf("Ne soglasnie: \"%s\". \n", non_consonants);

        if(MsgReply(rcvid, EOK, non_consonants, strlen(non_consonants)+1) == -1){
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
    return(EXIT_SUCCESS);
}