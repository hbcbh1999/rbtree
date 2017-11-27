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
    node secondNode;
    node thirdNode;
    node *find;
    int firstNum = 10;
    int secondNum = 5;
    int thirdNum = 9;
    int array[3] = {0};

    rbtreeInit(&t, node, node_, key, rbtreeIntComparator);

    firstNode.key = firstNum;
    if (&firstNode != rbtreeInsert(&t, &firstNode)) {
        fprintf(stderr, "Insert key failed.\n");
        return -1;
    }

    if (0 != rbtreeVerify(&t)) {
        fprintf(stderr, "Verify failed.\n");
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

    secondNode.key = secondNum;
    if (&secondNode != rbtreeInsert(&t, &secondNode)) {
        fprintf(stderr, "Insert second key failed.\n");
        return -1;
    }

    if (0 != rbtreeVerify(&t)) {
        fprintf(stderr, "Verify failed.\n");
        return -1;
    }

    if (&firstNode != rbtreeFind(&t, &firstNum)) {
        fprintf(stderr, "Find key failed after insertion.\n");
        return -1;
    }

    if (&secondNode != rbtreeFind(&t, &secondNum)) {
        fprintf(stderr, "Find second key failed after insertion.\n");
        return -1;
    }

    if (2 != rbtreeDumpToArray(&t, keyToInt, array, 2)) {
        fprintf(stderr, "Dump to array failed.\n");
        return -1;
    }

    if (firstNum != array[0]) {
        fprintf(stderr, "Found incorrect value.\n");
        return -1;
    }

    if (secondNum != array[1]) {
        fprintf(stderr, "Found incorrect value.\n");
        return -1;
    }

    thirdNode.key = thirdNum;
    if (&thirdNode != rbtreeInsert(&t, &thirdNode)) {
        fprintf(stderr, "Insert third key failed.\n");
        return -1;
    }

    if (0 != rbtreeVerify(&t)) {
        fprintf(stderr, "Verify failed.\n");
        return -1;
    }

    if (&firstNode != rbtreeFind(&t, &firstNum)) {
        fprintf(stderr, "Find key failed after insertion.\n");
        return -1;
    }

    if (&secondNode != rbtreeFind(&t, &secondNum)) {
        fprintf(stderr, "Find second key failed after insertion.\n");
        return -1;
    }

    if (&thirdNode != rbtreeFind(&t, &thirdNum)) {
        fprintf(stderr, "Find third key failed after insertion.\n");
        return -1;
    }

    if (3 != rbtreeDumpToArray(&t, keyToInt, array, 3)) {
        fprintf(stderr, "Dump to array failed.\n");
        return -1;
    }

    if (9 != array[0]) {
        fprintf(stderr, "Found incorrect value.\n");
        return -1;
    }

    if (5 != array[1]) {
        fprintf(stderr, "Found incorrect value.\n");
        return -1;
    }

    if (10 != array[2]) {
        fprintf(stderr, "Found incorrect value.\n");
        return -1;
    }

    return 0;
}
