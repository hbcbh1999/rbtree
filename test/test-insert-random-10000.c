#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "rbtree.h"

#define GEN_NUM 10000

typedef struct node {
    rbtreeNode node_;
    int key;
} node;

static int keyToInt(const void *key) {
    return *(int *)key;
}

int main(int argc, char *argv[]) {
    rbtree t;
    static node nodes[GEN_NUM];
    static int numbers[GEN_NUM];
    int i;
    unsigned int seed = time(NULL);

    printf("seed:%u\n", seed);
    fflush(stdout);
    srand(seed);
    //srand(12963846);

    rbtreeInit(&t, node, node_, key, rbtreeIntComparator);

    for (i = 0; i < GEN_NUM; ++i) {
        numbers[i] = rand() % GEN_NUM;
        numbers[i] <<= 16;
        numbers[i] += i;
        nodes[i].key = numbers[i];
        if (&nodes[i] != rbtreeInsert(&t, &nodes[i])) {
            fprintf(stderr, "Insert key([%d]:%d) failed.\n", i, numbers[i]);
            return -1;
        }
        //printf("After insert key([%d]:%d):\n", i, numbers[i]);
        //rbtreePrint(&t, keyToInt);
        //printf("\n");
    }

    for (i = 0; i < GEN_NUM; ++i) {
        if (&nodes[i] != rbtreeFind(&t, &numbers[i])) {
            fprintf(stderr, "Find key([%d]:%d) failed.\n", i, numbers[i]);
            return -1;
        }
    }

    return 0;
}
