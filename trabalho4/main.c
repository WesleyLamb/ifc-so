#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

#ifndef __GLIBC_USE_LIB_EXT1
    typedef int errno_t;
#endif

typedef

typedef struct {
    int startingPopulation;
    int growthRate;
    int time;
    int threadCount;
    int resourceCount;
} InputFlags;

typedef struct {
    int startingPopulation;
    int growthRate;
    int time;

} ThreadArgs;

errno_t handleInput(int argc, char **argv, InputFlags *inputFlags);

int main(int argc, char **argv)
{
    srand(time(NULL));

    errno_t err;
    InputFlags inputFlags;

    pthread_t **threads;

    err = handleInput(argc, argv, &inputFlags);
    if (err != 0) {
        return 1;
    }

    threads = malloc(sizeof(pthread_t*) * inputFlags.threadCount);
    for (int i = 0; i < inputFlags.threadCount; i++) {
        threads[i] = malloc(sizeof(pthread_t));
        pthread_create(threads[i], NULL, NULL, NULL);
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

    while ((opt = getopt(argc, argv, "p:g:t:r:c:")) != -1)
    {
        switch (opt)
        {
        case 'p':
            inputFlags->startingPopulation = atoi(optarg);
            missingStartingPopulation = false;
            break;
        case 'g':
            inputFlags->growthRate = atoi(optarg);
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
