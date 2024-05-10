#include "functions.h"

void logAction(const char* action, const char* filename) {
    FILE* logFile = fopen("log.txt", "a");
    if (!logFile) {
        fprintf(stderr, "Ошибка открытия файла журнала: %s\n", strerror(errno));
        return;
    }

    time_t now = time(NULL);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

    fprintf(logFile, "[%s] %s: %s\n", timestamp, action, filename);
    fclose(logFile);
}

void createBasketFolder() {
    if (mkdir(BASKET_FOLDER, 0777) != 0 && errno != EEXIST) {
        fprintf(stderr, "Ошибка создания папки корзины: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

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

void* autoCleanThread(void* arg) {
    autoCleanBasket();
    return NULL;
}
