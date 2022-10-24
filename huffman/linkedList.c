#include <stdio.h>
#include <stdlib.h> // malloc
#include <assert.h>
#include "linkedList.h"

LinkedList *llCreate()
{
    return NULL;
}

int llIsEmpty(LinkedList *ll)
{
    return (ll == NULL);
}

void llDisplay(LinkedList *p)
{
    if (p)
    {
        printf("Node: %c, Weight: %d\n", p->value->c, p->value->weight);
        llDisplay(p->next);
    }
}

void llAdd(LinkedList **ll, struct tnode* newValue)
{
    // Create the new node
    LinkedList *newNode = (LinkedList *)malloc(1 * sizeof(LinkedList));
    newNode->value = newValue;
    newNode->next = NULL;

    // Find the end of the list
    LinkedList *p = *ll;
    if (p == NULL)
    {                  // Add first element 
        *ll = newNode; // This is why we need ll to be a **
    }
    else
    {
        while (p->next != NULL)
        {
            p = p->next;
        }

        // Attach it to the end
        p->next = newNode;
    }
}

void list_add_in_order(LinkedList** ll, struct tnode* newValue) {
    // Create the new node
    LinkedList *newNode = (LinkedList *)malloc(1 * sizeof(LinkedList));
    newNode->value = newValue;
    newNode->next = NULL;

    // Find the end of the list
    LinkedList *p = *ll;
    LinkedList *pTrail = NULL;

    // find the insertion point
    while (p && newValue->weight >= p->value->weight)   
    {
        pTrail = p;
        p = p->next;
    }

    // case insert before head
    if (pTrail == NULL) {
        *ll = newNode;
        newNode->next = p;
        return;
    } 

    // case insert node in middle or end
    pTrail->next = newNode;
    newNode->next = p;
}


void llFree(LinkedList* ll) {
  LinkedList* p = ll;
  while (p != NULL) {
    LinkedList* oldP = p;
    p = p->next;
    free(oldP);
  }
  
}