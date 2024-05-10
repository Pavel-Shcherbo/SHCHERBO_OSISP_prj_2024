#include "binCommands.h"
#include "logActions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define BASKET_FOLDER "/Users/pavelshcherbo/Desktop/stud/bin"
#define MAX_FILENAME_LENGTH 1024
#define AUTO_CLEAN_INTERVAL (60 * 10 * 1)

void addToBasket(const char* filename) {
    char newFilename[1024];
    snprintf(newFilename, sizeof(newFilename), "%s/%s", BASKET_FOLDER, strrchr(filename, '/') + 1);
    if (rename(filename, newFilename) != 0) {
        fprintf(stderr, "Ошибка перемещения файла в корзину: %s\n", strerror(errno));
        return;
    }

    FILE* basketInfo = fopen(BASKET_FOLDER "/bin.info", "a");
    if (!basketInfo) {
        fprintf(stderr, "Ошибка открытия файла корзины: %s\n", strerror(errno));
        return;
    }

    fprintf(basketInfo, "%s %s\n", filename, newFilename);

    fclose(basketInfo);
    logAction("Добавлено в корзину", newFilename);
}

void restoreFromBasket() {
    FILE* basketInfo = fopen(BASKET_FOLDER "/bin.info", "r");
    if (!basketInfo) {
        fprintf(stderr, "Ошибка открытия файла корзины: %s\n", strerror(errno));
        return;
    }

    char originalFilename[1024], newFilename[1024];
    while (fscanf(basketInfo, "%s %s", originalFilename, newFilename) == 2) {
        printf("Восстановление файла: %s\n", originalFilename);
        if (rename(newFilename, originalFilename) != 0) {
            fprintf(stderr, "Ошибка восстановления файла: %s\n", strerror(errno));
        }
        logAction("Восстановлено из корзины", originalFilename);
    }

    fclose(basketInfo);
    if (remove(BASKET_FOLDER "/bin.info") != 0) {
        fprintf(stderr, "Ошибка удаления файла информации о корзине: %s\n", strerror(errno));
    }
}

void clearBasket() {
    FILE* basketInfo = fopen(BASKET_FOLDER "/bin.info", "r");
    if (!basketInfo) {
        fprintf(stderr, "Ошибка открытия файла корзины: %s\n", strerror(errno));
        return;
    }

    char originalFilename[1024], newFilename[1024];
    while (fscanf(basketInfo, "%s %s", originalFilename, newFilename) == 2) {
        printf("Удаление файла из корзины: %s\n", originalFilename);
        if (unlink(newFilename) != 0) {
            fprintf(stderr, "Ошибка удаления файла из корзины: %s\n", strerror(errno));
        }
    }

    fclose(basketInfo);
    if (remove(BASKET_FOLDER "/bin.info") != 0) {
        fprintf(stderr, "Ошибка удаления файла информации о корзине: %s\n", strerror(errno));
    }
    logAction("Корзина очищена", "");
}

void displayBasketInfo() {
    FILE* basketInfo = fopen(BASKET_FOLDER "/bin.info", "r");
    if (!basketInfo) {
        fprintf(stderr, "Ошибка открытия файла корзины: %s\n", strerror(errno));
        return;
    }

    char line[2048];
    while (fgets(line, sizeof(line), basketInfo)) {
        printf("Файл в корзине: %s\n", strtok(line, "\n"));
    }

    fclose(basketInfo);
}

void autoCleanBasket() {
    while (1) {
        sleep(AUTO_CLEAN_INTERVAL);
        printf("Auto cleaning basket...\n");
        clearBasket();
        logAction("Корзина очищена автоматически", "");
    }
}


