#include "property.h"
#include <stdio.h>
#include <stdlib.h>

/* PROGRAM: Rental matching
   AUTHORS: Andressa Machado [040923007] & Harsh Patel [040919280]
   DATE: 11.March.2019
   PURPOSE: A program to simulate a matching app for rental properties.
   LEVEL OF DIFFICULTY: 9
   CHALLENGES: comparator function for sorting. Double pointers.
   HOURS SPENT: 15 hours
*/


struct PropertyNode;
struct StreetStruct;

char *streetNames[10] = {
        "Street 1", "Street 2", "Street 3", "Street 4", "Street 5",
        "Street 6", "Street 7", "Street 8", "Street 9", "Street 10",
};

//generates random number between two values
int randBetween(int min, int max) {
    int diff = max + 1 - min;
    int result = (rand() % diff) + min;
    return result;
}

// Creates a Street Struct with a random name and random discance
StreetStruct *createStreet() {
    // Allocs memory
    StreetStruct *tmp = (StreetStruct *)malloc(sizeof(StreetStruct));

    //get random index for names
    int streetIndex = randBetween(0,9);
    tmp->street = streetNames[streetIndex];

    //distance must be between 500m(0.5km) and 4000m(4km)
    tmp->distance = 100 * randBetween(5, 40);
    return tmp;
}

// Calculates total distance with the street number in the calculation
int totalDistance(PropertyNode *property) {
    return (property->street)->distance + property->streetNumber * 20;
}

// Creates a PropertyNode with random value following the rules
PropertyNode *createProperty() {
    // Allocs memory
    PropertyNode *prop = (PropertyNode *)malloc(sizeof(PropertyNode));
    // calls create street function
    prop->street = createStreet();
    // Generate other data sing randBetween function
    prop->streetNumber = randBetween(1, 200);
    prop->numberOfBedrooms = randBetween(1, 4);
    prop->pricePerBedroom = 50 * randBetween(4, 12);
    return prop;
}

// Prints a properties' data in a single readable, formatted line
void printFormatted(PropertyNode *property) {
    printf("Addr: %d %s, # Rooms: %d, Rent/Room: $%d, Distance: %.2f km\n",
           property->streetNumber, (property->street)->street,
           property->numberOfBedrooms, property->pricePerBedroom,
           (double)totalDistance(property) / 1000);
}

// Prints a properties' data in a tabular, spacing controlled line
void printTableFormat(PropertyNode *property) {
    printf("%-3d %-43s %-9d %-5d %.2f km\n", property->streetNumber,
           (property->street)->street, property->numberOfBedrooms,
           property->pricePerBedroom, (double)totalDistance(property) / 1000);
}
