#include <stdio.h>
#include "scheduler.h"
#include "sync.h"

int main() {
    init_sync();
    
    PCB processes[] = {
        {1, 1, 5, 5, SYSTEM},
        {2, 3, 8, 8, INTERACTIVE},
        {3, 4, 6, 6, INTERACTIVE},
        {4, 7, 10, 10, BACKGROUND},
        {5, 8, 4, 4, BACKGROUND}
    };

    int process_count = sizeof(processes) / sizeof(PCB);

    printf("Hybrid CPU Scheduler Simulation\n");
    printf("--------------------------------\n\n");

    printf("Loaded Processes:\n");
    for (int i = 0; i < process_count; i++) {
        printf("P%d | Priority=%d | Burst=%d | Type=%d\n",
               processes[i].pid,
               processes[i].priority,
               processes[i].burst_time,
               processes[i].type);
    }

    run_scheduler(processes, process_count);

    destroy_sync();
    return 0;
}