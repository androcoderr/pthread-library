#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond_var;
int shared_data = 0;
void* waiter(void* arg) {
    pthread_mutex_lock(&mutex);
    while (shared_data < 10) {
        printf("Waiter: waiting for condition...\n");
        pthread_cond_wait(&cond_var, &mutex);
    }
    printf("Waiter: condition met, shared_data = %d\n", shared_data);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* incrementer(void* arg) {
    sleep(2);
    pthread_mutex_lock(&mutex);
    shared_data = 10;
    printf("Incrementer: updated shared_data to %d\n", shared_data);
    pthread_cond_signal(&cond_var);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_var, NULL);

    pthread_create(&thread1, NULL, waiter, NULL);
    pthread_create(&thread2, NULL, incrementer, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_var);

    return 0;
}
