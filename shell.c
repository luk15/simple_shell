#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LEN 256

int main() {
    char command[MAX_LEN];
    int status;

    while(1) {
        printf("simple_shell> ");
        if (fgets(command, MAX_LEN, stdin) == NULL) {
            printf("\nExiting...\n");
            exit(0);
        }
        command[strcspn(command, "\n")] = 0;

        pid_t pid = fork();
        if (pid == 0) {
            execlp(command, command, (char *) NULL);
            printf("Error: command not found\n");
            exit(0);
        } else if (pid > 0) {
            wait(&status);
        } else {
            printf("Error: fork failed\n");
        }
    }

    return 0;
}