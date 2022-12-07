#include <stdlib.h>
#include <string.h>

#include "header.h"

node *create_node(enum node_type nt, int children) {
    static int IDCOUNT = 0;

    node *new_node = (node*) calloc(1, sizeof(node) + sizeof(node*) * (children - 1));
    new_node->type = nt;
    new_node->childcount = children;
    new_node->id = IDCOUNT++;
    new_node->lineno = yylineno;

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
    else if (no->type == IDENT) {
        if (nr->type == ASSIGN && no == nr->children[0]) return;

        int s = search_symbol(no->name);
        if (s == -1 || !t_simbolos[s].exists) {
            printf("%d: erro: simbolo %s não declarado.\n", no->lineno, no->name);
            error_count++;
        }
    }
}

void check_ari(node **root, node *no) {
    node *nr = *root;

    if (no->type == SUM || no->type == MINUS || no->type == MULTI || no->type == DIVIDE) {

        if (no->children[0]->type != no->children[1]->type) {
            printf("%d: erro: operacao %s com operandos de tipos diferentes  \n", no->lineno, node_type_name[no->type]);
			error_count++;
        }
    }
}

// void check_log(node **root, node *no) {
//     node *nr = *root;

//     if (no->type == AND || no->type == OR) {
//         if ((no->children[0]->type == GREATER ||
//              no->children[0]->type == LESSER ||
//              no->children[0]->type == EQUAL ||
//              no->children[0]->type == GREATER_E ||
//              no->children[0]->type == LESSER_E ||
//              no->children[0]->type == NOT_EQUAL
//             ) &&
//             (no->children[1]->type == GREATER ||
//              no->children[1]->type == LESSER ||
//              no->children[1]->type == EQUAL ||
//              no->children[1]->type == GREATER_E ||
//              no->children[1]->type == LESSER_E ||
//              no->children[1]->type == NOT_EQUAL
//             )) {
//             printf("erro: operacao \"%s\" com operandos de tipos diferentes  \n", node_type_name[no->type]);
// 			error_count++;
//         }
//     }
// }


void check_division_by_zero(node **root, node *no) {
    node *nr = *root;

    if (no->type == DIVIDE) {
        if (no->children[1]->intv == 0) {
            printf("%d: erro: operacao invalida, nao pode dividir por 0  \n", no->lineno);
			error_count++;
        } else if (no->children[1]->dblv == 0) {
            printf("%d: erro: operacao invalida, nao pode dividir por 0  \n", no->lineno);
			error_count++;
        }
    }
}

void code_generate(node **root, node *no) {

    if (no->type == IDENT) {
        printf("%s\n", no->name);
    }
    else if (no->type == ASSIGN) {
        printf(" = ");
    }
    else if (no->type == INTEGER) {
        printf(" %d ", no->intv);
    }
    else if (no->type == FLOAT) {
        printf(" %f ", no->dblv);
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
    t_simbolos[simbolo_qtd].exists = false;

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

void debug(void) {
    printf("Simbolos: \n");
    for (int i = 0; i < simbolo_qtd; i++) {
        printf("\t%s\n", t_simbolos[i].nome);
    }
}
