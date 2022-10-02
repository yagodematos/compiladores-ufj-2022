#include <stdlib.h>
#include "header.h"

node *create_node(enum node_type nt, int children) {
    static int IDCOUNT = 0;

    node *new_node = (node*) calloc(1, sizeof(node) + sizeof(node*) * (children - 1));
    new_node->type = nt;
    new_node->childcount = children;
    new_node->id = IDCOUNT++;

    return new_node;
}

void print(node *root) {
    FILE *f = fopen("output.dot", "w");

    if (f == NULL) {
        fprintf(stderr, "Error: Unable to open file\n");
        return;
    }

    fprintf(f, "graph G {\n");
    print_rec(f, root);
    fprintf(f, "}");

    fclose(f);
}

void print_rec(FILE *f, node *root) {
    fprintf(f, "N%d;\n", root->id);

    for (int i = 0; i < root->childcount; i++) {
        print_rec(f, root->children[i]);
        fprintf(f, "N%d -- N%d;\n", root->id, root->children[i]->id);
    }
}
