#pragma once

enum node_type {
    PROGRAM,
    ASSIGN,
    SUM,
    MINUS,
    MULTI,
    DIVIDE,
    PRINT,
    POW,
    FLOAT,
    INTEGER,
    PAREN,
    GENERIC,
    MODULO,
    STMT,
    IDENT
};

struct node {
    int id;
    enum node_type type;
    int childcount;
    double value;
    char *name;

    struct node *children[1];
};

typedef struct node node;

node *create_node(enum node_type, int children);
