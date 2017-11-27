#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
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
    static unsigned char map[GEN_NUM];
    int i;
    unsigned int seed = time(NULL);

    memset(map, 0, sizeof(map));

    //seed = 1511683476;
    printf("seed:%u\n", seed);
    fflush(stdout);
    srand(seed);
    //srand(12963846);

    rbtreeInit(&t, node, node_, key, rbtreeIntComparator);

    for (i = 0; i < GEN_NUM; ++i) {
        numbers[i] = rand() % GEN_NUM;
        nodes[i].key = numbers[i];
    }

    for (i = 0; i < GEN_NUM; ++i) {
        if (map[numbers[i]]) {
            node *n = rbtreeFind(&t, &numbers[i]);
            printf("ROUND %d REMOVE:%d\n", i, numbers[i]);
            if (!n) {
                fprintf(stderr, "Find node([%d]:%d) failed.\n", i, numbers[i]);
                return -1;
            }
            if (n->key != numbers[i]) {
                fprintf(stderr, "Find incorrect node([%d]:%d).\n", i, numbers[i]);
                return -1;
            }
            rbtreeDelete(&t, n);
            if (0 != rbtreeVerify(&t)) {
                fprintf(stderr, "Verify failed.\n");
                rbtreePrint(&t, keyToInt);
                printf("\n");
                return -1;
            }
            map[numbers[i]] = 0;
        } else {
            printf("ROUND %d ADD:%d\n", i, numbers[i]);
            if (&nodes[i] != rbtreeInsert(&t, &nodes[i])) {
                fprintf(stderr, "Insert key([%d]:%d) failed.\n", i, numbers[i]);
                return -1;
            }
            if (0 != rbtreeVerify(&t)) {
                fprintf(stderr, "Verify failed.\n");
                rbtreePrint(&t, keyToInt);
                printf("\n");
                return -1;
            }
            map[numbers[i]] = 1;
        }
        //rbtreePrint(&t, keyToInt);
        //printf("\n");
    }

    for (i = 0; i < GEN_NUM; ++i) {
        if (map[numbers[i]]) {
            node *n = rbtreeFind(&t, &numbers[i]);
            if (!n) {
                fprintf(stderr, "Find node([%d]:%d) failed.\n", i, numbers[i]);
                return -1;
            }
            if (n->key != numbers[i]) {
                fprintf(stderr, "Find key([%d]:%d) failed.\n", i, numbers[i]);
                return -1;
            }
        } else {
            if (0 != rbtreeFind(&t, &numbers[i])) {
                fprintf(stderr, "Should not exist([%d]:%d).\n", i, numbers[i]);
                return -1;
            }
        }
    }

    return 0;
}
