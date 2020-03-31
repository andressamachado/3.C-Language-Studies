#include "property.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Defines the Node struct of the list item
typedef struct Node {
    PropertyNode *property;
    struct Node *next;
} ListNode;

int isListEmpty(ListNode *pHead);
int getCount(ListNode *pHead);

ListNode *createList();
void initializeList(ListNode **pHead);

ListNode *createListNode();
ListNode *getNodeAtIndex(ListNode *pHead, int n);

void appendNode(ListNode **pHead, ListNode *pNewNode);

void randomAddToList(ListNode **pHead);

void insertNode(ListNode **pHead, ListNode *pNewNode, int n);
void displayList(ListNode *pHead);

ListNode *removeNodeAtIndex(ListNode **pHead, int n);

void moveNodeToList(ListNode **pHeadSource, ListNode **pHeadDestination,
                    int indexOfNode);
