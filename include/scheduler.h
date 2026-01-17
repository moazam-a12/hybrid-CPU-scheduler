#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "common.h"

void schedule_fcfs(PCB processes[], int count);
void schedule_priority(PCB processes[], int count);
void schedule_round_robin(PCB processes[], int count);

void run_scheduler(PCB processes[], int count);
void classify_and_schedule(PCB process);

#endif