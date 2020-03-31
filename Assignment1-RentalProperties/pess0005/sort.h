#include "lists.h"

int (*pComparator)(PropertyNode *a, PropertyNode *b);

int distanceCompare(PropertyNode *a, PropertyNode *b);
int numberOfRoomsCompare(PropertyNode *a, PropertyNode *b);
int rentCompare(PropertyNode *a, PropertyNode *b);
int addressCompare(PropertyNode *a, PropertyNode *b);
void bubbleSort(ListNode **pHead,
                int (*pComparator)(PropertyNode *a, PropertyNode *b));
