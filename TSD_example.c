#include <stdio.h>
#include <pthread.h>

pthread_key_t tsd_key;
char *address;
void destructor(void *value) {
    printf("Destructor called, value: %d\n", value);
    free(value);
}

void* thread_function(void* arg) {
    char *name = (char *)malloc(20);
    address = name;
    printf("Address : %d\n",address);
    strcpy(name,"Omer Ayana");
    pthread_setspecific(tsd_key, (void *)name);

    void* value = pthread_getspecific(tsd_key);
    printf("Thread ID: %lu, TSD value: %s\n", pthread_self(), (char*)value);

    return NULL;
}

int main() {
    pthread_key_create(&tsd_key, destructor);
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread_function, NULL);
    pthread_create(&thread2, NULL, thread_function, NULL);
    sleep(1);
    printf("Value : %s",address);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_key_delete(tsd_key);
    return 0;
}
