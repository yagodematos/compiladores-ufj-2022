
%{
	#include <stdio.h>
	#include "calc.tab.h"
%}

%option yylineno

D	[0-9]
L	[a-zA-Z_]

%% 

[ \t\r\n]			{}
"print"				{ return TOK_PRINT; }
"="					{ return '='; }
"^"					{ return '^'; }
"*"					{ return '*'; }
"/"					{ return '/'; }
"+"					{ return '+'; }
"-"					{ return '-'; }
"("					{ return '('; }
")"					{ return ')'; }


{D}+				{ return TOK_INTEGER; }
{D}+\.{D}+			{ return TOK_FLOAT; }
{L}({L}|{D})*		{ return TOK_IDENT; }
 /* [a-zA-Z_][a-zA-Z0-9_]* {} */


 /* comentário */
.					{ printf("Invalid caracter: %c.\n", yytext[0]); }

%%

int yywrap() {
	return 1;
}

int main(int argc, char *argv[]) {
	
	if (argc <= 1) {
		printf("%s [file]\n", argv[0]);
		return 1;
	}

	FILE *f = fopen(argv[1], "r");
	yyin = f;
	yyparse();
	fclose(f);
	return 0;
}

