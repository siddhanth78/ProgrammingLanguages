#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

int main(int argc, char *argv[]) {

    // // Check the make sure the input parameters are correct
    // if (argc != 3) {
    //     printf("Error: The correct format is \"hcompress -e filename\" or \"hcompress -d filename.huf\"\n"); fflush(stdout);
    //     exit(1);
    // }

    printf("before\n");
    // Create the frequency table by reading the generic file
    char* file = "test.txt";
    struct tnode* leafNodes = createFreqTable(&file);

    printf("after\n");
    // Create the huffman tree from the frequency table
    struct tnode* treeRoot = createHuffmanTree(leafNodes);

    printf("root val: %d, root weight: %d\n", treeRoot->c, treeRoot->weight);
    printf("left val: %d, left weight: %d\n", treeRoot->left->c, treeRoot->left->weight);
    printf("right val: %d, right weight: %d\n", treeRoot->right->c, treeRoot->right->weight);

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

struct tnode* createFreqTable(char** file) {

    printf("in leaf node\n");

    struct tnode* leafs = (struct tnode*)malloc(128 * sizeof(struct tnode));
    int total = 0;
    int* e;

    // read characters from file, put them into freq array based on ASCII value
    int eof_flag = 0;
    while(eof_flag != -1) {
        eof_flag = scanf("%d", e);
        leafs[*e].weight += 1;
        total++;
    }

    printf("values read in\n");

    for(int i = 0; i < 128; i++) {
        leafs[i].c = i;
    }

    return leafs;
}

struct tnode* createHuffmanTree(struct tnode* leafNodes) {

    // construct ll from frequency array
    LinkedList *ll = llCreate();

    // add tnodes from tnode* to linkedList
    for(int i = 0; i < 128; i++) {
        list_add_in_order(&ll, &leafNodes[i]);
    }

    LinkedList* p = ll;

    while(p->next != NULL) {
        struct tnode *newNode;

        // assign pointers
        newNode->left = p->value;
        newNode->right = p->next->value;
        p->value->parent = newNode;
        p->next->value->parent = newNode;

        // assign weight to newNode
        newNode->weight = p->value->weight + p->next->value->weight;
        
        // reassign p, add tnode into linkedList
        list_add_in_order(&p, newNode);
        p = p->next->next;
    }
}

void encodeFile(char* argv, struct tnode* leafNodes) {

}

void decodeFile(char* argv, struct tnode* treeRoot) {

}