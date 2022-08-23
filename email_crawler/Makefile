URL = https://portalufj.jatai.ufg.br/p/35341-ouvidoria
URL_TEST = https://computacao.jatai.ufg.br/n/36222-corpo-docente

default: build

build: clean
	gcc -Wall -o cmp main.c util.c -lcurl

clean:
	rm -rf cmp

test: build
	./cmp $(URL)
	./cmp $(URL_TEST)
