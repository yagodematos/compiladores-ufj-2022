%{
	#include <stdio.h>
	#include "header.h"
	#include "grammar.tab.h"
%}

%option yylineno

D	[0-9]
L	[a-zA-Z_]
N 	{D}+
F 	("."{N})|({N}"."{N})
%%

[ \t\r\n]			{}
"="					{ return '='; }
"^"					{ return '^'; }
"*"					{ return '*'; }
"/"					{ return '/'; }
"+"					{ return '+'; }
"-"					{ return '-'; }

">"					{ return '>'; }
"<"					{ return '>'; }
"!"					{ return '!'; }

"print"				{ return TOK_PRINT; }
"var"				{ return TOK_VAR; }

"and"				{ return TOK_AND; }
"or"				{ return TOK_OR; }

"if"				{ return TOK_IF; }
"else"				{ return TOK_ELSE; }
"while"				{ return TOK_WHILE; }
"end"				{ return TOK_END; }

"("					{ return '('; }
")"					{ return ')'; }

"{"					{ return '{'; }
"}"					{ return '}'; }

{D}+				{ yylval.args.intv = atoi(yytext); return TOK_INTEGER; }
{F}					{ yylval.args.dblv = atof(yytext); return TOK_FLOAT; }
{L}({L}|{D})*		{ yylval.args.ident = strndup(yytext, yyleng); return TOK_IDENT; }
\"[a-zA-Z0-9_]+\" 	{ yylval.args.strv = strndup(yytext, yyleng); return TOK_STRING; }


 /* comentário */
.					{ printf("Invalid caracter: %c.\n", yytext[0]); }

%%

int yywrap() {
	return 1;
}

int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("%s [file]\n", argv[0]);
		return 1;
	}

	FILE *f = fopen(argv[1], "r");

	if(!f) {
		printf("Can\'t open the file %s\n", argv[1]);
	}

	yyin = f;
	yyparse();
	fclose(f);
	return 0;
}
