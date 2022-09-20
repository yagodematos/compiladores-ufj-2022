#include "header.h"
#include <stdlib.h>

node *create_node(enum node_type nt, int children) {
    static int IDCOUNT = 0;
    
    node *new_node = (node*) calloc(1, sizeof(node) + sizeof(node*) * (children - 1));
    new_node->type = nt;
    new_node->childcount = children;    
    new_node->id = IDCOUNT++;

    return new_node;
}
