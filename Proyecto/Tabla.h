#ifndef TABLA_SIMBOLOS
#define TABLA_SIMBOLOS

#define YELLOW	"\x1b[33m"
#define RED	"\x1b[31m"
#define REDBG	"\x1b[31m"
#define GREEN	"\x1b[32m"
#define BLUE	"\x1b[34m"
#define RESETCOL	"\x1b[0m"

typedef struct Nodo
{
	char* name;
	int tamanio;
	char* pert;
	char* tipod;
	char tipo;
	struct Nodo* siguiente;
}Nodo ;		//Estructura que utilizaremos para almacenar las variables

void insertarBD(char* nombre);
void insertarTabla(char* nombre,char* perte);
void insertarCampo(char* nombre, char* tipo,char* perte, int tamanio);

Nodo* NuevoNodoBD(char* nombre);
Nodo* NuevoNodoTabla(char* nombre, char* pert);
Nodo* NuevoNodoCampo(char* nombre, char* tipo, char* perte, int tamanio);

//Funciones para obtener los datos de las variables
void * getVariable(char* nombre);
void   showVar(void* var);
int    existe (char* nombre);
char* existetabla();
char* existebd();

// Funciones auxiliares para impresión de texto con color.
void printError(char * m);
void printWarning(char * m);

void GuardarArchivo();

#endif