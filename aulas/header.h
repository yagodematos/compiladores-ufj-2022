#pragma once

#include <stdio.h>
#include <stdbool.h>

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

typedef struct {
    char *nome;
    int token;
    bool exists;
} simbolo;

static int simbolo_qtd = 0;
static simbolo t_simbolos[100];

simbolo *simbolo_novo(char *nome, int token);
bool simbolo_existe(char *nome);
void debug();


typedef void (*visitor_action) (node **root, node *no);

void check_declared_vars(node **root, node *no);

void visitor_leaf_first(node **root, visitor_action action);


node *create_node(enum node_type, int children);

void print(node *root);

void print_rec(FILE *f, node *root);
