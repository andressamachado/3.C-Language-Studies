#include "sort.h"
#include <string.h>

/* PROGRAM: Rental matching
   AUTHORS: Andressa Machado [040923007] & Harsh Patel [040919280]
   DATE: 11.March.2019
   PURPOSE: A program to simulate a matching app for rental properties.
   LEVEL OF DIFFICULTY: 9
   CHALLENGES: comparator function for sorting. Double pointers.
   HOURS SPENT: 15 hours
*/


// Comparator to sort by number of rooms DESCENDING
int numberOfRoomsCompare(PropertyNode *a, PropertyNode *b) {
    return b->numberOfBedrooms - a->numberOfBedrooms;
}

// Comparator to sort by rent ASCENDING
int rentCompare(PropertyNode *a, PropertyNode *b) {
    return a->pricePerBedroom - b->pricePerBedroom;
}


// Comparator to sort by address ASCENDING
int addressCompare(PropertyNode *a, PropertyNode *b) {
    // usses string.h strcmg to get which string is "bigger"
    // result is 0 for equal, 1 if a > b, -1 if a < b
    int result = strcmp(a->street->street, b->street->street);

    //if street name is the same, compare numbers
    if (result == 0) {
        return a->streetNumber - b->streetNumber;
    }
    return result;
}

// Comparator to sort by distance ASCENDING
int distanceCompare(PropertyNode *a, PropertyNode *b) {
    return totalDistance(a) - totalDistance(b);
}

// The swap contents function provided by the Professor
void swap(ListNode *pNode_A, ListNode *pNode_B) {
    PropertyNode *temp = pNode_A->property;
    pNode_A->property = pNode_B->property;
    pNode_B->property = temp;
}


void bubbleSort(ListNode **ppHead,
                int (*pComparator)(PropertyNode *a, PropertyNode *b)) {
    int swapped;
    ListNode *pTemp1;
    ListNode *lastPointer = NULL;

    //  if list is null, just return
    if ((*ppHead)->next == NULL)
        return;

    // simple bubble sort implementation
    // compares all items in pairs, swapping when on is bigger then the other
    // going to the end of the list until a full pass is done and no swaps are made
    do {
        swapped = 0;
        pTemp1 = (*ppHead)->next;

        while (pTemp1->next != lastPointer) {
            if (pComparator(pTemp1->property, pTemp1->next->property) > 0) {
                swap(pTemp1, pTemp1->next);
                swapped = 1;
            }
            pTemp1 = pTemp1->next;
        }
        lastPointer = pTemp1;
    } while (swapped);
}
