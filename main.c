#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "manejoArchivos.h"
#include "push-relabel.h"

int main(int argc, char const* argv[]) {
  if (argc != 3) {
    printf("Error. El número de argumentos ingresado es incorrecto.\n");
    printf("Modo de uso: %s archivoEntrada archivoSalida\n", argv[0]);
    return 1;
  }

  Grafo* datos = grafo_crear();
  int error = grafo_cargar(argv[1], datos);
  if (error) {
    switch (error) {
      case 1:
        printf("Error: El archivo %s no existe.\n", argv[1]);
        break;
      case 2:
        printf("Error: El formato del archivo %s es incorrecto.\n", argv[1]);
        break;
      case 3:
        printf("Error: Uno de los lados contiene un nodo inexistente.\n");
    }

    grafo_destruir(datos);
    return 1;
  } else {
    printf("El grafo de %s ha sido leído correctamente.\n", argv[1]);
  }

  int *flow;
  flow= calloc(datos->N * datos->N, sizeof(int));

  clock_t timer = clock();

  int maxFlujo = pushRelabel(datos->A, flow, datos->N - 1, datos->N - 2,datos->N);

  timer = clock() - timer;

  /*
  printf("Capacidades:\n");
  imprimirMatriz(datos->A,datos->N);
  
  printf("Flujos:\n");
  imprimirMatriz(flow,datos->N);
  */

  printf("Se ha encontrado una solución en %lfs.\n", ((double)timer) / CLOCKS_PER_SEC);
  
  escribir_solucion(argv[2], datos, flow, maxFlujo);
  printf("La solución al MFP ha sido escrita en %s.\n", argv[2]);

  grafo_destruir(datos);
  free(flow);

  if (error)
    return 1;
  else
    return 0;
}