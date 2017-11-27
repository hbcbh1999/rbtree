#include <stdlib.h>
#include <stdio.h>
#include <sys/resource.h>
#include "rbtree.h"

struct mytype {
	rbtreeNode node;
	int key;
};

#define GEN_NUM 1000000

int main(int argc, char *argv[]) {
    struct mytype *nodes = (struct mytype *)calloc(GEN_NUM, sizeof(struct mytype));
    unsigned int seed = 1511797570;
    int i;
    struct rusage begin;
    struct rusage end;
    rbtree t;

    rbtreeInit(&t, struct mytype, node, key, rbtreeIntComparator);

    srand(seed);
    for (i = 0; i < GEN_NUM; ++i) {
        nodes[i].key = rand();
    }

    getrusage(RUSAGE_SELF, &begin);
    for (i = 0; i < GEN_NUM; ++i) {
        rbtreeInsert(&t, &nodes[i]);
    }
    getrusage(RUSAGE_SELF, &end);
    printf("my,insert,%d,%ld\n", GEN_NUM, begin.ru_utime.tv_sec * 100000 + begin.ru_utime.tv_usec);

    getrusage(RUSAGE_SELF, &begin);
    for (i = 0; i < GEN_NUM; ++i) {
        rbtreeFind(&t, &nodes[i].key);
    }
    getrusage(RUSAGE_SELF, &end);
    printf("my,search,%d,%ld\n", GEN_NUM, begin.ru_utime.tv_sec * 100000 + begin.ru_utime.tv_usec);

    getrusage(RUSAGE_SELF, &begin);
    for (i = 0; i < GEN_NUM; ++i) {
        struct mytype *data = rbtreeFind(&t, &nodes[i].key);
        if (data) {
            rbtreeDelete(&t, data);
        }
    }
    getrusage(RUSAGE_SELF, &end);
    printf("my,delete,%d,%ld\n", GEN_NUM, begin.ru_utime.tv_sec * 100000 + begin.ru_utime.tv_usec);

    return 0;
}
