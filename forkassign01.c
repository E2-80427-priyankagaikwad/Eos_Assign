#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num_children = 5;

    for (int i = 0; i < num_children; ++i) {
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            // Child process
            printf("Child %d with PID %d started.\n", i + 1, getpid());
            sleep(5); // Child runs for 5 seconds
            printf("Child %d with PID %d completed.\n", i + 1, getpid());
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process
    int status;
    pid_t wpid;
    
    while ((wpid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            printf("Child with PID %d exited with status %d.\n", wpid, WEXITSTATUS(status));
        } else {
            printf("Child with PID %d terminated abnormally.\n", wpid);
        }
    }

    return 0;
}
