//
// Created by andressa on 2/18/2019.
//

#ifndef LAB4_CATEGORY_H
#define LAB4_CATEGORY_H

#include "Ticket.h"

typedef struct MyCategory {
    char *name;
    char *code;
    int listSize;
    Ticket *ticketArray;
} Category;

Category *createCategoryList(int nTotalCategories);

void initializeCategories(Category *categoriesArray);

void randomizeCategories(Category *categoriesArray, int size,  int nCategoriesToUse);

void printSelectedCategories(Category *categoriesArray, int nCategoriesToUse, int initial);

void printCategory(Category category);

void freeAllMemory(Category *categoriesArray, int nCategoriesToUse);

#endif //LAB4_CATEGORY_H
