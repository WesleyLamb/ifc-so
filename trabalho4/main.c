#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <math.h>

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
    time_t elapsed;

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

        pthread_create(threads[i], NULL, threadFunc, &threadArgs[i]);
    }

    for (int i = 0; i < inputFlags.threadCount; i++) {
        pthread_join(*threads[i], NULL);
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
    while (threadArgs->currentGeneration <= threadArgs->time) {
        sleep(rand() % 5);
        // if (threadArgs->colonyType == TypeA) {
        //     sem_wait(threadArgs->nutrients);
        // } else {
            sem_wait(threadArgs->area);
        // }

        // if (threadArgs->colonyType == TypeA) {
        //     sem_wait(threadArgs->area);
        // } else {
            sem_wait(threadArgs->nutrients);
        // }

        threadArgs->currentPopulation = threadArgs->currentPopulation * (1 + threadArgs->growthRate / 100.0);

        sem_post(threadArgs->nutrients);
        sem_post(threadArgs->area);
        threadArgs->currentGeneration++;;
    }
    threadArgs->elapsed = time(NULL) - initialTime;
    // printf("Colony type: %d\n", threadArgs->colonyType);
    // printf("Starting population: %d\n", threadArgs->startingPopulation);
    // printf("Growth rate: %d\n", threadArgs->growthRate);
    // printf("Time: %d\n", threadArgs->time);
    // printf("Current population: %d\n", threadArgs->currentPopulation);
}
