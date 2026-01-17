#ifndef COMMON_H
#define COMMON_H

// process type
#define SYSTEM 0
#define INTERACTIVE 1
#define BACKGROUND 2

#define TIME_QUANTUM 2   // seconds

// PCB
typedef struct {
    int pid;              // process ID
    int priority;         // lower = high priority
    int burst_time;       // total CPU burst time
    int remaining_time;   // Round Robin
    int type;             // SYSTEM / INTERACTIVE / BACKGROUND
} PCB;

#endif