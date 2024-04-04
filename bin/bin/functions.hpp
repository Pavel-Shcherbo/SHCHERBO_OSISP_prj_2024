#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

void createBasketFolder();
void addToBasket(const std::string& filename);
void restoreFromBasket();
void clearBasket();
void displayBasketInfo();

#endif
