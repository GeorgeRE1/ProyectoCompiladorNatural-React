#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Archivo.h"

#define MAX 100

int generarArchivos(Nodo * ind)
{
	Nodo * indice;
	

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
	printf(YELLOW "Generando Models...%s\n",RESETCOL );
	if(generarModels(bd,tabla,ind))
		printf(GREEN "Models generado.%s\n",RESETCOL );
	else
		return 0;

	printf(YELLOW "Generando Functions...%s\n",RESETCOL );
	if(generarFunctions(bd,tabla,ind))
		printf(GREEN "Functions generado.%s\n",RESETCOL );
	else
		return 0;

	printf(YELLOW "Generando Route...%s\n",RESETCOL );
	if(generarRoute(bd,tabla,ind))
		printf(GREEN "Route generado.%s\n",RESETCOL );
	else
		return 0;
	return 1;
}

int generarModels(char* bd, char* tabla, Nodo * ind)
{
	FILE *fp;
	Nodo * indice;
	char arc[1024]="Models/";
	strcat(arc,tabla);
	strcat(arc,".txt");
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
  	return 1;
}

int generarFunctions(char* bd, char* tabla, Nodo * ind)
{
	FILE *fp;
	Nodo * indice;
	char arc[1024]="Functions/";
	strcat(arc,tabla);
	strcat(arc,".txt");
	printf("%s\n", arc);
	fp = fopen(arc, "w+");
	fprintf(fp,"import axios from 'axios'\nimport { saveAs } from 'file-saver'\n\nexport const sendData = newForm => {\n\treturn axios\n\t\t.post('%s/%s',{\n",tabla,tabla);
  	for (indice = ind; indice != NULL; indice = indice -> siguiente)
	{
		if(indice -> tipo == 'c')
  			fprintf(fp, "\t\t\t%s: newForm.%s,\n",indice->name, indice-> name);
  	}
  	fprintf(fp, "\n\t\t})\n\t\t.then(response => {\n\t\t\tconsole.log('Datos enviados.')\n\t\t})\n\t\t.catch(err => {\n\t\t\tconsole.log('Datos NO enviados.'+err)\n\t\t})\n}");
  	fclose(fp);
  	return 1;
}

int generarRoute(char* bd, char* tabla, Nodo * ind)
{
	FILE *fp;
	Nodo * indice;
	char arc[1024]="Route/";
	strcat(arc,tabla);
	strcat(arc,".txt");
	printf("%s\n", arc);
	fp = fopen(arc, "w+");
	fprintf(fp, "const path = require('path')\nconst express = require('express')\nconst %s = express.Router()\nconst cors = require('cors')\nconst jwt = require('jsonwebtoken')\nconst bcrypt = require('bcryptjs')\nvar pdf = require('pdf-creator-node')\nvar fs = require('fs')\n",tabla);
  	fprintf(fp, "var options = {\n\tformat: 'Letter'\n}\n\nvar pdfName = ""\n\nconst %s = require('../Models/%s.js')\n%s.use(cors())\n\nprocess.env.SECRET_KEY = 'secret'\n\n%s.post('/%s',async (req, res) => {\n\tconst today = new Date().toJSON()\n\tconst formData = {\n",tabla,tabla,tabla,tabla,tabla); 
  	for (indice = ind; indice != NULL; indice = indice -> siguiente)
	{
		if(indice -> tipo == 'c')
  			fprintf(fp, "\t%s: req.body.%s,\n",indice->name, indice-> name);
  	}
  	fprintf(fp,"\t}\n})\n\nmodule.exports = %s",tabla);
  	fclose(fp);
  	return 1;
}
