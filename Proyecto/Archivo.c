#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Archivo.h"

#define MAX 100

int generarArchivos(Nodo * ind)
{
	Nodo * indice;
	printf(YELLOW "Iniciando...%s\n",RESETCOL );

	char* archivo = "";

	char* bd;
	char* tabla;
	int contador_campos = 0;
	//printf("checa nombre %s ", nombre);
	for (indice = ind; indice != NULL; indice = indice -> siguiente)
	{
		if(indice -> tipo == 'b')
			bd = indice -> name;
		else if(indice -> tipo == 't')
			tabla = indice -> name;
	}
	generarModels(bd,tabla,ind);
	return 1;
}

int generarModels(char* bd, char* tabla, Nodo * ind)
{
	FILE *fp;
	Nodo * indice;
	char arc[1024]="";
	strcat(arc,tabla);
	strcat(arc,"M.txt");
	printf("%s\n", arc);
	fp = fopen(arc, "w+");
	fprintf(fp,"const Sequelize = require('sequelize')\nconst db = require('../database/db')\n\n");
  	fprintf(fp,"module.exports = db.sequelize.define(\n\t'");
  	fprintf(fp,"%s',\n\t{\n",tabla);
  	for (indice = ind; indice != NULL; indice = indice -> siguiente)
	{
		if(indice -> tipo == 'c')
  			fprintf(fp, "\t%s : {\n\t\t\ttype: Sequelize.%s\n\t\t},\n",indice->name, indice-> tipod);
  	}
  	fprintf(fp, "\t},\n\t{\n\t\ttimestamps: false\n\t}\n)");
  	fclose(fp);
}

int generarFunctions(char* bd, char* tabla, Nodo * indice)
{
	//En produccion, algun dia se terminara...
}

int generarRoute(char* bd, char* tabla, Nodo * indice)
{
	//En produccion, algun dia se terminara...
}
