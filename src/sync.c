#include "sync.h"

pthread_mutex_t exec_mutex;
int execution_count = 0;

void init_sync() {
    pthread_mutex_init(&exec_mutex, NULL);
}

void destroy_sync() {
    pthread_mutex_destroy(&exec_mutex);
}