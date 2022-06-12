#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct process {
    int R1;
    int B1;
    int R2;
    int B2;
    char status[100];
    int timer;
} PROCESS;

void FIFO(int size, PROCESS * process) {
    int end = 1;
    int n = size;
    int cycle = 0;
    while (end != 0) {
        cycle += 1;
        printf("%-10d", cycle);
        int flag_all_ready = 1;
        int i;
        for (i = 0; i < size; i++) {
            if (strcmp(process[i].status, "Ready") != 0) {
                flag_all_ready = 0;
            }
        }
        if (flag_all_ready == 1) {
            strcpy(process[0].status, "Run");
            process[0].R1 -= 1;
            for (i = 0; i < size; i++) {
                printf("%-15s", process[i].status);
            }
            printf("\n");
            continue;
        }
        int flag_run = 0;
        for (i = 0; i < size; i++) {
            if (strcmp(process[i].status, "Run") == 0) {
                flag_run = 1;
            }
        }

        for (i = 0; i < size; i++) {
            if (strcmp(process[i].status, "Run") == 0) {
                if (process[i].R1 > 0) {
                    process[i].R1 -= 1;
                } else if (process[i].B1 > 0) {
                    process[i].B1 -= 1;
                    strcpy(process[i].status, "Block");
                    flag_run = 0;
                } else if (process[i].R2 > 0) {
                    process[i].R2 -= 1;
                } else if (process[i].B2 > 0) {
                    process[i].B2 -= 1;
                    strcpy(process[i].status, "Block");
                    flag_run = 0;
                }
            } else if (strcmp(process[i].status, "Ready") == 0) {
                if (flag_run == 0) {
                    flag_run = 1;
                    if (process[i].R1 > 0) {
                        process[i].R1 -= 1;
                        strcpy(process[i].status, "Run");
                    } else if (process[i].R2 > 0) {
                        process[i].R2 -= 1;
                        strcpy(process[i].status, "Run");
                    } else {
                        strcpy(process[i].status, "Terminate");
                    }
                }
            } else if (strcmp(process[i].status, "Block") == 0) {
                if (process[i].B1 > 0) {
                    process[i].B1 -= 1;
                } else if (process[i].R2 > 0) {
                    if (flag_run == 0) {
                        process[i].R2 -= 1;
                        strcpy(process[i].status, "Run");
                    } else {
                        strcpy(process[i].status, "Ready");
                    }
                } else if (process[i].B2 > 0) {
                    process[i].B2 -= 1;
                } else if (process[i].B2 <= 0) {
                    strcpy(process[i].status, "Ready");
                }
            } else if (strcmp(process[i].status, "Terminate") == 0) {
                n -= 1;
                strcpy(process[i].status, " ");
            }
        }
        if (flag_run == 0) {
            for (i = 0; i < size; i++) {
                if (strcmp(process[i].status, "Ready") == 0) {
                    if (process[i].R1 > 0) {
                        process[i].R1 -= 1;
                        strcpy(process[i].status, "Run");
                        break;
                    } if (process[i].R2 > 0) {
                        process[i].R2 -= 1;
                        strcpy(process[i].status, "Run");
                        break;
                    } else {
                        strcpy(process[i].status, "Terminate");
                    }
                }
            }
        }
        for (i = 0; i < size; i++) {
            printf("%-15s", process[i].status);
        }
        if (n == 0){
            end -= 1;
        }
        printf("\n");
    }
}

void RR(int size, int q, PROCESS * process) {
    int end = 1;
    int n = size;
    int cycle = 0;
    int i;
    while (end != 0) {
        cycle += 1;
        printf("%-10d", cycle);
        int flag_all_ready = 1;
        for (i = 0; i < size; i++) {
            if (strcmp(process[i].status, "Ready") != 0) {
                flag_all_ready = 0;
            }
        }
        if (flag_all_ready == 1) {
            strcpy(process[0].status, "Run");
            process[0].R1 -= 1;
            process[0].timer += 1;
            for (i = 0; i < size; i++) {
                printf("%-15s", process[i].status);
            }
            printf("\n");
            continue;
        }
        int flag_run = 0;
        for (i = 0; i < size; i++) {
            if (strcmp(process[i].status, "Run") == 0) {
                flag_run = 1;
            }
        }
        for (i = 0; i < size; i++) {
            if (strcmp(process[i].status, "Run") == 0) {
                if (process[i].timer < q) {
                    if (process[i].R1 > 0) {
                        process[i].R1 -= 1;
                        process[i].timer += 1;
                    } else if (process[i].B1 > 0) {
                        process[i].B1 -= 1;
                        process[i].timer = 0;
                        strcpy(process[i].status, "Block");
                        process[i].timer = 0;
                        flag_run = 0;
                    } else if (process[i].R2 > 0) {
                        process[i].R2 -= 1;
                        process[i].timer += 1;
                    } else if (process[i].B2 > 0) {
                        process[i].B2 -= 1;
                        process[i].timer = 0;
                        strcpy(process[i].status, "Block");
                        flag_run = 0;
                    }
                } else {
                    flag_run = 0;
                    process[i].timer = 0;
                    if (process[i].R1 > 0) {
                        strcpy(process[i].status, "Ready");
                    } else if (process[i].B1 > 0) {
                        process[i].B1 -= 1;
                        strcpy(process[i].status, "Block");
                    } else if (process[i].R2 > 0) {
                        strcpy(process[i].status, "Ready");
                    } else if (process[i].B2 > 0) {
                        process[i].B2 -= 1;
                        strcpy(process[i].status, "Block");
                    }
                }
            } else if (strcmp(process[i].status, "Ready") == 0) {
                if (flag_run == 0) {
                    flag_run = 1;
                    if (process[i].R1 > 0) {
                        process[i].R1 -= 1;
                        process[i].timer += 1;
                        strcpy(process[i].status, "Run");
                    } else if (process[i].R2 > 0) {
                        process[i].R2 -= 1;
                        process[i].timer += 1;
                        strcpy(process[i].status, "Run");
                    } else {
                        strcpy(process[i].status, "Terminate");
                    }
                }
            } else if (strcmp(process[i].status, "Block") == 0) {
                if (flag_run == 1) {
                    if (process[i].B1 > 0) {
                        process[i].B1 -= 1;
                    }
                    else if (process[i].B1 == 0) {
                        process[i].B1 -= 1;
                        strcpy(process[i].status, "Ready");
                    }
                    else if (process[i].B2 > 0) {
                        process[i].B2 -= 1;
                    } else {
                        strcpy(process[i].status, "Terminate");
                    }
                } else {
                    if (process[i].B1 > 0) {
                        process[i].B1 -= 1;
                    } else if (process[i].B1 == 0) {
                        flag_run = 1;
                        process[i].B1 -= 1;
                        process[i].R2 -= 1;
                        process[i].timer += 1;
                        strcpy(process[i].status, "Run");
                    } else if (process[i].B2 > 0) {
                        process[i].B2 -= 1;
                    } else if (process[i].B2 <= 0) {
                        strcpy(process[i].status, "Terminate");
                    }
                }
            } else if (strcmp(process[i].status, "Terminate") == 0) {
                n -= 1;
                strcpy(process[i].status, " ");
            }
        }

        if (flag_run == 0) {
            for (i = 0; i < size; i++) {
                if (strcmp(process[i].status, "Ready") == 0) {
                    if (process[i].R1 > 0) {
                        strcpy(process[i].status, "Run");
                        process[i].R1 -= 1;
                        process[i].timer += 1;
                        break;
                    } if (process[i].R2 > 0) {
                        strcpy(process[i].status, "Run");
                        process[i].R2 -= 1;
                        process[i].timer += 1;
                        break;
                    } else {
                        strcpy(process[i].status, "Terminate");
                    }
                }
            }
        }

        for (i = 0; i < size; i++) {
            printf("%-15s", process[i].status);
        }
        if (n == 0){
            end -= 1;
        }
        printf("\n");

    }
}

int main(int argc, char *argv[]) {
    printf("This program simulates two scheduling methods: FIFO and RR.\n");
    printf("If you type in 1 as SA, then what shown below is the result of FIFO scheduling.\n");
    printf("If you type in 2 as SA, then what shown below is the result of RR scheduling.\n");
    int n = atoi(argv[1]);
    int SA = atoi(argv[2]);
    printf("Cycle     ");
    int i;
    for (i = 0; i < n ; i++) {
        printf("P%d State       ", i+1);
    }
    printf("\n");
    PROCESS * processlist = malloc(sizeof(PROCESS) *  n);
    if (SA == 1) {
        for (i = 0; i < n; i++) {
            processlist[i].R1 = atoi(argv[i*4+3]);
            processlist[i].B1 = atoi(argv[i*4+4]);
            processlist[i].R2 = atoi(argv[i*4+5]);
            processlist[i].B2 = atoi(argv[i*4+6]);
            processlist[i].timer = 0;
            strcpy(processlist[i].status, "Ready");
        }
        FIFO(n, processlist);
    } else if (SA == 2) {
        int q = atoi(argv[3]);
        for (i = 0; i < n; i++) {
            processlist[i].R1 = atoi(argv[i*4+4]);
            processlist[i].B1 = atoi(argv[i*4+5]);
            processlist[i].R2 = atoi(argv[i*4+6]);
            processlist[i].B2 = atoi(argv[i*4+7]);
            processlist[i].timer = 0;
            strcpy(processlist[i].status, "Ready");
        }
        RR(n, q, processlist);
    }
    return 0;
}
