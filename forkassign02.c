#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void runProcess(char processName) {
    pid_t pid = getpid();
    printf("Process %c with PID %d is running for 5 seconds...\n", processName, pid);
    sleep(5);
    printf("Process %c with PID %d completed.\n", processName, pid);
}

int main() {
    pid_t childB, childC, childD;

    // Parent process A
    printf("Parent Process A with PID %d is running...\n", getpid());

    
    childB = fork();

    if (childB < 0) {
        perror("Fork error for Process B");
        exit(EXIT_FAILURE);
    } else if (childB == 0) {
        
        runProcess('B');

        
        childC = fork();

        if (childC < 0) {
            perror("Fork error for Process C");
            exit(EXIT_FAILURE);
        } else if (childC == 0) {
            
            runProcess('C');

            
            childD = fork();

            if (childD < 0) {
                perror("Fork error for Process D");
                exit(EXIT_FAILURE);
            } else if (childD == 0) {
            
                runProcess('D');
                exit(EXIT_SUCCESS);
            }

            
            waitpid(childD, NULL, 0);
            exit(EXIT_SUCCESS);
        }

        
        waitpid(childC, NULL, 0);
        exit(EXIT_SUCCESS);
    }

    
    waitpid(childB, NULL, 0);

    printf("Parent Process A completed.\n");

    return 0;
}
