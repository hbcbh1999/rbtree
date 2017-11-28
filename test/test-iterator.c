#include <stdio.h>
#include "rbtree.h"

#define GEN_NUM 1000

typedef struct node {
    rbtreeNode node_;
    int key;
} node;

static int keyToInt(const void *key) {
    return *(int *)key;
}

int main(int argc, char *argv[]) {
    rbtree t;
    int i;
    node nodes[GEN_NUM];
    node *it;

    rbtreeInit(&t, node, node_, key, rbtreeIntComparator);
    for (i = 0; i < GEN_NUM; ++i) {
        nodes[i].key = i + 1;
        rbtreeInsert(&t, &nodes[i]);
    }

    printf("from %d to %d:\n", nodes[0].key, nodes[GEN_NUM - 1].key);
    for (i = 0, it = (node *)rbtreeFirst(&t); it; it = (node *)rbtreeNext(&t, it), i++) {
        printf("i:%d key:%d\n", i, it->key);
        if (&nodes[i] != it) {
            fprintf(stderr, "Iterate failed(i:%d expectedKey:%d got:%d).\n", i, nodes[i].key, it->key);
            rbtreePrint(&t, keyToInt);
            return -1;
        }
    }
    if (i != GEN_NUM) {
        fprintf(stderr, "Iterate failed(i:%d).\n", i);
        rbtreePrint(&t, keyToInt);
        return -1;
    }

    printf("from %d to %d:\n", nodes[GEN_NUM - 1].key, nodes[0].key);
    for (i = GEN_NUM - 1, it = (node *)rbtreeLast(&t); it; it = (node *)rbtreePrevious(&t, it), i--) {
        printf("i:%d key:%d\n", i, it->key);
        if (&nodes[i] != it) {
            fprintf(stderr, "Iterate failed(i:%d expectedKey:%d got:%d).\n", i, nodes[i].key, it->key);
            rbtreePrint(&t, keyToInt);
            return -1;
        }
    }
    if (i != -1) {
        fprintf(stderr, "Iterate failed(i:%d).\n", i);
        rbtreePrint(&t, keyToInt);
        return -1;
    }

    return 0;
}
