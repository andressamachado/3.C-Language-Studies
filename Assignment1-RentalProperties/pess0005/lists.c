#include "lists.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* PROGRAM: Rental matching
   AUTHORS: Andressa Machado [040923007] & Harsh Patel [040919280]
   DATE: 11.March.2019
   PURPOSE: A program to simulate a matching app for rental properties.
   LEVEL OF DIFFICULTY: 9
   CHALLENGES: comparator function for sorting. Double pointers.
   HOURS SPENT: 15 hours
*/

struct ListNode;
struct List;

// Allocates memory for a new ListNode, sets next to null, return pointer
ListNode *createList() {
    ListNode *tmp = (ListNode *)malloc(sizeof(ListNode));
    tmp->next = NULL;
    return tmp;
}

// checks if head-> next is null
int isListEmpty(ListNode *pHead) { return pHead->next == NULL; }

// Goes to the end of the list, counting elements
int getCount(ListNode *pHead) {
    int count = 0;
    if (isListEmpty(pHead))
        return count;
    else {
        // Steps to first item, grows count
        ListNode *temp = pHead->next;
        count++;
        // until last element, grows count and go forward
        while (temp->next != NULL) {
            temp = temp->next;
            count++;
        }
        return count;
    }
}

// Created a list node by creating a random PropertyNode, a List Node using createList (which returns a ListNode)
// sets node property to the newly created Property node and returns
ListNode *createListNode() {
    PropertyNode *prop = createProperty();
    ListNode *node = createList();
    node->property = prop;
    return node;
}

// Using double pointer to list Head, add 6 random generated list Nodes to list.
void initializeList(ListNode **ppHead) {
    for (int i = 0; i < 6; i++) {
        appendNode(ppHead, createListNode());
    };
}

// Using double pointer to list Head and a newNode pointer, goes to end of list and appends
void appendNode(ListNode **pHead, ListNode *pNewNode) {
    ListNode *temp;
    // If list is empty, add straigh to head
    if (isListEmpty(*pHead))
        (*pHead)->next = pNewNode;
    else {
        // Walks the list until last item (when ->next == null)
        temp = (*pHead)->next;
        while (temp->next != NULL)
            temp = temp->next;

        // sets last item to be newNode
        temp->next = pNewNode;
    }
}

// Using pointer to head, goes through list calling the display table format of property
void displayList(ListNode *pHead) {
    ListNode *temp;

    temp = pHead->next;
    while (temp != NULL) {
        printTableFormat(temp->property);
        temp = temp->next;
    }
}

// Using pointer to list Head, goes through list counting each step to return correct position node
ListNode *getNodeAtIndex(ListNode *pHead, int n) {
    int i = 0;
    ListNode *temp;

    temp = pHead->next;
    for (; i < n; i++)
        temp = temp->next;

    return temp;
}

// Function to insert node at a certain position
void insertNode(ListNode **ppHead, ListNode *pNewNode, int n) {
    ListNode *temp;

    // if position is 0, add to head, organizes pointers
    if (n == 0) {
        pNewNode->next = (*ppHead)->next;
        (*ppHead)->next = pNewNode;
        return;
    } else {
        // else, just get element at previous position of n
        // and adds right after
        temp = getNodeAtIndex(*ppHead, n - 1);
        pNewNode->next = temp->next;
        temp->next = pNewNode;
    }
}

// Given the double pointer to head, finds element at position n, and removes
ListNode *removeNodeAtIndex(ListNode **ppHead, int n) {
    ListNode *temp;
    ListNode *temp2;

    // if n==0 remove the head
    if (n == 0) {
        temp = (*ppHead)->next;
        (*ppHead)->next = temp->next;
        return temp;
    }

    // if not, find element right before the one to remove, organizes the pointers and return desired item
    temp = getNodeAtIndex(*ppHead, n - 1);
    temp2 = temp->next;
    temp->next = temp2->next;
    return temp2;
}

// Function to move items from one list to another.
void moveNodeToList(ListNode **pHeadSource, ListNode **pHeadDestination,
                    int indexOfNode) {
    // remove  from first list at index
    ListNode *toMove = removeNodeAtIndex(pHeadSource, indexOfNode);
    // Append to scond list, set next to null since it will be last
    toMove->next = NULL;
    appendNode(pHeadDestination, toMove);
}

// Takes a random number simulating a 50% chance, if good, adds to the list
void randomAddToList(ListNode **ppHead) {
    int willAdd = rand() % 2;
    if (willAdd) {
        appendNode(ppHead, createListNode());
    }
}
