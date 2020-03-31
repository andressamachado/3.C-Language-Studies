//
// Created by andressa on 2/18/2019.
//

#ifndef LAB4_TICKETMANAGER_H
#define LAB4_TICKETMANAGER_H

#include "Category.h"

void addTicketToList(Category *category, Ticket ticket);

void distributeTickets(Category *categoriesArray, int nNumTickets,
                       int nCategoriesToUse);

void squashArray(Ticket *ticketArray, int pos, int size);

void removeTickets(Category *categoriesArray, int nNumTickets,
                   int nCategoriesToUse);

#endif //LAB4_TICKETMANAGER_H
