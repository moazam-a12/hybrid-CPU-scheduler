#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"
#include "process.h"

int compare_priority(const void* a, const void* b) {
    PCB* p1 = (PCB*)a;
    PCB* p2 = (PCB*)b;
    return p1->priority - p2->priority;
}

void schedule_fcfs(PCB processes[], int count) {
    printf("\n--- FCFS Scheduling ---\n");
    for (int i = 0; i < count; i++) {
        execute_process(processes[i]);
    }
}

void schedule_priority(PCB processes[], int count) {
    printf("\n--- Priority Scheduling ---\n");

    qsort(processes, count, sizeof(PCB), compare_priority);

    for (int i = 0; i < count; i++) {
        execute_process(processes[i]);
    }
}

void schedule_round_robin(PCB processes[], int count) {
    printf("\n--- Round Robin Scheduling (Quantum = %d) ---\n", TIME_QUANTUM);

    int completed;
    do {
        completed = 1;

        for (int i = 0; i < count; i++) {
            if (processes[i].remaining_time > 0) {
                completed = 0;

                int exec_time =
                    (processes[i].remaining_time > TIME_QUANTUM)
                    ? TIME_QUANTUM
                    : processes[i].remaining_time;

                PCB temp = processes[i];
                temp.burst_time = exec_time;

                execute_process(temp);

                processes[i].remaining_time -= exec_time;

                printf("Scheduler: P%d remaining time = %d\n",
                       processes[i].pid,
                       processes[i].remaining_time);
            }
        }
    } while (!completed);
}

void classify_and_schedule(PCB process) {
    if (process.type == SYSTEM) {
        printf("\nProcess P%d → Priority Scheduling\n", process.pid);
    }
    else if (process.type == INTERACTIVE) {
        printf("\nProcess P%d → Round Robin Scheduling\n", process.pid);
    }
    else {
        printf("\nProcess P%d → FCFS Scheduling\n", process.pid);
    }

    execute_process(process);
}

void run_scheduler(PCB processes[], int count) {
    PCB system[count], interactive[count], background[count];
    int s = 0, i = 0, b = 0;

    for (int k = 0; k < count; k++) {
        if (processes[k].type == SYSTEM)
            system[s++] = processes[k];
        else if (processes[k].type == INTERACTIVE)
            interactive[i++] = processes[k];
        else
            background[b++] = processes[k];
    }

    schedule_priority(system, s);
    schedule_round_robin(interactive, i);
    schedule_fcfs(background, b);

    printf("\nAll processes completed successfully.\n");
}