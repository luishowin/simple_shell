#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * read_cmd: reads the command entered
 * 
 * return 0
*/
#define MAX_INPUT_BUFFER_SIZE 1024

void read_cmd(char *command) {
    size_t len;  /* Declare size_t at the beginning of the block or function */
    printf("$ ");
    fgets(command, MAX_INPUT_BUFFER_SIZE, stdin);

    /* Remove newline character */
    len = strlen(command);
    if (len > 0 && command[len - 1] == '\n') {
        command[len - 1] = '\0';
    }
}

void execute_cmd(char *command) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
    } else if (pid == 0) {
        /* Child process */
        char *args[64]; /* Adjust the size based on your needs */
        int i = 0;

        /* Tokenize the command */
        char *token = strtok(command, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL; /* Null-terminate the argument list */

        /* Execute the command */
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process */
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally\n");
        }
    }
}

int main() {
    char command[MAX_INPUT_BUFFER_SIZE];

    while (1) {
        read_cmd(command);

        /* Exit the shell if the user enters "exit" */
        if (strcmp(command, "exit") == 0) {
            break;
        }

        execute_cmd(command);
    }

    return 0;
}