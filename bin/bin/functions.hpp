#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

void createBasketFolder();
void addToBasket(const std::string& filename);
void restoreFromBasket();
void clearBasket();
void displayBasketInfo();
void autoCleanBasket(int maxMemoryUsage, int autoCleanInterval);


const std::string BASKET_FOLDER = "/Users/pavelshcherbo/Desktop/stud/bin";
const int AUTO_CLEAN_INTERVAL = 60 * 1 * 1; // Auto clean interval in seconds (24 hours)
const int MAX_MEMORY_USAGE = 1000000000; // Maximum memory usage in bytes (1 GB)

#endif
