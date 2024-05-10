#ifndef BIN_COMMANDS_H
#define BIN_COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define AUTO_CLEAN_INTERVAL (60 * 10 * 1)

void addToBasket(const char* filename);
void restoreFromBasket();
void clearBasket();
void displayBasketInfo();
void autoCleanBasket();

#endif /* BIN_COMMANDS_H */
