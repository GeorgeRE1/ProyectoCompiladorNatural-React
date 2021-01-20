%{
	#include <math.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <string.h>
	#include "Tabla.h"

%}

/* Declaraciones de BISON */

%union
{
	int ent;
	double real;
	char* let;
	char* bd;
	char* tab;
	void* var;
}

%token <ent> ENTERO
%token <real> REAL
%token <let> CAD
%token <let> VARIABLE
%token <bd> BD
%token <tab> TABLA
%token INT STRING DOUBLE DATE FIN

%type <ent> opint
%type <ent> errores
%type <let> declarar
%type <bd> base
%type <tab> tabla


%left '+' ';'
%left VARIABLE
%left INT STRING DOUBLE DATE FIN

/* Gramática */
%%

input:    /* cadena vacía */
        | input line
;

line:     		'\n'				{ printf("> ");}
	|base							{ printf("\t ");}
	|errores 		'\n'			{/* Reglas para cachar los errores */}
;

base:	
	 BD VARIABLE ';'				{ $$ = $2; /*printf("%s>\n",$$);*/ insertarBD($2);}	
	|tabla 							{ printf("\t\t> ");}
	
;

tabla:	
	TABLA VARIABLE ';'	'\n'		{ $$ = $2; /*printf("%s\n\t\t" , $$);*/ insertarTabla($2,$$); }
	|declarar						{ }
	|fin							{ }
;

declarar:	
	VARIABLE INT opint ';' '\n'		{ /*printf(GREEN"Tabla %s %s" , existetabla(),RESETCOL); */int aux = $3; /*printf(GREEN"\t\t%s int %d%s\n", $1,aux,RESETCOL);*/ insertarCampo($1,"INTEGER",$$,$3);}
	| VARIABLE DOUBLE opint ';'	'\n'	{ /*printf(GREEN"Tabla %s %s" , existetabla(),RESETCOL); */int aux = $3; /*printf(GREEN"\t\t%s double %d%s\n", $1,aux,RESETCOL);*/ insertarCampo($1,"DOUBLE",$$,$3);}
	| VARIABLE STRING opint ';'	'\n'	{ /*printf(GREEN"Tabla %s %s" , existetabla(),RESETCOL); */int aux = $3; /*printf(GREEN "\t\t%s string %d%s\n", $1,aux,RESETCOL);*/insertarCampo($1,"STRING",$$,$3);}
	| VARIABLE DATE ';'		'\n'		{ /*printf(GREEN"Tabla %s %s\n" , existetabla(),RESETCOL); printf(GREEN "\t\t%s date%s\n", $1,RESETCOL);*/insertarCampo($1,"DATE",$$,0);}
;

fin:
	FIN 								{GuardarArchivo(); exit(0);}
;

//Producciones de tipo entero
opint:
		ENTERO 				  		{ $$ = $1; }
;

//Producciones de errores
errores:
	';'															{  }
;

%%
int main()
{
	int d=0;
	int k;
	printf("\n> ");
	yyparse();
}

yyerror (char *s){  printf (RED "-> %s %s\n",s, RESETCOL ); }
int yywrap(){  return 1;}
