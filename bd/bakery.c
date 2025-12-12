#include "bakery.h"

void initDB(BakeryDB *db) {
    db->capacity = 2;
    db->count = 0;
    db->data = (Pastry *)malloc(db->capacity * sizeof(Pastry));
    if (!db->data) exit(1);
}

void freeDB(BakeryDB *db) {
    free(db->data);
    db->data = NULL;
    db->count = 0;
    db->capacity = 0;
}

void resizeDB(BakeryDB *db) {
    if (db->count >= db->capacity) {
        db->capacity *= 2;
        Pastry *newData = (Pastry *)realloc(db->data, db->capacity * sizeof(Pastry));
        if (!newData) exit(1);
        db->data = newData;
    }
}

void printDB(const BakeryDB *db) {
    if (db->count == 0) {
        printf("База данных пуста.\n");
        return;
    }
    printf("\n--- Товары ---\n");
    printf("%-5s %-20s %-10s %-10s\n", "ID", "Название", "Цена", "Кол-во");
    for (size_t i = 0; i < db->count; i++) {
        printf("%-5zu %-20s %-10.2f %-10d\n", i + 1, db->data[i].name, db->data[i].price, db->data[i].quantity);
    }
    printf("--------------\n");
}

void addPastry(BakeryDB *db) {
    resizeDB(db);

    Pastry p;
    printf("Название: ");
    scanf("%49s", p.name);
    printf("Цена: ");
    scanf("%f", &p.price);
    printf("Количество: ");
    scanf("%d", &p.quantity);

    db->data[db->count++] = p;
    printf("Товар добавлен.\n");
}

void deletePastry(BakeryDB *db) {
    printDB(db);
    if (db->count == 0) return;

    int id_input;
    printf("Введите ID для удаления: ");
    if (scanf("%d", &id_input) != 1 || id_input <= 0) {
        printf("Неверный ввод ID.\n");
        return;
    }

    size_t id = (size_t)id_input;

    if (id > db->count) {
        printf("Неверный ID.\n");
        return;
    }

    for (size_t i = id - 1; i < db->count - 1; i++) {
        db->data[i] = db->data[i + 1];
    }
    db->count--;
    printf("Товар удален.\n");
}

void editPastry(BakeryDB *db) {
    printDB(db);
    if (db->count == 0) return;

    int id_input;
    printf("Введите ID для редактирования: ");
    if (scanf("%d", &id_input) != 1 || id_input <= 0) {
        printf("Неверный ввод ID.\n");
        return;
    }

    size_t id = (size_t)id_input;

    if (id > db->count) {
        printf("Неверный ID.\n");
        return;
    }

    Pastry *p = &db->data[id - 1];
    printf("Редактирование '%s'.\n", p->name);

    printf("Новое название: ");
    scanf("%49s", p->name);
    printf("Новая цена: ");
    scanf("%f", &p->price);
    printf("Новое количество: ");
    scanf("%d", &p->quantity);

    printf("Товар обновлен.\n");
}



void searchByName(const BakeryDB *db) {
    char query[50];
    printf("Введите название для поиска: ");
    scanf("%49s", query);

    int found = 0;
    printf("\nРезультаты поиска:\n");
    for (size_t i = 0; i < db->count; i++) {
        if (strstr(db->data[i].name, query) != NULL) {
            printf("%-20s Цена: %.2f Кол-во: %d\n", db->data[i].name, db->data[i].price, db->data[i].quantity);
            found = 1;
        }
    }
    if (!found) printf("Ничего не найдено.\n");
}

void searchByPriceRange(const BakeryDB *db) {
    float minP, maxP;
    printf("Диапазон цен (мин макс): ");
    scanf("%f %f", &minP, &maxP);

    int found = 0;
    printf("\nРезультаты поиска:\n");
    for (size_t i = 0; i < db->count; i++) {
        if (db->data[i].price >= minP && db->data[i].price <= maxP) {
            printf("%-20s Цена: %.2f Кол-во: %d\n", db->data[i].name, db->data[i].price, db->data[i].quantity);
            found = 1;
        }
    }
    if (!found) printf("Ничего не найдено.\n");
}

void saveDB(const BakeryDB *db, const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) return;

    fwrite(&db->count, sizeof(size_t), 1, f);
    if (db->count > 0) {
        fwrite(db->data, sizeof(Pastry), db->count, f);
    }

    fclose(f);
    printf("Данные сохранены.\n");
}

void loadDB(BakeryDB *db, const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Файл не найден. Новая база.\n");
        return;
    }

    size_t newCount;
    if (fread(&newCount, sizeof(size_t), 1, f) != 1) {
        fclose(f);
        return;
    }

    if (newCount > db->capacity) {
        db->capacity = newCount + 5;
        db->data = (Pastry *)realloc(db->data, db->capacity * sizeof(Pastry));
    }

    db->count = newCount;
    fread(db->data, sizeof(Pastry), db->count, f);
	fclose(f);
    printf("Загружено %zu товаров.\n", db->count);
}
