#include <stdlib.h>

#include "header.h"
#include <string.h>

node *create_node(enum node_type nt, int children) {
    static int IDCOUNT = 0;

    node *new_node = (node*) calloc(1, sizeof(node) + sizeof(node*) * (children - 1));
    new_node->type = nt;
    new_node->childcount = children;
    new_node->id = IDCOUNT++;

    return new_node;
}


const char * get_label(node *n) {
    static char aux[100];
    switch (n->type) {
        case INTEGER:
            sprintf(aux, "%d", n->intv);
            return aux;
        case FLOAT:
            sprintf(aux, "%f", n->dblv);
            return aux;
        case IDENT:
            return n->name;
        case STRING:
            sprintf(aux, "%s", n->strv + 1);
            aux[strlen(aux) - 1] = '\0';
            return aux;
        default:
            return node_type_name[n->type];
    }
}


void print_rec(FILE *f, node *root) {
    fprintf(f, "    N%d[label=\"%s\"];\n", root->id, get_label(root));

    for (int i = 0; i < root->childcount; i++) {
        print_rec(f, root->children[i]);
        fprintf(f, "    N%d -- N%d;\n", root->id, root->children[i]->id);
    }
}


void print(node *root) {
    FILE *f = fopen("output.dot", "w");

    if (f == NULL) {
        fprintf(stderr, "Error: Unable to open file\n");
        return;
    }

    fprintf(f, "graph G {\n");
    print_rec(f, root);
    fprintf(f, "}\n");

    fclose(f);
}
