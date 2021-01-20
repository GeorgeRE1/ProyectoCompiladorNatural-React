all: bison flex compilar ejecutar
bison: simbolos.y
	bison simbolos.y -d

flex: simbolos.tab.h simbolos.l
	flex simbolos.l

compilar: simbolos.c	simbolos.tab.c lex.yy.c
	gcc -o Tabla.out Tabla.c Archivo.c simbolos.tab.c lex.yy.c -ll -w

ejecutar: Tabla.out
	./Tabla.out
