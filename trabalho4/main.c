#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <semaphore.h>
#include <math.h>
// Descomente a linha abaixo para adicionar o intermediador e evitar deadlock
#define INTERMEDIATOR

#ifndef __GLIBC_USE_LIB_EXT1
    typedef int errno_t;
#endif

typedef enum {
    TypeA,
    TypeB,
} ColonyType;

typedef struct {
    int startingPopulation;
    int growthRate;
    int time;
    int threadCount;
    int resourceCount;
} InputFlags;

typedef struct {
    int colonyType;
    double startingPopulation;
    double growthRate;
    double currentPopulation;
    int time;
    int currentGeneration;
    sem_t* nutrients;
    sem_t* area;
    sem_t* intermediator;
    time_t elapsed;
    pid_t threadId;
    int threadCount;
    int resourceCount;

} ThreadArgs;

static struct option long_options[] =
{
    {"population", required_argument, NULL, 'p'},
    {"growth", required_argument, NULL, 'g'},
    {"time", required_argument, NULL, 't'},
    {"resources", required_argument, NULL, 'r'},
    {"threads", required_argument, NULL, 'c'},
    {"help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0}
};

errno_t handleInput(int argc, char **argv, InputFlags *inputFlags);
void* threadFunc(void *args);

int main(int argc, char **argv)
{
    srand(time(NULL));

    errno_t err;
    InputFlags inputFlags;

    err = handleInput(argc, argv, &inputFlags);
    if (err != 0) {
        return 1;
    }

    sem_t nutrients;
    sem_init(&nutrients, 0, inputFlags.resourceCount);

    sem_t area;
    sem_init(&area, 0, inputFlags.resourceCount);

    sem_t intermediator;
    sem_init(&intermediator, 0, inputFlags.resourceCount);

    ThreadArgs *threadArgs = malloc(sizeof(ThreadArgs) * inputFlags.threadCount);
    pthread_t **threads = malloc(sizeof(pthread_t*) * inputFlags.threadCount);

    for (int i = 0; i < inputFlags.threadCount; i++) {
        threads[i] = malloc(sizeof(pthread_t));
        threadArgs[i].colonyType = rand() % 2;
        threadArgs[i].startingPopulation = inputFlags.startingPopulation;
        threadArgs[i].growthRate = inputFlags.growthRate;
        threadArgs[i].time = inputFlags.time;
        threadArgs[i].currentPopulation = inputFlags.startingPopulation;
        threadArgs[i].currentGeneration = 1;
        threadArgs[i].nutrients = &nutrients;
        threadArgs[i].area = &area;
        threadArgs[i].intermediator = &intermediator;
        threadArgs[i].threadCount = inputFlags.threadCount;
        threadArgs[i].resourceCount = inputFlags.resourceCount;

        pthread_create(threads[i], NULL, threadFunc, &threadArgs[i]);
    }

    for (int i = 0; i < inputFlags.threadCount; i++) {
        pthread_join(*threads[i], NULL);
    }

    for (int i = 0; i <inputFlags.threadCount; i++) {
        printf("Colony type: %d\n", threadArgs[i].colonyType);
        printf("Starting population: %f\n", threadArgs[i].startingPopulation);
        printf("Growth rate: %f\n", threadArgs[i].growthRate);
        printf("Time: %d\n", threadArgs[i].time);
        printf("Final population: %f\n", threadArgs[i].currentPopulation);
        printf("Elapsed time: %ld\n", threadArgs[i].elapsed);
    }

    return 0;
}

errno_t handleInput(int argc, char **argv, InputFlags *inputFlags)
{
    int opt;
    bool missingStartingPopulation = true;
    bool missingGrowthRate = true;
    bool missingTime = true;
    bool missingResourceCount = true;

    // Default values
    inputFlags->threadCount = sysconf(_SC_NPROCESSORS_ONLN);
    //
    while ((opt = getopt_long(argc, argv, "p:g:t:r:c:h", long_options, NULL)) != -1)
    {
        switch (opt)
        {
        case 'p':
            inputFlags->startingPopulation = atof(optarg);
            missingStartingPopulation = false;
            break;
        case 'g':
            inputFlags->growthRate = atof(optarg);
            missingGrowthRate = false;
            break;
        case 't':
            inputFlags->time = atoi(optarg);
            missingTime = false;
            break;
        case 'r':
            inputFlags->resourceCount = atoi(optarg);
            missingResourceCount = false;
            break;
        case 'c':
            inputFlags->threadCount = atoi(optarg);
            break;
        case 'h':
            printf("Usage: %s [OPTIONS]\n", argv[0]);
            printf("Options:\n");
            printf("\t-p, --population POPULATION\t\tStarting population\n");
            printf("\t-g, --growth GROWTH_RATE\t\tGrowth rate\n");
            printf("\t-t, --time TOTAL_TIME\t\t\tTime\n");
            printf("\t-r, --resources RESOURCES_AMOUNT\tResource count\n");
            printf("\t-c, --threads THREAD_COUNT\t\tThread count\n");
            printf("\t-h, --help\t\t\t\tShow this help message\n");
            return EINVAL;
        default:
            break;
        }
    }

    if (missingStartingPopulation) {
        fprintf(stderr, "Missing starting population arg (-p)\n");
        return EINVAL;
    }

    if (missingGrowthRate) {
        fprintf(stderr, "Missing growth rate arg (-g)\n");
        return EINVAL;
    }

    if (missingTime) {
        fprintf(stderr, "Missing time arg (-t)\n");
        return EINVAL;
    }

    if (missingResourceCount) {
        fprintf(stderr, "Missing resource count arg (-r)\n");
        return EINVAL;
    }

    return EXIT_SUCCESS;
}

void *threadFunc(void *args)
{
    time_t initialTime = time(NULL);

    ThreadArgs *threadArgs = (ThreadArgs *)args;
    threadArgs->threadId = syscall(SYS_gettid);
    errno_t err;
    struct timespec timeout;
    while (threadArgs->currentGeneration <= threadArgs->time) {
        sleep(rand() % 2    );

        #ifdef INTERMEDIATOR
        sem_wait(threadArgs->intermediator);
        #endif

        timeout.tv_sec = time(NULL) + threadArgs->threadCount;
        if (threadArgs->colonyType == TypeA) {
            printf("%d is trying to get nutrients\n", threadArgs->threadId);
            err = sem_timedwait(threadArgs->nutrients, &timeout);
        } else {
            printf("%d is trying to get area\n", threadArgs->threadId);
            err = sem_timedwait(threadArgs->area, &timeout);
        }
        if (err != 0) {
            printf("%d detected a deadlock\n", threadArgs->threadId);
            break;
        }

        sleep(1);

        if (threadArgs->colonyType == TypeA) {
            printf("%d is trying to get area\n", threadArgs->threadId);
            err = sem_timedwait(threadArgs->area, &timeout);
        } else {
            printf("%d is trying to get nutrients\n", threadArgs->threadId);
            err = sem_timedwait(threadArgs->nutrients, &timeout);
        }
        if (err != 0) {
            printf("%d detected a deadlock\n", threadArgs->threadId);
            break;
        }

        #ifdef INTERMEDIATOR
        sem_post(threadArgs->intermediator);
        #endif

        threadArgs->currentPopulation += threadArgs->currentPopulation * (threadArgs->growthRate);

        sem_post(threadArgs->nutrients);
        sem_post(threadArgs->area);
        threadArgs->currentGeneration++;
    }
    threadArgs->elapsed = time(NULL) - initialTime;
}
