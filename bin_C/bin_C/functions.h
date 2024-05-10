#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

#define BASKET_FOLDER "/Users/pavelshcherbo/Desktop/stud/bin"
#define AUTO_CLEAN_INTERVAL (60 * 10 * 1) // Auto clean interval in seconds (10 minutes)
#define MAX_MEMORY_USAGE 1000000000     // Maximum memory usage in bytes (1 GB)

typedef struct {
    char action[20];
    char filename[1024];
    time_t timestamp;
} Action;

void logAction(const char* action, const char* filename);
void createBasketFolder();
void addToBasket(const char* filename);
void restoreFromBasket();
void clearBasket();
void displayBasketInfo();
void autoCleanBasket();
void* autoCleanThread(void* arg);

#endif /* FUNCTIONS_H */
