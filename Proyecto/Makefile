all: clean bison flex compilar run
bison: simbolos.y
	bison simbolos.y -d

flex: simbolos.tab.h simbolos.l
	flex simbolos.l

compilar: simbolos.c	simbolos.tab.c lex.yy.c
	gcc -o Tabla.out Tabla.c Archivo.c simbolos.tab.c lex.yy.c -ll -w

ejecutar: Tabla.out
	./Tabla.out

clean:
	clear
	rm -f Tabla.out main.o lex.yy.o lex.yy.c simbolos.tab.h simbolos.tab.c simbolos.c

run: Tabla.out
	./Tabla.out