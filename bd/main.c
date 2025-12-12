#include "bakery.h"

#define DB_FILE "bakery_data.bin"

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
    fflush(stdout); // Принудительный вывод перед scanf
}

int main() {
    BakeryDB db;
    initDB(&db);

    loadDB(&db, DB_FILE);

    int choice;
    do {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); 
            choice = -1;
        }
        // fflush(stdout) внутри printMenu уже гарантирует, что "Введите номер: " отобразится.

        switch (choice) {
            case 1: printDB(&db); break;
            case 2: searchByName(&db); break;
            case 3: searchByPriceRange(&db); break;
            case 4: addPastry(&db); break;
            case 5: editPastry(&db); break;
            case 6: deletePastry(&db); break;
            case 7: saveDB(&db, DB_FILE); break;
            case 0: 
                saveDB(&db, DB_FILE); 
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
