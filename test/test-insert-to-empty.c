#include <stdio.h>
#include "rbtree.h"

typedef struct node {
    rbtreeNode node_;
    int key;
} node;

static int keyToInt(const void *key) {
    return *(int *)key;
}

int main(int argc, char *argv[]) {
    rbtree t;
    node firstNode;
    node *find;
    int firstNum = 10;
    int array[1] = {0};

    rbtreeInit(&t, node, node_, key, rbtreeIntComparator);

    firstNode.key = firstNum;
    if (&firstNode != rbtreeInsert(&t, &firstNode)) {
        fprintf(stderr, "Insert key failed.\n");
        return -1;
    }

    if (&firstNode != rbtreeFind(&t, &firstNum)) {
        fprintf(stderr, "Find key failed after insertion.\n");
        return -1;
    }

    if (1 != rbtreeDumpToArray(&t, keyToInt, array, 1)) {
        fprintf(stderr, "Dump to array failed.\n");
        return -1;
    }

    if (10 != array[0]) {
        fprintf(stderr, "Found incorrect value.\n");
        return -1;
    }

    return 0;
}
