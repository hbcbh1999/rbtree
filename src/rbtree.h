#ifndef RBTREE_H
#define RBTREE_H

typedef struct rbtreeNode {
    unsigned char isRed;
    struct rbtreeNode *parent;
    struct rbtreeNode *left;
    struct rbtreeNode *right;
} rbtreeNode;

typedef struct rbtree rbtree;

typedef int (*rbtreeComparator)(rbtree *tree, const void *firstKey, const void *secondKey);

struct rbtree {
    rbtreeNode *root;
    int keyOffsetOfNode;
    int nodeOffsetOfParent;
    rbtreeComparator comparator;
};

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((int)&((TYPE *)0)->MEMBER)
#endif

#define rbtreeInit(tree_, parentType_, nodeFileName_, keyFieldName_, comparator_) do {  \
    (tree_)->root = 0;                                                                  \
    (tree_)->nodeOffsetOfParent = (int)offsetof(parentType_, nodeFileName_);            \
    (tree_)->keyOffsetOfNode = (int)offsetof(parentType_, keyFieldName_) -              \
        (tree_)->nodeOffsetOfParent;                                                    \
    (tree_)->comparator = comparator_ ? comparator_ : rbtreeStringComparator;           \
} while (0)

int rbtreeIntComparator(rbtree *tree, const void *firstKey, const void *secondKey);
int rbtreeUintComparator(rbtree *tree, const void *firstKey, const void *secondKey);
int rbtreeLongComparator(rbtree *tree, const void *firstKey, const void *secondKey);
int rbtreeUlongComparator(rbtree *tree, const void *firstKey, const void *secondKey);
int rbtreeLongLongComparator(rbtree *tree, const void *firstKey, const void *secondKey);
int rbtreeUlongLongComparator(rbtree *tree, const void *firstKey, const void *secondKey);
int rbtreeStringComparator(rbtree *tree, const void *firstKey, const void *secondKey);

void *rbtreeFind(rbtree *tree, const void *key);
void *rbtreeInsert(rbtree *tree, void *insert);

#if RBTREE_DEBUG
typedef int (*rbtreeKeyToIntConverter)(const void *key);
void rbtreePrint(rbtree *tree, rbtreeKeyToIntConverter converter);
int rbtreeDumpToArray(rbtree *tree, rbtreeKeyToIntConverter converter, int *array, int maxNum);
#endif

#endif
