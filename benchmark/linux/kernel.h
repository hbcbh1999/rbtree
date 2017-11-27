#ifndef FAKE_KERNEL_H
#define FAKE_KERNEL_H

#define NULL (void *)0

#define FALSE   0
#define TRUE    1

typedef unsigned long size_t;

#if defined(offsetof)
  #undef offsetof
  #define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#else
  #define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#if defined(container_of)
  #undef container_of
  #define container_of(ptr, type, member) \
                  ((type *) ((char *)(ptr) - offsetof(type, member)))
#else
    #define container_of(ptr, type, member) \
                    ((type *) ((char *)(ptr) - offsetof(type, member)))
#endif

#endif
