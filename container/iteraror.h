#pragma once

struct vrs_iterator;

typedef void *vrs_iterator_element;
typedef  vrs_iterator_element (*vrs_next)(struct vrs_iterator*);
typedef void (*vrs_dispose)(struct vrs_iterator*);
typedef int (*vrs_has)(struct vrs_iterator*);

struct vrs_iterator {
    vrs_has has;
    vrs_next next;
    vrs_dispose dispose;
};

typedef struct vrs_iterator vrs_iterator;

#define vrs_foreach(iterator, var, code) while((iterator)->has(iterator)) { \
     var = (iterator)->next(iterator);                 \
     code \
}
