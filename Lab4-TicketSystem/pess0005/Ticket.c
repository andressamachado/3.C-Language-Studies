#include "Ticket.h"
#include <stdio.h>

//Referencing the struct created in Ticket.h
struct Ticket;

//Print the code and ticket ID
void printTicket(Ticket ticket, char *categoryCode) {

    printf("%s%03d", categoryCode, ticket.ID);
}