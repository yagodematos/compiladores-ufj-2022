%{
#include <stdio.h>

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

%token TOK_PRINT
%token <args> TOK_IDENT TOK_INTEGER TOK_FLOAT
/* %token TOK_LITERAL */

%type <n> program stmts stmt atribuicao aritmetica term exp factor

%start program
%%

program:
    stmts {
        node *prog = create_node(PROGRAM, 1);
        prog->children[0] = $1;

        print(prog);
        // chamada da arvore abstrata
        // chamada da verificação semantica
        // chamada da geração de codigo

    }
    ;

stmts:
    stmt stmts {
        $$ = create_node(STMT, 2);
        $$->children[0] = $1;
        $$->children[1] = $2;
    }
    | stmt {
        $$ = create_node(STMT, 1);
        $$->children[0] = $1;
    }
    ;

stmt:
    atribuicao {
        $$ = create_node(GENERIC, 1);
        $$->children[0] = $1;
    }
    |TOK_PRINT aritmetica {
        $$ = create_node(PRINT, 1);
        $$->children[0] = $2;
    }
    ;

atribuicao:
    TOK_IDENT '=' aritmetica {
        $$ = create_node(ASSIGN, 2);
        node *aux = create_node(IDENT, 0);
        aux->name = $1.ident;
        $$->children[0] = aux;
        $$->children[1] = $3;
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
        $$ = create_node(GENERIC, 1);
        $$->children[0] = $1;
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
        $$ = create_node(GENERIC, 1);
        $$->children[0] = $1;
    }
    ;

exp:
    exp '^' factor {
        $$ = create_node(POW, 2);
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | factor {
        $$ = create_node(GENERIC , 1);
        $$->children[0] = $1;
    }
    ;

factor:
    '(' aritmetica ')' {
        $$ = create_node(PAREN, 1);
        $$->children[0] = $2;
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
    ;


%%

int yyerror(const char *s) {
    printf("Parser erro na linha %d: %s\n", yylineno, s);
    return 1;
}
