#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() 
{
    pid_t p = fork();

    if (p < 0) 
    {
        perror("Fork fail");
        return -1;
    } else if (p == 0) {
        printf("Hello from child, process_ID (pid): %d\n", getpid());
    } else {
        printf("Hello from parent, process_id (pid): %d\n", getpid());
    }
    return 1;
}