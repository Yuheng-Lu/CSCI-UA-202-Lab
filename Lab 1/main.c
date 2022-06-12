#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
void instruction();

int main() {
    instruction();
    printf("Lab 1:\n");
    char command[50];
    while (1) {
        printf("\nParent process %d\n", getpid());
        fgets(command, 50, stdin);
        command[strlen(command)-1] = '\0';
        if (strcmp(command, "hello") == 0 || strcmp(command, "bye") == 0 || strcmp(command, "assignment") == 0 || strcmp(command, "author") == 0 || strcmp(command, "section") == 0) {
            if (strcmp(command, "hello") == 0) {
                printf("Hello User! Welcome!\n");
            } else if (strcmp(command, "bye") == 0) {
                exit(0);
            } else if (strcmp(command, "assignment") == 0) {
                printf("202 lab #1 (Spring 2022)\n");
            } else if (strcmp(command, "author") == 0) {
                printf("Name: Yuheng Lu\nN-number: N10242133\nNetID: yl7789\n");
            } else if (strcmp(command, "section") == 0) {
                printf("002\n");
            }
        } else {
            int parentOrChild = fork();
            if (parentOrChild == 0) {
                printf("Child process %d\n", getpid());
                char *argv[] = {command, NULL};
                char dest[50] = "/bin/";
                strcat(dest, command);
                execve(dest, argv, NULL);
                exit(2);
            } else {
                int status;
                wait(&status);
            }
        }

    }
}
void instruction() {
    printf("This program implements an extremely limited shell.\n");
    printf("The following type 1 commands are supported (one word per command and one line per command):\n");
    printf("-----------------------------------------------------------------\n");
    printf("%-1s%-17s%-46s%-1s\n", "|", "Command:", "What it can do?", "|");
    printf("%-1s%-17s%-46s%-1s\n", "|", "hello", "Respond by printing a friendly greeting.", "|");
    printf("%-1s%-17s%-46s%-1s\n", "|", "bye", "Acknowledge the command and terminate the run.",  "|");
    printf("%-1s%-17s%-46s%-1s\n", "|", "assignment", "Print 202 lab #1 (Spring 2022).",  "|");
    printf("%-1s%-17s%-46s%-1s\n", "|", "author", "Print name, N-number, and netid.",  "|");
    printf("%-1s%-17s%-46s%-1s\n", "|", "section", "Print 002 (which is the section I am in)",  "|");
    printf("-----------------------------------------------------------------\n");
    printf("Type 2 commands are also supported.\nType 2 commands are defined by: commands not built into my shell but are internal to Unix.\n");
}