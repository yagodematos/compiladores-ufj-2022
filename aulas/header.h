#pragma once

#include <stdio.h>

enum node_type {
    PROGRAM,
    ASSIGN,
    SUM,
    MINUS,
    MULTI,
    DIVIDE,
    MODULO,
    PRINT,
    POW,
    PAREN,
    STMT,
    INTEGER,
    FLOAT,
    IDENT,
    GENERIC
};

static const char * node_type_name[] = {
    "program", "=", "+", "-", "*",
    "/", "%", "print", "^", "()", "stmt",
    "int", "float", "ident", "generic"
};

typedef struct {
    int intv;
    double dblv;
    char *ident;
} token_args;

struct node {
    int id;
    enum node_type type;
    int childcount;
    double dblv;
    int intv;

    char *name;

    struct node *children[1];
};

typedef struct node node;

node *create_node(enum node_type, int children);

void print(node *root);

void print_rec(FILE *f, node *root);
