## CSCI-UA 202 Lab01

*Yuheng Lu, yl7789, March 2022*

1. To compile main.c file, run the command:
   - cc -o lab01 main.c
2. To run the complied file, run the command:
   - ./lab01
   - Then, type in the command following the format in lab document.
3. The following type 1 commands are supported:
   - hello: Respond by printing a friendly greeting.
   - bye: Acknowledge the command and terminate the run.
   - assignment: Print 202 lab #1 (Spring 2022).
   - author: Print name, N-number, and netid.
   - section: Print 002.
3. Type 2 commands are supported as well.
   Type 2 commands are defined by: commands not built into my shell but are internal to Unix.
5. The texts "Parent process #" and "Child process #" shown on the interface indicate whether the process is executed as a parent process or child process. A wrong command (not type 1 or type 2) might cause a fork behavior with corresponding "Child process #".
