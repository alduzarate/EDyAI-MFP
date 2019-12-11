#if !defined(__PUSH_RELABEL__)
#define __PUSH_RELABEL__

#define INFINITO 100000000

//Devuelve el mínimo entre dos valores enteros. (Se usa específicicamente en la función push)
int MIN(int x, int y);

//Envia flujo desde un vertice activo u a un vertice v mediante una arista admisible.
void push(int* C, int * F, int *exceso, int u, int v, int cantNodos);

//Se aplica la funcion sobre un nodo activo u sin ninguna arista saliente admisible en el grafo residual.
//Encuentra la nueva "height" siendo la más chiquita posible que me hablite a hacer un push, si dicho push es posible
void relabel(int* C, int* F, int *height, int u, int cantNodos);

//Repetidamente pushea flujo desde un nodo activo hasta que se vuelve inactivo, re-etiquetando
//si fuese necesario para crear aristas admisibles en el proceso.
void descarga(int* C, int * F, int *exceso, int *height, int *seen, int u, int cantNodos);

//Reacomoda la lista para elegir nodos activos.
void moveToFront(int i, int *A, int cantNodos);

//Funcion principal encargada de retornar el flujo máximo de una red.
int pushRelabel(int* C, int * F, int fuente, int sumidero, int cantNodos);

//Imprime en pantalla una matriz M de enteros.
void imprimirMatriz(int* M, int cantNodos);

#endif  // __PUSH_RELABEL__