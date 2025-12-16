#include "bakery.h"

void printMenu() {
    printf("\n=== Меню ===\n");
    printf("1. Вывести товары на экран\n");
    printf("2. Поиск по названию\n");
    printf("3. Поиск по цене\n");
    printf("4. Добавить новый товар\n");
    printf("5. Редактировать товар\n");
    printf("6. Удалить товар\n");
    printf("7. Сохранить изменения\n");
    printf("0. Выход\n");
    printf("Введите номер: ");
    fflush(stdout);
}

int main() {
    BakeryDB db;
    initDB(&db);

    char filename[100];

    printf("Введите имя файла базы данных: ");
    fflush(stdout);

    if (scanf("%99s", filename) != 1) {
        printf("Ошибка ввода.\n");
        freeDB(&db);
        return 1;
    }

    loadDB(&db, filename);

    int choice;
    do {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            choice = -1;
        }

        switch (choice) {
            case 1: printDB(&db); break;
            case 2: searchByName(&db); break;
            case 3: searchByPriceRange(&db); break;
            case 4: addPastry(&db); break;
            case 5: editPastry(&db); break;
            case 6: deletePastry(&db); break;
            case 7: saveDB(&db, filename); break;
            case 0:
                saveDB(&db, filename);
                printf("Выход...\n");
                fflush(stdout);
                break;
            default:
                printf("Неверный ввод.\n");
                fflush(stdout);
        }
    } while (choice != 0);

    freeDB(&db);
    return 0;
}
