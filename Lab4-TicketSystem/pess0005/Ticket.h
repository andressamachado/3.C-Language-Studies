//
// Created by andressa on 2/18/2019.
//

#ifndef LAB4_TICKET_H
#define LAB4_TICKET_H

// struct def
typedef struct MyTicket {
    int ID;
    long timestamp;
} Ticket;

void printTicket(Ticket, char *);

#endif //LAB4_TICKET_H
