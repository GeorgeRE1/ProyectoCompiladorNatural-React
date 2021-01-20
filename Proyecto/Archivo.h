#ifndef ARCHIVO
#define ARCHIVO
#include "Tabla.h"
int generarArchivos(Nodo *);
int generarModels(char* bd, char* tabla, Nodo * indice);
int generarFunctions(char* bd, char* tabla, Nodo * indice);
int generarRoute(char* bd, char* tabla, Nodo * indice);

#endif