#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_function(void* arg) {
    printf("Thread is running\n");
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_attr_t attr;
    size_t stack_size;
    size_t guard_size = 4096;
    pthread_attr_init(&attr);
    pthread_attr_getstacksize(&attr, &stack_size);
    printf("Default stack size = %zu bytes\n", stack_size);
    stack_size = 1024 * 1024;
    pthread_attr_setstacksize(&attr, stack_size);
    pthread_attr_setguardsize(&attr, guard_size);
    pthread_create(&thread, &attr, thread_function, NULL);
    pthread_join(thread, NULL);
    pthread_attr_destroy(&attr);
    printf("Thread finished\n");
    return 0;
}
