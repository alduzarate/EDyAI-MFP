#if !defined(__MANEJO_ARCHIVOS__)
#define __MANEJO_ARCHIVOS__

#include "slist.h"

// Definimos una longitud máxima para el nombre de las ciudades
#define MAX_LONGITUD_CIUDAD 50

typedef struct {
  int N, *A;
  SList nodos;
} Grafo;

Grafo* grafo_crear();

int grafo_cargar(char const* nombreDeArchivo, Grafo* datos);

void grafo_destruir(Grafo* datos);

void escribir_solucion(char const* nombreDeArchivo, Grafo* datos, int* flujos, int flujoMaximo);

#endif //__MANEJO_ARCHIVOS__