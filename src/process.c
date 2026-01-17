#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include "process.h"
#include "sync.h"

void* thread_execution(void* arg) {
    PCB* process = (PCB*)arg;

    pthread_mutex_lock(&exec_mutex);
    execution_count++;
    printf("Thread started for P%d | Execution Count = %d\n",
           process->pid, execution_count);
    pthread_mutex_unlock(&exec_mutex);

    printf("Executing P%d for %d seconds\n",
           process->pid, process->burst_time);

    sleep(process->burst_time);

    pthread_mutex_lock(&exec_mutex);
    printf("Thread completed for P%d\n", process->pid);
    pthread_mutex_unlock(&exec_mutex);

    return NULL;
}

void execute_process(PCB process) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return;
    }

    if (pid == 0) {
        // Child process
        printf("\nChild Process Created: P%d (OS PID=%d)\n",
               process.pid, getpid());

        pthread_t thread;

        // Create thread inside child
        pthread_create(&thread, NULL, thread_execution, &process);

        // Wait for thread to finish
        pthread_join(thread, NULL);

        printf("Process P%d completed execution\n", process.pid);
        exit(0);
    }
    else {
        // Parent waits for child
        wait(NULL);
    }
}