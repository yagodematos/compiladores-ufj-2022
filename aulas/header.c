#include <stdlib.h>
#include <string.h>

#include "header.h"


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

int search_symbol(char *nome) {
    for (int i = 0; i < simbolo_qtd; i++) {
        if (strcmp(t_simbolos[i].nome, nome) == 0) {
            return i;
        }
    }

    return -1;
}

void check_declared_vars(node **root, node *no) {
    node *nr = *root;

    if (no->type == ASSIGN) {
        int s = search_symbol(no->children[0]->name);

        if (s != -1) {
            t_simbolos[s].exists = true;
        }
    }
}

void visitor_leaf_first(node **root, visitor_action action) {
    node * r = *root;

    for (int i = 0; i < r->childcount; i++) {
        visitor_leaf_first(&r->children[i], action);

        if (action) {
            action(root, r->children[i]);
        }
    }
}

simbolo *simbolo_novo(char *nome, int token) {
    t_simbolos[simbolo_qtd].nome = nome;
    t_simbolos[simbolo_qtd].token = token;

    simbolo *result = &t_simbolos[simbolo_qtd];
    simbolo_qtd++;

    return result;
}

bool simbolo_existe(char *nome) {
    for (int i = 0; i < simbolo_qtd; i++) {
        if (strcmp(t_simbolos[i].nome, nome) == 0) {
            return true;
        }
    }

    return false;
}

void debug() {
    printf("Simbolos: \n");
    for (int i = 0; i < simbolo_qtd; i++) {
        printf("\t%s\n", t_simbolos[i].nome);
    }
}
