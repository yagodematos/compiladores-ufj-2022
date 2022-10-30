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
    GENERIC,
    VAR,
    STRING,
    IF,
    ELSE,
    OR,
    AND,
    GREATER,
    LESSER,
    EQUAL,
    GREATER_E,
    LESSER_E,
    NOT_EQUAL,
    WHILE
};

static const char * node_type_name[] = {
    "program",
    "=",
    "+",
    "-",
    "*",
    "/",
    "%",
    "print",
    "^",
    "()",
    "stmt",
    "int",
    "float",
    "ident",
    "generic",
    "var",
    "string",
    "if",
    "else",
    "or",
    "and",
    ">",
    "<",
    "==",
    ">=",
    "<=",
    "!=",
    "while"
};

typedef struct {
    int intv;
    double dblv;
    char *ident;
    char *strv;
} token_args;

struct node {
    int id;
    enum node_type type;
    int childcount;
    double dblv;
    int intv;
    char *strv;

    char *name;

    struct node *children[1];
};

typedef struct node node;

node *create_node(enum node_type, int children);

void print(node *root);

void print_rec(FILE *f, node *root);
