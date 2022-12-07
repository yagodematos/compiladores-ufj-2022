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

extern int yylineno;

struct node {
    int id;
    int lineno;
    enum node_type type;
    int childcount;
    double dblv;
    int intv;
    char *strv;
    char *name;

    struct node *children[1];
};

typedef struct node node;

typedef struct {
    char *nome;
    int token;
    bool exists;
} simbolo;

static int error_count = 0;
static int simbolo_qtd = 0;
static simbolo t_simbolos[100];

simbolo *simbolo_novo(char *nome, int token);
bool simbolo_existe(char *nome);
void debug(void);


typedef void (*visitor_action) (node **root, node *no);

void check_declared_vars(node **root, node *no);

void code_generate(node **root, node *no);
void check_ari(node **root, node *no);
void check_log(node **root, node *no);
void check_division_by_zero(node **root, node *no);

void visitor_leaf_first(node **root, visitor_action action);



node *create_node(enum node_type, int children);

void print(node *root);

void print_rec(FILE *f, node *root);
