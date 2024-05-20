#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 2
float Salaries[] = {1000 ,1500};
pthread_mutex_t salaries_mutex[2];
bool IsRead[2] = {false, false};

void *increase(void *) {
    pthread_mutex_lock(&salaries_mutex[0]);
    Salaries[0] += 100;
    sleep(5);
    Salaries[0] *= 1.1;
    pthread_mutex_unlock(&salaries_mutex[0]);
    return 0;
}

void *readSalary(void *) {
    int count = 0;
    int i = 0;
    while(count != SIZE)
    {
        if (IsRead[i]== false && pthread_mutex_trylock(&salaries_mutex[i]) == 0) {
            float newSalary1 = Salaries[i];
            pthread_mutex_unlock(&salaries_mutex[i]);
            printf("Salary %d: %f\n",i+1, newSalary1);
            count++;
            IsRead[i] = true;
        }
        i++;
        if(i== SIZE)
            i = 0;
        sleep(1);
    }
    return 0;
}

int main() {
    pthread_t th1, th2;

    for(int i = 0; i< SIZE;i++)
        pthread_mutex_init(&salaries_mutex[i], NULL);

    pthread_create(&th1, NULL, increase, NULL);
    pthread_create(&th2, NULL, readSalary, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    for(int i = 0; i< SIZE;i++)
        pthread_mutex_destroy(&salaries_mutex[i]);

    printf("Exiting from main\n");
    return 0;
}
