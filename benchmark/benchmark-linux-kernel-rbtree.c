////////////////////////////////////////////////////////////////////////////////
// Following code copy & modify from https://www.kernel.org/doc/Documentation/rbtree.txt
#include <linux/rbtree.h>

struct mytype {
	struct rb_node node;
	int key;
};

struct mytype *my_search(struct rb_root *root, int number)
{
  struct rb_node *node = root->rb_node;

  while (node) {
      struct mytype *data = container_of(node, struct mytype, node);
      int result;

      result = number - data->key;

      if (result < 0)
          node = node->rb_left;
      else if (result > 0)
          node = node->rb_right;
      else
          return data;
  }
  return NULL;
}

int my_insert(struct rb_root *root, struct mytype *data)
{
  struct rb_node **new = &(root->rb_node), *parent = NULL;

  /* Figure out where to put new node */
  while (*new) {
      struct mytype *this = container_of(*new, struct mytype, node);
      int result = data->key - this->key;

      parent = *new;
      if (result < 0)
          new = &((*new)->rb_left);
      else if (result > 0)
          new = &((*new)->rb_right);
      else
          return FALSE;
  }

  /* Add new node and rebalance tree. */
  rb_link_node(&data->node, parent, new);
  rb_insert_color(&data->node, root);

  return TRUE;
}
////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <sys/resource.h>

#define GEN_NUM 1000000

int main(int argc, char *argv[]) {
    struct rb_root mytree = RB_ROOT;
    struct mytype *nodes = (struct mytype *)calloc(GEN_NUM, sizeof(struct mytype));
    unsigned int seed = 1511797570;
    struct rusage begin;
    struct rusage end;
    int i;

    srand(seed);
    for (i = 0; i < GEN_NUM; ++i) {
        nodes[i].key = rand();
    }

    getrusage(RUSAGE_SELF, &begin);
    for (i = 0; i < GEN_NUM; ++i) {
        my_insert(&mytree, &nodes[i]);
    }
    getrusage(RUSAGE_SELF, &end);
    printf("linux,insert,%d,%ld\n", GEN_NUM, begin.ru_utime.tv_sec * 100000 + begin.ru_utime.tv_usec);

    getrusage(RUSAGE_SELF, &begin);
    for (i = 0; i < GEN_NUM; ++i) {
        my_search(&mytree, nodes[i].key);
    }
    getrusage(RUSAGE_SELF, &end);
    printf("linux,search,%d,%ld\n", GEN_NUM, begin.ru_utime.tv_sec * 100000 + begin.ru_utime.tv_usec);

    getrusage(RUSAGE_SELF, &begin);
    for (i = 0; i < GEN_NUM; ++i) {
        struct mytype *data = my_search(&mytree, nodes[i].key);
        if (data) {
            rb_erase(&data->node, &mytree);
        }
    }
    getrusage(RUSAGE_SELF, &end);
    printf("linux,delete,%d,%ld\n", GEN_NUM, begin.ru_utime.tv_sec * 100000 + begin.ru_utime.tv_usec);

    return 0;
}
