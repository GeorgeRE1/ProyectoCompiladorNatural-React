#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Tabla.h"
#define  MAX 1000


Nodo * cabeza = NULL;

void insertarBD(char* nombre)
{
	Nodo *nuevo ;
	nuevo = NuevoNodoBD(nombre);
	nuevo -> siguiente = cabeza;
	cabeza = nuevo;
}
void insertarTabla(char* nombre,char* perte)
{
	Nodo *nuevo ;
	nuevo = NuevoNodoTabla(nombre,perte);
	nuevo -> siguiente = cabeza;
	cabeza = nuevo;
}
void insertarCampo(char* nombre, char* tipo,char* perte, int tamanio)
{
	Nodo *nuevo ;
	nuevo = NuevoNodoCampo(nombre,tipo,perte,tamanio);
	nuevo -> siguiente = cabeza;
	cabeza = nuevo;
}

Nodo* NuevoNodoBD(char* nombre)
{	
	Nodo *a ;
	a = (Nodo*)malloc(sizeof(Nodo)); 			/* asiqna memoria a nuevo nodo */
	a-> tipo = 'b';
	a-> name = nombre;
	a-> siguiente = NULL;
	return a;
}
Nodo* NuevoNodoTabla(char* nombre, char* perte)
{
	Nodo *a ;
	a = (Nodo*)malloc(sizeof(Nodo)); 			/* asiqna memoria a nuevo nodo */
	a-> tipo = 't';
	a-> pert = perte;
	a-> name = nombre;
	a-> siguiente = NULL;
	return a;
}
Nodo* NuevoNodoCampo(char* nombre, char* tipo, char* perte, int tam)
{
	Nodo *a ;
	a = (Nodo*)malloc(sizeof(Nodo)); 			/* asiqna memoria a nuevo nodo */
	a-> tipo = 'c';
	a-> tipod = tipo;
	a-> pert = perte;
	a-> tamanio = tam;
	a-> name = nombre;
	a-> siguiente = NULL;
	return a;
}

//Funciones para obtener los datos de las variables
void * getVariable(char* nombre)
{
	void * nope = NULL;
	double au=0.0;
	Nodo * indice;
	for (indice=cabeza; indice != NULL; indice = indice->siguiente)
	{
		if (strcmp(nombre, indice->name) == 0)
			return (void *)indice;
	}
  printf(BLUE "No existe la variable '%s'! %s\n> ",nombre, RESETCOL );
  return nope;
}
void showVar(void* v)
{
	if(v != NULL)
	{
	    Nodo * var =  (Nodo*) v;
	    switch (var->tipo) 
	    {
	      case 'b': printf(GREEN "%d\n" RESETCOL, var->name); printf("> "); break;
	      case 't': printf(BLUE "%lf\n" RESETCOL, var->name); printf("> ");break;
	      case 'c': printf(YELLOW "'%s'\n" RESETCOL, var->name); printf("> ");break;
	    }
  	}
}
int existe (char* nombre)
{
	Nodo *indice;
	char* aux;
	//printf("checa nombre %s ", nombre);
	for (indice=cabeza; indice != NULL; indice = indice ->siguiente)
	{
		//printf("nombre: %s ", indice -> name);
		aux = indice -> name;
		if (strcmp(nombre, aux) == 0)
		{
			return 1;
		}
	}

	return 0;
}
char* existetabla()
{
	Nodo *indice;
	char* aux;
	for (indice=cabeza; indice != NULL; indice = indice ->siguiente)
	{
		aux = indice -> tipo;
		if (aux == 't')
			return 1;
	}

	return 0;
}
char* existebd()
{
	Nodo *indice;
	char* aux;
	for (indice=cabeza; indice != NULL; indice = indice ->siguiente)
	{
		aux = indice -> tipo;
		if (aux == 'b')
			return 1;
	}

	return 0;
}

void printError(char * m)
{
  printf(RED "%s %s\n> ", m, RESETCOL);
}

void printWarning(char * m)
{
  printf(YELLOW "%s %s\n", m, RESETCOL);
}
void GuardarArchivo()
{
	printf(BLUE "Generando...%s\n",RESETCOL);
	if(generarArchivos(cabeza))
		printf(GREEN"Generado.\n");
	else
		printf(RED "Error generando archivos.\n");
}
