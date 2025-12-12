#ifndef BAKERY_H
#define BAKERY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    float price;
    int quantity;
} Pastry;

typedef struct {
    Pastry *data;
    size_t count;
    size_t capacity;
} BakeryDB;

void initDB(BakeryDB *db);
void freeDB(BakeryDB *db);

void printDB(const BakeryDB *db);
void addPastry(BakeryDB *db);
void deletePastry(BakeryDB *db);
void editPastry(BakeryDB *db);

void searchByName(const BakeryDB *db);
void searchByPriceRange(const BakeryDB *db);

void saveDB(const BakeryDB *db, const char *filename);
void loadDB(BakeryDB *db, const char *filename);

#endif
