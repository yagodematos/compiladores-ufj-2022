CC=gcc

all: pjc

grammar.tab.c grammar.tab.h: grammar.y
	bison -d grammar.y

lex.yy.c: lexer.l grammar.tab.h
	flex lexer.l

pjc: lex.yy.c grammar.tab.c grammar.tab.h
	$(CC) -o pjc grammar.tab.c lex.yy.c header.c

test: all
	./pjc test.pj

clean:
	$(RM) pjc grammar.tab.c lex.yy.c grammar.tab.h output.out output.dot

clean-img:
	$(RM) *.png

# need python3, python3-graphviz, python3-tk
view: test
	python3 ./generate_view.py
