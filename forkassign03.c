#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int count = 0;

    while (1) {
        pid_t pid = fork();

        if (pid < 0) {
            
            perror("Fork error");
            break;
        } else if (pid == 0) {
            
            exit(EXIT_SUCCESS);
        } else {
            
            count++;
            printf("Created child process %d with PID %d\n", count, pid);
        }
    }

    printf("Maximum number of child processes reached. Created %d child processes.\n", count);

    return 0;
}
