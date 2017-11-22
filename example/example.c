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
    node fourthNode;
    node fifthNode;
    node *find;
    int firstNum = 10;
    int secondNum = 5;
    int thirdNum = 9;
    int fourthNum = 4;
    int fifthNum = 3;

    rbtreeInit(&t, node, node_, key, rbtreeIntComparator);

    firstNode.key = firstNum;
    rbtreeInsert(&t, &firstNode);
    
    printf("After insert first num:\n");
    rbtreePrint(&t, keyToInt);
    printf("\n");

    secondNode.key = secondNum;
    rbtreeInsert(&t, &secondNode);
    
    printf("After insert second num:\n");
    rbtreePrint(&t, keyToInt);
    printf("\n");

    thirdNode.key = thirdNum;
    rbtreeInsert(&t, &thirdNode);
    
    printf("After insert third num:\n");
    rbtreePrint(&t, keyToInt);
    printf("\n");

    fourthNode.key = fourthNum;
    rbtreeInsert(&t, &fourthNode);
    
    printf("After insert fourth num:\n");
    rbtreePrint(&t, keyToInt);
    printf("\n");

    fifthNode.key = fifthNum; 
    rbtreeInsert(&t, &fifthNode);
    
    printf("After insert fifth num:\n");
    rbtreePrint(&t, keyToInt);
    printf("\n");

    find = (node *)rbtreeFind(&t, &fourthNum);
    if (find) {
        printf("found(%d)!\n", find->key);
    } else {
        printf("not found!\n");
    }
    return 0;
}
