#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/neutrino.h>

int main(void)
{
    char smsg[200];
    char rmsg[200];
    int coid;
    long serv_pid;
    printf("prog client, Vvedite PID servera \n");
    scanf("%ld", &serv_pid);
    printf("Vveli %ld \n", serv_pid);
    coid = ConnectAttach(0, serv_pid, 1, 0, 0);
    if (coid == -1) {
        perror("ConnectAttach failed");
        return 1;
    }
    printf("ConnectAttach result %d\nVvedite soobshenie \n", coid);
    getchar();
    fgets(smsg, sizeof(smsg), stdin);
    size_t len = strlen(smsg);
    if(len > 0 && smsg[len-1]=='\n')
    {
        smsg[len-1] = '\0';
    }
    printf("Vveli %s \n", smsg);
    if(MsgSend(coid, smsg, strlen(smsg)+1, rmsg, sizeof(rmsg)) == -1)
    {
        printf("Error MsgSend \n");
        ConnectDetach(coid);
        return(-1);
    }
    printf("Otvet servera: %s\n", rmsg);
    ConnectDetach(coid);
    return(1);
}