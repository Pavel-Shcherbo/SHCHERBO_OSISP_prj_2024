#include "menu.h"

void menu() {
    createBasketFolder();

    pthread_t tid;
    pthread_create(&tid, NULL, autoCleanThread, NULL);

    int choice;
    while (1) {
        printf("Меню:\n");
        printf("1. Удалить файл\n");
        printf("2. Восстановить файлы из корзины\n");
        printf("3. Просмотреть содержимое корзины\n");
        printf("4. Очистить корзину\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char filename[1024];
                printf("Введите полный путь к файлу для удаления: ");
                getchar(); // Clear input buffer
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0; // Remove trailing newline
                addToBasket(filename);
                break;
            }
            case 2: {
                restoreFromBasket();
                break;
            }
            case 3: {
                displayBasketInfo();
                break;
            }
            case 4: {
                clearBasket();
                break;
            }
            case 0: {
                printf("Выход из программы.\n");
                exit(0);
            }
            default:
                printf("Неверный ввод! Пожалуйста, выберите существующий пункт.\n");
        }
    }
    pthread_join(tid, NULL);
    logAction("Запущено приложение", "");
}
