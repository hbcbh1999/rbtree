#include <string.h>
#include <stdio.h>
#include "rbtree.h"

#define keyOfNode(tree, node) (const void *)((char *)(node) + (tree)->keyOffsetOfNode)
#define integerComparator(type, firstKey, secondKey)    (*(type *)(firstKey) == *(type *)(secondKey)) ? 0 : (*(type *)(firstKey) < *(type *)(secondKey) ? -1 : 1)

int rbtreeIntComparator(rbtree *tree, const void *firstKey, const void *secondKey) {
    return integerComparator(int, firstKey, secondKey);
}

int rbtreeUintComparator(rbtree *tree, const void *firstKey, const void *secondKey) {
    return integerComparator(int, firstKey, secondKey);
}

int rbtreeLongComparator(rbtree *tree, const void *firstKey, const void *secondKey) {
    return integerComparator(int, firstKey, secondKey);
}

int rbtreeUlongComparator(rbtree *tree, const void *firstKey, const void *secondKey) {
    return integerComparator(int, firstKey, secondKey);
}

int rbtreeLongLongComparator(rbtree *tree, const void *firstKey, const void *secondKey) {
    return integerComparator(int, firstKey, secondKey);
}

int rbtreeUlongLongComparator(rbtree *tree, const void *firstKey, const void *secondKey) {
    return integerComparator(int, firstKey, secondKey);
}

int rbtreeStringComparator(rbtree *tree, const void *firstKey, const void *secondKey) {
    return strcmp((const char *)firstKey, (const char *)secondKey);
}

rbtreeNode *rbtreeSearch(rbtree *tree, const void *key, rbtreeNode **lastNode, int *lastCmp) {
    rbtreeNode *node;
    node = tree->root;
    while (node) {
        *lastNode = node;
        *lastCmp = tree->comparator(tree, key, keyOfNode(tree, node));
        if (0 == *lastCmp) {
            break;
        } else if (*lastCmp < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}

#define swapColors(firstNode, secondNode) do {  \
    unsigned char tmp = (firstNode)->isRed;     \
    (firstNode)->isRed = (secondNode)->isRed;   \
    (secondNode)->isRed = tmp;                  \
} while (0)

#define replaceChild(tree, child, newChild) do {    \
    if ((child)->parent) {                          \
        if ((child)->parent->left == (child)) {     \
            (child)->parent->left = (newChild);     \
        } else {                                    \
            (child)->parent->right = (newChild);    \
        }                                           \
    }                                               \
} while (0)

#define updateRoot(tree, node) do { \
    if (!(node)->parent) {          \
        (tree)->root = (node);      \
    }                               \
} while (0)

static void leftRotate(rbtree *tree, rbtreeNode *node) {
    rbtreeNode *newParent = node->right;
    rbtreeNode *oldLeft = newParent->left;
    newParent->left = node;
    newParent->parent = node->parent;
    replaceChild(tree, node, newParent);
    node->parent = newParent;
    node->right = oldLeft;
    if (oldLeft) {
        oldLeft->parent = node;
    }
    updateRoot(tree, newParent);
}

static void rightRotate(rbtree *tree, rbtreeNode *node) {
    rbtreeNode *newParent = node->left;
    rbtreeNode *oldRight = newParent->right;
    newParent->right = node;
    newParent->parent = node->parent;
    replaceChild(tree, node, newParent);
    node->parent = newParent;
    node->left = oldRight;
    if (oldRight) {
        oldRight->parent = node;
    }
    updateRoot(tree, newParent);
}

static void fixInsert(rbtree *tree, rbtreeNode *current) {
    for (;;) {
        rbtreeNode *uncleNode;
        rbtreeNode *parentNode;
        rbtreeNode *grandParentNode;
        parentNode = current->parent;
        if (!parentNode) {
            current->isRed = 0;
            break;
        }
        if (!parentNode->isRed) {
            break;
        }
        grandParentNode = parentNode->parent;
        uncleNode = parentNode == grandParentNode->left ? grandParentNode->right : grandParentNode->left;
        if (uncleNode && uncleNode->isRed) {
            parentNode->isRed = 0;
            uncleNode->isRed = 0;
            uncleNode->parent->isRed = 1;
            current = uncleNode->parent;
            continue;
        } else {
            if (parentNode == parentNode->parent->left) {
                if (current == parentNode->right) {
                    leftRotate(tree, parentNode);
                }
                rightRotate(tree, grandParentNode);
                swapColors(grandParentNode, grandParentNode->parent);
            } else {
                if (current == parentNode->left) {
                    rightRotate(tree, parentNode);
                }
                leftRotate(tree, grandParentNode);
                swapColors(grandParentNode, grandParentNode->parent);
            }
        }
        break;
    }
}

rbtreeNode *rbtreeFindNode(rbtree *tree, const void *key) {
    rbtreeNode *lastNode = 0;
    int lastCmp = 0;
    return rbtreeSearch(tree, key, &lastNode, &lastCmp);
}

rbtreeNode *rbtreeInsertNode(rbtree *tree, rbtreeNode *insert) {
    rbtreeNode *lastNode = 0;
    int lastCmp = 0;
    rbtreeNode *existing = rbtreeSearch(tree, keyOfNode(tree, insert), &lastNode, &lastCmp);
    if (existing) {
        return existing;
    }
    insert->left = 0;
    insert->right = 0;
    if (!lastNode) {
        insert->isRed = 0;
        insert->parent = 0;
        tree->root = insert;
        return insert;
    }
    insert->parent = lastNode;
    insert->isRed = 1;
    if (lastCmp < 0) {
        lastNode->left = insert;
    } else {
        lastNode->right = insert;
    }
    fixInsert(tree, insert);
    return insert;
}

void *rbtreeFind(rbtree *tree, const void *key) {
    rbtreeNode *node = rbtreeFindNode(tree, key);
    if (!node) {
        return 0;
    }
    return (void *)((char *)node - tree->nodeOffsetOfParent);
}

void *rbtreeInsert(rbtree *tree, void *insert) {
    rbtreeNode *node = rbtreeInsertNode(tree, (rbtreeNode *)((char *)insert + tree->nodeOffsetOfParent));
    if (!node) {
        return 0;
    }
    return (void *)((char *)node - tree->nodeOffsetOfParent);
}

#if RBTREE_DEBUG

static void printNode(rbtree *tree, rbtreeNode *node, rbtreeKeyToIntConverter converter) {
    if (!node || (!node->left && !node->right)) {
        return;
    }
    if (node->left) {
        printf("(%d:%c)", converter(keyOfNode(tree, node->left)), node->left->isRed ? 'R' : 'B');
    } else {
        printf("NULL");
    }
    printf(" <- (%d:%c) -> ", converter(keyOfNode(tree, node)), node->isRed ? 'R' : 'B');
    if (node->right) {
        printf("(%d:%c)", converter(keyOfNode(tree, node->right)), node->right->isRed ? 'R' : 'B');
    } else {
        printf("NULL");
    }
    printf("\n");
    printNode(tree, node->left, converter);
    printNode(tree, node->right, converter);
}

void rbtreePrint(rbtree *tree, rbtreeKeyToIntConverter converter) {
    if (!tree->root) {
        printf("(Empty)\n");
        return;
    }
    printNode(tree, tree->root, converter);
}

int rbtreeDumpNodeToArray(rbtree *tree, rbtreeNode *node, rbtreeKeyToIntConverter converter, int *array, int maxNum, int *num) {
    if (!node) {
        return 0;
    }
    if (*num >= maxNum) {
        return -1;
    }
    array[(*num)++] = converter(keyOfNode(tree, node));
    if (0 != rbtreeDumpNodeToArray(tree, node->left, converter, array, maxNum, num)) {
        return -1;
    }
    if (0 != rbtreeDumpNodeToArray(tree, node->right, converter, array, maxNum, num)) {
        return -1;
    }
    return 0;
}

int rbtreeDumpToArray(rbtree *tree, rbtreeKeyToIntConverter converter, int *array, int maxNum) {
    int num = 0;
    int result = rbtreeDumpNodeToArray(tree, tree->root, converter, array, maxNum, &num);
    if (0 != result) {
        return -1;
    }
    return num;
}

#endif
