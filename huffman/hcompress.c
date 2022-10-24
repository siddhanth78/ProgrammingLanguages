#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linkedList.h"

// compile with: gcc -g hcompress.c linkedList.c -o out

int main(int argc, char *argv[]) {

    // // Check the make sure the input parameters are correct
    // if (argc != 3) {
    //     printf("Error: The correct format is \"hcompress -e filename\" or \"hcompress -d filename.huf\"\n"); fflush(stdout);
    //     exit(1);
    // }

    // Create the frequency table by reading the generic file
    char* file = "test.txt";
    struct tnode* leafNodes = createFreqTable(file);

    // Create the huffman tree from the frequency table
    struct tnode* treeRoot = createHuffmanTree(leafNodes);

    //printf("root val: %c, root weight: %d\n", treeRoot->c, treeRoot->weight);
    //printf("left val: %c, left weight: %d\n", treeRoot->left->c, treeRoot->left->weight);
    //printf("right val: %c, right weight: %d\n", treeRoot->right->c, treeRoot->right->weight);

    // // encode
    // if (strcmp(argv[1], "-e") == 0) {
    //     // Pass the leafNodes since it will process bottom up
    //     encodeFile(argv[2], leafNodes);
    // } else { // decode
    //     // Pass the tree root since it will process top down
    //     decodeFile(argv[2], treeRoot);
    // }

    return 0;
}

struct tnode* createFreqTable(char* file) {

    //struct tnode* leafs = (struct tnode*)malloc(128 * sizeof(struct tnode));
    // ^^^ easier to view in the debugger when type array vs pointer
    static struct tnode leafs[128];
    
    int total = 0;
    unsigned char e;

    // read characters from file, put them into freq array based on ASCII value
    while(scanf("%c", &e) != -1) {
        assert(e >= 0 && e<= 128);
        leafs[e].weight += 1;
        total++;
    }

    for(int i = 0; i < 128; i++) {
        leafs[i].c = i;
    }

    return &leafs[0];
}

struct tnode* createHuffmanTree(struct tnode* leafNodes) {

    // construct ll from frequency array
    LinkedList *ll = llCreate();

    // add tnodes from tnode* to linkedList
    for(int i = 0; i < 128; i++) {
        if(leafNodes[i].weight != 0)
            list_add_in_order(&ll, &leafNodes[i]);
    }

    LinkedList* p = ll;

    llDisplay(ll);

    //printf("p: %c, weight: %d\n", p->value->c, p->value->weight);
    //printf("p.next.c: %c p.next.weight %d\n", p->next->value->c, p->next->value->weight); SEGMENTATION FAULT

    while(p->next != NULL) {
        
        p = ll;
        
        struct tnode *newNode = malloc(sizeof(struct tnode*));
        
        // assign pointers
        printf("p_c: %c, p_weight: %d\n", p->value->c, p->value->weight);

        newNode->left = p->value; // SEG FAULTING AT THIS LINE // 
        // gets through loop once...
        // then Segmentation Fault
        //
        // guess: either llFree() or list_add_in_order() missassign pointers

        newNode->right = p->next->value;
        p->value->parent = newNode;
        p->next->value->parent = newNode;

        // assign weight to newNode
        newNode->weight = p->value->weight + p->next->value->weight;
        
        // reassign p, add tnode into linkedList
        list_add_in_order(&p, newNode);
        
        // free the combined nodes
        //llFree(ll);
        llFree(ll);
        printf("free?\n");
    }

    printf("no seg fault?\n");
    return p->value;
}

void encodeFile(char* argv, struct tnode* leafNodes) {

}

void decodeFile(char* argv, struct tnode* treeRoot) {

}