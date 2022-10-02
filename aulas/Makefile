CC=gcc

all: calc

calc.tab.c calc.tab.h:	calc.y
	bison -d calc.y

lex.yy.c: calc.l calc.tab.h
	flex calc.l

calc: lex.yy.c calc.tab.c calc.tab.h
	$(CC) -o calc calc.tab.c lex.yy.c header.c

test: all
	./calc teste.txt

clean:
	rm calc calc.tab.c lex.yy.c calc.tab.h output.dot

# need python3, python3-graphviz, python3-tk
view: test
	python3 ./generate_view.py
