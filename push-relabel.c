#include <stdlib.h>
#include <stdio.h>
#include "push-relabel.h"

void push(int* C, int * F, int *exceso, int u, int v, int cantNodos) {
  int send = MIN(exceso[u], C[cantNodos * u + v] - F[cantNodos * u + v]);
  F[cantNodos * u + v] += send;
  F[cantNodos * v + u] -= send;
  exceso[u] -= send;
  exceso[v] += send;
}

void relabel(int* C, int* F, int *height, int u, int cantNodos) {
  int min_height = INFINITO;
  for (int v = 0; v < cantNodos; v++) {
    if (C[cantNodos * u + v] - F[cantNodos * u + v] > 0) {
      min_height = MIN(min_height, height[v]);
      height[u] = min_height + 1;
    }
  }
}

void descarga(int* C, int * F, int *exceso, int *height, int *seen, int u, int cantNodos) {
  while (exceso[u] > 0) {
    if (seen[u] < cantNodos) {    //  chequeo el vecino siguiente
      int v = seen[u];
      if ((C[cantNodos * u + v] - F[cantNodos * u + v] > 0) && (height[u] > height[v])) {
        push(C, F, exceso, u, v, cantNodos);
      } else {
        seen[u] += 1;
      }
    } else {    // ya chequeamos todos los vecinos, debemos re-etiquetar
      relabel(C, F, height, u, cantNodos);
      seen[u] = 0;
    }
  }
}

void moveToFront(int i, int *A, int cantNodos) {
  int temp = A[i];
  for (int n = i; n > 0; n--) {
    A[n] = A[n-1];
  }
  A[0] = temp;
}

int pushRelabel(int* C, int * F, int fuente, int sumidero, int cantNodos) {
  int *exceso, *height, *list, *seen, p;

  exceso = (int *) calloc(cantNodos, sizeof(int));  // flujo entrante menos flujo saliente del nodo
  height = (int *) calloc(cantNodos, sizeof(int));  // hight del nodo
  seen = (int *) calloc(cantNodos, sizeof(int));    // vertices vecinos vistos desde el ultimo relabel
  list = (int *) calloc((cantNodos-2), sizeof(int));  // nodo "cola", sin contar la fuente ni el sumidero

  //defino list
  for (int i = 0, p = 0; i < cantNodos; i++){
    if((i != fuente) && (i != sumidero)) {
      list[p] = i;
      p++;
    }
  }

  height[fuente] = cantNodos; // el camino más largo de fuente a sumidero es si o si menor a la cantidad de nodos
  exceso[fuente] = INFINITO;  // enviar todo el flujo que sea posible a los vertices vecinos de la fuente
  for (int i = 0; i < cantNodos; i++)
    push(C, F, exceso, fuente, i, cantNodos);

  p = 0;
  while (p < cantNodos - 2) {
    int u = list[p];
    int old_height = height[u];
    descarga(C, F, exceso, height, seen, u, cantNodos);
    if (height[u] > old_height) {
      moveToFront(p, list, cantNodos);  // movemos al frente de la lista
      p = 0;  // empezar desde el frente de la lista
    } else {
      p += 1;
    }
  }
  int maxFlujo = 0;
  for (int i = 0; i < cantNodos; i++)
    maxFlujo += F[cantNodos * fuente + i];

  free(list);
  free(seen);
  free(height);
  free(exceso);

  return maxFlujo;
}

void imprimirMatriz(int* M, int cantNodos) {
  for (int i = 0; i < cantNodos; i++) {
    for (int j = 0; j < cantNodos; j++)
      printf("%d\t",M[cantNodos * i + j]);
    printf("\n");
  }
}

int MIN(int x, int y){
  return ((x) < (y) ? (x) : (y));
}
