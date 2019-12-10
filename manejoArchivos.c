#include "manejoArchivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Grafo* grafo_crear() {
  Grafo* datos = malloc(sizeof(Grafo));
  datos->N = 0;
  datos->A = NULL;
  datos->nodos = slist_crear();

  return datos;
}

int grafo_cargar(char const* nombreDeArchivo, Grafo* datos) {
  FILE* entrada = fopen(nombreDeArchivo, "r");
  int longitud;
  char *nombreNodo;
  if (entrada == NULL) return 1;

  char buffer1[MAX_LONGITUD_CIUDAD], buffer2[MAX_LONGITUD_CIUDAD];

  if (fscanf(entrada, "%s", buffer1) == EOF) {  // Ignoro "Fuente"
    fclose(entrada);
    return 2;
  }

  //Leo fuente
  if(fscanf(entrada, "%s", buffer1) != EOF){
    longitud = strlen(buffer1);
    nombreNodo = malloc(sizeof(char) * (longitud + 1));
  strcpy(nombreNodo, buffer1);

  datos->nodos = slist_agregar_inicio(datos->nodos, nombreNodo);
  datos->N++;
  }

  if(fscanf(entrada, "%s", buffer1) == EOF){ //Ignoro Sumidero
    fclose(entrada);
    return 2;
  }

  //Leo sumidero
  if(fscanf(entrada, "%s", buffer1) != EOF){
  longitud = strlen(buffer1);
  nombreNodo = malloc(sizeof(char) * (longitud + 1));
  strcpy(nombreNodo, buffer1);
  datos->nodos = slist_agregar_inicio(datos->nodos, nombreNodo);
  datos->N++;
  }

  if(fscanf(entrada, "%s", buffer1)==EOF){ //Ignoro Puntos
    fclose(entrada);
    return 2;
  }

  if(fscanf(entrada, "%s", buffer1)==EOF){ //Ignoro Intermedios
    fclose(entrada);
    return 2;
  }
  
  if(fscanf(entrada, "%s", buffer1)==EOF){
    fclose(entrada);
    return 2;
  }

  nombreNodo = strtok(buffer1, ", ");
  
  while(nombreNodo != NULL) {

    longitud=strlen(nombreNodo);
    char *aux = malloc(sizeof(char) * (longitud + 1));
    strcpy(aux, nombreNodo);

    datos->nodos = slist_agregar_inicio(datos->nodos, aux);
    datos->N++;

    nombreNodo = strtok(NULL, ", ");
  }

  if (fscanf(entrada, "%s\n", buffer1) == EOF) {  // Ignoro "Conexiones"
    fclose(entrada);
    return 2;
  }

  datos->A = calloc(datos->N * datos->N, sizeof(int));
  int capacidad, error = 0;
  while (fscanf(entrada, "%[^,],%[^,],%d\n", buffer1, buffer2, &capacidad) != EOF &&
         !error) {
    int i = -1, j = -1, indice = 0;
    for (SNodo* iter = datos->nodos; iter != NULL && (i == -1 || j == -1);
         iter = iter->sig) {
      if (strcmp(buffer1, iter->dato) == 0) i = indice;
      if (strcmp(buffer2, iter->dato) == 0) j = indice;

      indice++;
    }

    if (i == -1 || j == -1)
      error = 1;
    else {
      datos->A[datos->N * i + j] = capacidad;
    }
  }

  fclose(entrada);

  if (error)
    return 3;
  else
    return 0;
}

void grafo_destruir(Grafo* datos) {
  slist_destruir(datos->nodos);
  free(datos->A);
  free(datos);
}


void escribir_solucion(char const* nombreDeArchivo, Grafo* datos, int* flujos, int flujoMax) {
  FILE* salida = fopen(nombreDeArchivo, "w");

  fprintf(salida, "%s\n%d\n%s\n", "Flujo maximo",flujoMax,"Flujos");

  char *nodoI, *nodoJ;

  for (int i = 0; i < datos->N; i++) {
    for (int j = 0; j < datos->N; j++){
      int k=0;
      if(flujos[datos->N * i + j]>0){

        SNodo* iter = datos->nodos;
        for(;k<i;iter=iter->sig,k++);
        nodoI=iter->dato;

        k=0;
        iter = datos->nodos;
        for(;k<j;iter=iter->sig,k++);
        nodoJ=iter->dato;

        int flujoActual= flujos[datos->N * i + j];

        fprintf(salida, "%s,%s,%d\n", nodoI, nodoJ, flujoActual);
      }
    }  
  }

  fclose(salida);
}


