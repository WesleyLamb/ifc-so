#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define QTDE_TRIBAIS 5
#define TAM_CALDEIRAO 10

typedef struct {
    sem_t *semaphore;
    pthread_mutex_t *cauldronMutex;
    pthread_mutex_t *chefMutex;
} ThreadArgs;

void* tribalThreadFunc(void* argp);
void* tribalChefThreadFunc(void* argp);

int main() {
    srand(time(NULL));
    ThreadArgs threadArgs;
    sem_t semaphore;
    pthread_mutex_t cauldronMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t chefMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_t tribalThread[QTDE_TRIBAIS];
    pthread_t tribalChefThread;
    sem_init(&semaphore, 0, 0);

    threadArgs.semaphore = &semaphore;
    threadArgs.cauldronMutex = &cauldronMutex;
    threadArgs.chefMutex = &chefMutex;


    for (int i = 0; i < QTDE_TRIBAIS; i++) {
        pthread_create(&tribalThread[i], NULL, tribalThreadFunc, (void*) &threadArgs);
    }

    pthread_create(&tribalChefThread, NULL, tribalChefThreadFunc, (void*) &threadArgs);

    for (int i = 0; i < QTDE_TRIBAIS; i++) {
        pthread_join(tribalThread[i], NULL);
    }

    pthread_join(tribalChefThread, NULL);

    return 0;
}

void *tribalThreadFunc(void *argp)
{
    ThreadArgs *args = (ThreadArgs*) argp;
    int avail;
    while (1) {
        // A mimir
        sleep(rand() % 10);
        // Se aproximou do caldeirão
        pthread_mutex_lock(args->cauldronMutex);
        sem_getvalue(args->semaphore, &avail);
        if (avail == 0) {
            printf("Acabou a comida, alguém vai acordar o chef\n");
            pthread_mutex_unlock(args->chefMutex);
        }
        sem_wait(args->semaphore);
        sem_getvalue(args->semaphore, &avail);
        printf("Alguém comeu, sobrou %d\n", avail);
        pthread_mutex_unlock(args->cauldronMutex);

        // printf("Tribal %d went to bed\n", pthread_self());
        // sleep(rand() % 5);
        // printf("Tribal %d wakes up\n", pthread_self());
        // pthread_mutex_lock(args->cauldronMutex);
        // printf("Tribal %d aproaches the cauldron\n", pthread_self());
        // sem_getvalue(args->semaphore, &avail);
        // if (avail == 0) {
        //     printf("Tribal %d wakes chef because there is no food\n", pthread_self());
        //     pthread_mutex_unlock(args->chefMutex);
        // }
        // printf("Tribal %d is going to take food\n", pthread_self());
        // sem_wait(args->semaphore);
        // printf("Tribal's %d tummy is full\n", pthread_self());
        // pthread_mutex_unlock(args->cauldronMutex);
    }
    return NULL;
}

void *tribalChefThreadFunc(void *argp)
{
    ThreadArgs *args = (ThreadArgs*) argp;
    int i = 0;
    while (1) {
        pthread_mutex_lock(args->chefMutex);
        for (i = 0; i < TAM_CALDEIRAO; i++) {
            sem_post(args->semaphore);
        }
        printf("Chef fez %d porções\n", TAM_CALDEIRAO);
    }

    return NULL;
}
