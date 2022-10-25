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

    printTree(treeRoot, 0);

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

// initializes tnode pointers to NULL
struct tnode* new_tnode() {
    struct tnode *n = malloc(sizeof(struct tnode));
    n->weight= 0;
    n->c     = 0;
    n->left  = NULL;
    n->right = NULL;
    n->parent= NULL;
    return n;
}

void printTree(struct tnode *n, int level)
{
        if (n == NULL) return;
        
        for (int i = 0; i < level; i++)
            printf(i == level - 1 ? "- " : "  ");
        
        if (n->c !=0)
            printf("%c (%d)\n", n->c, n->weight);
        else
            printf("%d\n", n->weight);

        printTree(n->left, level + 1);
        printTree(n->right, level + 1);
}


struct tnode* createFreqTable(char* file) {

    //struct tnode* leafs = (struct tnode*)malloc(128 * sizeof(struct tnode));
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

    while(ll->next != NULL) {
        
        // create new_tnode
        struct tnode *parent= new_tnode();
        
        // free and return children from linked list
        struct tnode *left  = llPop(&ll);
        struct tnode *right = llPop(&ll);

        // assign pointers
        left->parent  = parent;
        right->parent = parent;

        parent->left  = left;
        parent->right = right;

        parent->weight = left->weight + right->weight;
        
        // add tnode into linkedList
        list_add_in_order(&ll, parent);
    }
    return ll->value;
}

void encodeFile(char* argv, struct tnode* leafNodes) {

}

void decodeFile(char* argv, struct tnode* treeRoot) {

}