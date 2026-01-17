#ifndef SYNC_H
#define SYNC_H

#include <pthread.h>

// Mutex for shared resource
extern pthread_mutex_t exec_mutex;

// Shared execution counter
extern int execution_count;

void init_sync();
void destroy_sync();

#endif