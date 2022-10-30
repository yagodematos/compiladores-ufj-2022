%{
#include <stdio.h>
#include <stdlib.h>

#include  "header.h"

int yyerror(const char *s);
int yylex (void);

extern int yylineno;
%}

%union {
    token_args args;
	struct node *n;
}

%define parse.error verbose

%token TOK_PRINT TOK_VAR TOK_AND TOK_OR TOK_IF TOK_ELSE TOK_WHILE TOK_END
%token <args> TOK_IDENT TOK_INTEGER TOK_FLOAT TOK_STRING
/* %token TOK_LITERAL */

%type <n> program stmts stmt atribuicao aritmetica term exp factor
%type <n> logical lterm lfactor if loop p

%start program
%%

program:
    stmts {
        node *prog = create_node(PROGRAM, 1);
        prog->children[0] = $1;

        print(prog);
        // chamada da verificação semantica
        // chamada da geração de codigo

    }
    ;

stmts:
    stmts stmt {
        node *n = $1;
        n = (node *) realloc(n, sizeof(node) + sizeof(node*) * (n->childcount));

        n->children[n->childcount++] = $2;
        $$ = n;

    }
    | stmt {
        $$ = create_node(STMT, 1);
        $$->children[0] = $1;
    }
    ;

// if (while) while function
stmt:
    atribuicao {
        $$ = $1;
    }
    | logical {
        $$ = $1;
    }
    | if {
        $$ = $1;
    }
    | loop {
        $$ = $1;
    }
    | p {
        $$ = $1;
    }
    ;

p:
    TOK_PRINT TOK_IDENT {
        $$ = create_node(PRINT, 0);
    }
    ;


if:
    TOK_IF logical stmts TOK_END {
        $$ = create_node(IF, 2);
        $$->children[0] = $2;
        $$->children[1] = $3;
    }
    | TOK_IF logical stmts TOK_ELSE stmts TOK_END {
        $$ = create_node(IF, 3);
        $$->children[0] = $2;
        $$->children[1] = $3;
        $$->children[2] = $5;
    }
    ;

loop:
    TOK_WHILE logical stmts TOK_END {
        $$ = create_node(WHILE, 2);
        $$->children[0] = $2;
        $$->children[1] = $3;
    }
    ;

atribuicao:
    TOK_VAR TOK_IDENT '=' aritmetica {
        $$ = create_node(ASSIGN, 2);
        node *aux = create_node(IDENT, 0);
        aux->name = $2.ident;
        $$->children[0] = aux;
        $$->children[1] = $4;
    }
    | TOK_VAR TOK_IDENT '=' logical {
        $$ = create_node(ASSIGN, 2);
        node *aux = create_node(IDENT, 0);
        aux->name = $2.ident;
        $$->children[0] = aux;
        $$->children[1] = $4;
    }
    ;

logical:
    logical TOK_OR lterm {
        $$ = create_node(OR, 2);
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | lterm {
        $$ = $1;
    }
    ;

lterm:
    lterm TOK_AND lfactor {
        $$ = create_node(AND, 2);
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | lfactor {
        $$ = $1;
    }
    ;

lfactor:
    '(' logical ')' {
        $$ = $2;
    }
    | aritmetica '>' aritmetica {
        $$ = create_node(GREATER, 2);
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | aritmetica '<' aritmetica {
        $$ = create_node(LESSER, 2);
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | aritmetica '=''=' aritmetica {
        $$ = create_node(EQUAL, 2);
        $$->children[0] = $1;
        $$->children[1] = $4;
    }
    | aritmetica '>''=' aritmetica {
        $$ = create_node(GREATER_E, 2);
        $$->children[0] = $1;
        $$->children[1] = $4;
    }
    | aritmetica '<''=' aritmetica {
        $$ = create_node(LESSER_E, 2);
        $$->children[0] = $1;
        $$->children[1] = $4;
    }
    | aritmetica '!''=' aritmetica {
        $$ = create_node(NOT_EQUAL, 2);
        $$->children[0] = $1;
        $$->children[1] = $4;
    }
    ;


aritmetica:
    aritmetica '+' term {
        $$ = create_node(SUM, 2);
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | aritmetica '-' term {
        $$ = create_node(MINUS, 2);
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | term {
        $$ = $1;
    }
    ;

term:
    term '*' exp {
        $$ = create_node(MULTI, 2);
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | term '/' exp {
        $$ = create_node(DIVIDE, 2);
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | term '%' exp {
        $$ = create_node(MODULO, 2);
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | exp {
        $$ = $1;
    }
    ;

exp:
    exp '^' factor {
        $$ = create_node(POW, 2);
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | factor {
        $$ = $1;
    }
    ;

factor:
    '(' aritmetica ')' {
        $$ = $2;
    }
    | TOK_IDENT {
        $$ = create_node(IDENT, 0);
        $$->name = $1.ident;
    }
    | TOK_INTEGER {
        $$ = create_node(INTEGER, 0);
        $$->intv = $1.intv;
    }
    | TOK_FLOAT {
        $$ = create_node(FLOAT, 0);
        $$->dblv = $1.dblv;
    }
    | TOK_STRING {
        $$ = create_node(STRING, 0);
        $$->strv = $1.strv;
    }
    ;


%%

int yyerror(const char *s) {
    printf("Parser erro na linha %d: %s\n", yylineno, s);
    return 1;
}
