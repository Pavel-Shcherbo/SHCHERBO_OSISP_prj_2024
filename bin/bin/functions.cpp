#include "functions.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <sstream>

const std::string BASKET_FOLDER = "/Users/pavelshcherbo/Desktop/stud/bin";

void createBasketFolder() {
    mkdir(BASKET_FOLDER.c_str(), 0777);
}

void addToBasket(const std::string& filename) {
    std::string newFilename = BASKET_FOLDER + "/" + filename.substr(filename.find_last_of("/") + 1);
    if (rename(filename.c_str(), newFilename.c_str()) != 0) {
        std::cerr << "Ошибка перемещения файла в корзину!" << std::endl;
        return;
    }

    time_t now = time(0);
    tm* ltm = localtime(&now);

    std::string infoFilename = BASKET_FOLDER + "/" + "bin.info";
    std::ofstream basketInfo(infoFilename, std::ios::app);
    if (!basketInfo) {
        std::cerr << "Ошибка открытия файла корзины!" << std::endl;
        return;
    }

    basketInfo << filename << " " << newFilename << " "
               << std::setw(2) << std::setfill('0') << ltm->tm_mday << '.'
               << std::setw(2) << std::setfill('0') << 1 + ltm->tm_mon << '.'
               << 1900 + ltm->tm_year << std::endl;

    basketInfo.close();
}

void restoreFromBasket() {
    std::string infoFilename = BASKET_FOLDER + "/" + "bin.info";
    std::ifstream basketInfo(infoFilename);
    if (!basketInfo) {
        std::cerr << "Ошибка открытия файла корзины!" << std::endl;
        return;
    }

    std::string originalFilename, newFilename, date;
    while (basketInfo >> originalFilename >> newFilename >> date) {
        std::cout << "Восстановление файла: " << originalFilename << std::endl;
        
        date.erase(0, 13);

        if (rename(newFilename.c_str(), originalFilename.c_str()) != 0) {
            std::cerr << "Ошибка восстановления файла!" << std::endl;
        }
    }

    basketInfo.close();

    std::ofstream clearBasketInfo(infoFilename);
    if (!clearBasketInfo) {
        std::cerr << "Ошибка открытия файла корзины!" << std::endl;
        return;
    }
    clearBasketInfo.close();
}


void clearBasket() {
    std::string infoFilename = BASKET_FOLDER + "/" + "bin.info";
    std::ifstream basketInfo(infoFilename);
    if (!basketInfo) {
        std::cerr << "Ошибка открытия файла корзины!" << std::endl;
        return;
    }

    std::string originalFilename, newFilename, date;
    while (basketInfo >> originalFilename >> newFilename >> date) {
        std::cout << "Удаление файла из корзины: " << originalFilename << std::endl;

        if (unlink(newFilename.c_str()) != 0) {
            std::cerr << "Ошибка удаления файла из корзины!" << std::endl;
        }
    }

    basketInfo.close();

    std::ofstream clearBasketInfo(infoFilename);
    if (!clearBasketInfo) {
        std::cerr << "Ошибка открытия файла корзины!" << std::endl;
        return;
    }
    clearBasketInfo.close();
}

void displayBasketInfo() {
    std::string infoFilename = BASKET_FOLDER + "/" + "bin.info";
    std::ifstream basketInfo(infoFilename);
    if (!basketInfo) {
        std::cerr << "Ошибка открытия файла корзины!" << std::endl;
        return;
    }

    std::string line;
    while (getline(basketInfo, line)) {
        std::cout << "Файл в корзине: " << line << std::endl;
    }

    basketInfo.close();
}
