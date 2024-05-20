#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
float salary = 1000;
//pthread_mutex_t salary_mutex;

void *increase(void *) {
  //  pthread_mutex_lock(&salary_mutex);
    salary += 100;
    sleep(5);
    salary *= 1.1;
 //   pthread_mutex_unlock(&salary_mutex);
    return 0;
}

void *readSalary(void *) {
    sleep(1);
  //  pthread_mutex_lock(&salary_mutex);
    float newSalary = salary;
 //   pthread_mutex_unlock(&salary_mutex);
    printf("Salary : %f\n", newSalary);
    return 0;
}

int main() {
    pthread_t th1, th2;

    //pthread_mutex_init(&salary_mutex, NULL);
    //salary_mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_create(&th1, NULL, increase, NULL);
    pthread_create(&th2, NULL, readSalary, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

  //  pthread_mutex_destroy(&salary_mutex);

    printf("Exiting from main\n");
    return 0;
}
