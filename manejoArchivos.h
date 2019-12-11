#if !defined(__MANEJO_ARCHIVOS__)
#define __MANEJO_ARCHIVOS__

#include "slist.h"

// Definimos una longitud máxima para el nombre de los nodos
#define MAX_LONGITUD_NODO 50

typedef struct {
  int N, *A;
  SList nodos;
} Grafo;

//Crea un grafo
Grafo* grafo_crear();

//Lee el archivo y el entero que retorna depende de si hubo algun error o si se leyó correctamente.
int grafo_cargar(char const* nombreDeArchivo, Grafo* datos);

//Destruye un grafo
void grafo_destruir(Grafo* datos);

//Escribe en un archivo el flujo máximo encontrado
void escribir_solucion(char const* nombreDeArchivo, Grafo* datos, int* flujos, int flujoMaximo);

#endif //__MANEJO_ARCHIVOS__