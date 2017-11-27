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
    rbtreeInit(&t, node, node_, key, rbtreeIntComparator);
    printf("Usage: \n"
        "   enter positive integer to add;\n"
        "   enter nagative integer to remove the positive;\n"
        "   enter q to quit;\n"
        "   enter p to print rbtree.\n");
    for (;;) {
        char enter[1024];
        node *n = 0;
        printf(">");
        scanf("%s", enter);
        if (0 == strcmp(enter, "q")) {
            break;
        } else if (0 == strcmp(enter, "p")) {
            rbtreePrint(&t, keyToInt);
        } else {
            int integer = atoi(enter);
            if (integer > 0) {
                printf("Add \"%d\" ", integer);
                n = (node *)calloc(1, sizeof(node));
                n->key = integer;
                if (n == rbtreeInsert(&t, n)) {
                    printf(" succeed.\n");
                } else {
                    free(n);
                    printf(" failed.\n");
                }
            } else {
                integer = abs(integer);
                printf("Remove \"%d\"", integer);
                n = rbtreeFind(&t, &integer);
                if (n) {
                    rbtreeDelete(&t, n);
                    free(n);
                    printf(" done.\n");
                } else {
                    printf(" failed(not found).\n");
                }
            }
        }
    }
    printf("exit\n");
    return 0;
}
