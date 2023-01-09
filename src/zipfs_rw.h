#ifndef __ZIPFS_RW_H__
#define __ZIPFS_RW_H__

#include <libtree.h>

#include <stdbool.h>
#include <stddef.h>

typedef struct node_de_vd_tree {
    size_t n_children;
    struct node_bidi_ndtree *p_parent;
    struct node_dirtree *p_children;
};

#endif /* __ZIPFS_RW_H__ */
