struct tnode {
    int weight;
    int c;
    struct tnode* left;
    struct tnode* right;  
    struct tnode* parent;
};

struct tnode* createFreqTable(char** file);

struct tnode* createHuffmanTree(struct tnode* leafNodes);

void encodeFile(char* argv, struct tnode* leafNodes);

void decodeFile(char* argv, struct tnode* treeRoot);